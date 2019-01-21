#include <iostream>
#include <fstream>
#include <arpa/inet.h>
#include "tensorflow_serving/core/availability_preserving_policy.h"
#include "tensorflow_serving/model_servers/platform_config_util.h"
#include "tensorflow_serving/model_servers/server_core.h"
#include "tensorflow_serving/servables/tensorflow/predict_impl.h"

using namespace std;
using namespace tensorflow::serving;

class DataSet {
public:
    DataSet()
    {}

    void LoadDataFromDir(const std::string& path)
    {
        const char* x_train_file = "train-images-idx3-ubyte";
        const char* y_train_file = "train-labels-idx1-ubyte";
        const char* x_test_file = "t10k-images-idx3-ubyte";
        const char* y_test_file = "t10k-labels-idx1-ubyte";
        m_x_train = ExtractImages(path + "/" + x_train_file);
        m_y_train = ExtractLabels(path + "/" + y_train_file);
        m_x_test = ExtractImages(path + "/" + x_test_file);
        m_y_test = ExtractLabels(path + "/" + y_test_file);
    }

    vector<double>& x_train()
    {
        return m_x_train;
    }

    vector<int>& y_train()
    {
        return m_y_train;
    }

    vector<double>& x_test()
    {
        return m_x_test;
    }

    vector<int>& y_test()
    {
        return m_y_test;
    }

private:
    uint32_t ReadUint32(ifstream& is)
    {
        uint32_t data = 0;
        auto read_count = is.readsome(reinterpret_cast<char*>(&data), 4);
        if (read_count != 4) {
            throw logic_error("can't read 4 bytes");
        }
        return ntohl(data);
    }

    uint8_t ReadUint8(ifstream& is)
    {
        uint8_t data = 0;
        auto read_count = is.readsome(reinterpret_cast<char*>(&data), 1);
        if (read_count != 1) {
            throw logic_error("can't read 1 byte");
        }
        return data;
    }

    vector<double> ExtractImages(const string& file)
    {
        ifstream is(file);
        if (!is) {
            throw logic_error("can't open file: " + file);
        }
        uint32_t magic = ReadUint32(is);
        if (magic != 2051) {
            throw logic_error("bad magic: " + to_string(magic));
        }
        uint32_t num = ReadUint32(is);
        uint32_t rows = ReadUint32(is);
        uint32_t cols = ReadUint32(is);
        vector<double> images;
        for (size_t i = 0; i < num*rows*cols; ++i) {
            uint8_t byte = ReadUint8(is);
            images.push_back(static_cast<double>(byte)/255.0);
        }
        return images;
    }

    vector<int> ExtractLabels(const string& file)
    {
        ifstream is(file);
        if (!is) {
            throw logic_error("can't open file: " + file);
        }
        uint32_t magic = ReadUint32(is);
        if (magic != 2049) {
            throw logic_error("bad magic: " + to_string(magic));
        }
        uint32_t num = ReadUint32(is);
        vector<int> labels;
        for (size_t i = 0; i < num; ++i) {
            uint8_t byte = ReadUint8(is);
            labels.push_back(byte);
        }
        return labels;
    }

    std::vector<double> m_x_train;
    std::vector<int> m_y_train;
    std::vector<double> m_x_test;
    std::vector<int> m_y_test;
};

int GetPredictValue(const PredictResponse& resp)
{
    int predicted = 0;
    for (const auto& p : resp.outputs()) {
        if (p.first == "scores") {
            float max = 0;
            for (size_t j = 0; j < p.second.float_val_size(); ++j) {
                if (p.second.float_val(j) > max) {
                    max = p.second.float_val(j);
                    predicted = j;
                }
            }
        }
    }
    return predicted;
}

int main()
{
    // 加载测试数据。
    DataSet data_set;
    data_set.LoadDataFromDir("mnist_data");

    // 设置Serving选项。
    ServerCore::Options options;
    auto config = options.model_server_config.mutable_model_config_list()->add_config();
    // 设置模型名称，请求模型预测时必须与此一致，见下面。
    config->set_name("mnist");
    // 设置模型的路径。注意：必须是绝对路径。
    config->set_base_path("/home/qspace/data/spockwang/models");
    // 设置模型平台。对Tensorflow训练的模型来讲必须是"tensorflow".
    config->set_model_platform("tensorflow");

    options.aspired_version_policy = std::unique_ptr<AspiredVersionPolicy>(new AvailabilityPreservingPolicy);

    // 运行平台配置。
    SessionBundleConfig session_bundle_config;
    session_bundle_config.mutable_session_config()->set_intra_op_parallelism_threads(1);
    session_bundle_config.mutable_session_config()->set_inter_op_parallelism_threads(0);
    options.platform_config_map = CreateTensorFlowPlatformConfigMap(session_bundle_config, true);

    std::unique_ptr<ServerCore> core;
    auto status = ServerCore::Create(std::move(options), &core);
    if (!status.ok()) {
        cerr << "error: " << status.ToString() << endl;
        return 1;
    }
    std::unique_ptr<TensorflowPredictor> predictor(new TensorflowPredictor(true));

    // 遍历测试数据进行预测，然后计算预测精度。
    int total_cnt = 0;
    int success_cnt = 0;
    int n = data_set.x_test().size()/784;
    for (int i = 0; i < n; ++i) {
        cout << "#" << i << "/" << n << endl;
        vector<double> x = vector<double>(data_set.x_test().begin()+784*i,
                                          data_set.x_test().begin()+784*(i+1));
        int y = data_set.y_test()[i];

        PredictRequest req;
        auto model_spec = req.mutable_model_spec();
        // 与加载模型时设置的名字保持一致，见上面。
        model_spec->set_name("mnist");
        // 与保存模型时设置的签名保持一致，见mnist_saved_model.py
        model_spec->set_signature_name("predict_images");

        // 构造输入特征。
        auto inputs = req.mutable_inputs();
        auto& tensor = (*inputs)["images"];
        tensor.set_dtype(tensorflow::DataType::DT_FLOAT);
        for (auto i : x) {
            tensor.add_float_val(i);
        }
        tensor.mutable_tensor_shape()->add_dim()->set_size(1);
        tensor.mutable_tensor_shape()->add_dim()->set_size(x.size());

        // 计算预测输出。
        PredictResponse resp;
        auto status = predictor->Predict(tensorflow::RunOptions(), core.get(), req, &resp);
        if (!status.ok()) {
            cerr << status.ToString() << endl;
            return 1;
        }
        ++total_cnt;
        int predicted = GetPredictValue(resp);
        if (y == predicted) {
            ++success_cnt;
        }
    }

    double accuracy = static_cast<double>(success_cnt)/total_cnt;
    cout << "Accuracy: " << accuracy << endl;
    return 0;
}
