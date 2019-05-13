    // set up your input paths
    const string pathToGraph = "/home/senius/python/c_python/test/model-10.meta";
    const string checkpointPath = "/home/senius/python/c_python/test/model-10";

    auto session = NewSession(SessionOptions()); //　创建会话
    if (session == nullptr)
    {
        throw runtime_error("Could not create Tensorflow session.");
    }

    Status status;

    // Read in the protobuf graph we exported
    MetaGraphDef graph_def;
    status = ReadBinaryProto(Env::Default(), pathToGraph, &graph_def);　 //　导入图模型
    if (!status.ok())
    {
        throw runtime_error("Error reading graph definition from " + pathToGraph + ": " + status.ToString());
    }

    // Add the graph to the session
    status = session->Create(graph_def.graph_def());　 //　将图模型加入到会话中
    if (!status.ok())
    {
        throw runtime_error("Error creating graph: " + status.ToString());
    }

    // Read weights from the saved checkpoint
    Tensor checkpointPathTensor(DT_STRING, TensorShape());
    checkpointPathTensor.scalar<std::string>()() = checkpointPath;　// 读取预训练好的权重
    status = session->Run({{graph_def.saver_def().filename_tensor_name(), checkpointPathTensor},}, {},
                          {graph_def.saver_def().restore_op_name()}, nullptr);
    if (!status.ok())
    {
        throw runtime_error("Error loading checkpoint from " + checkpointPath + ": " + status.ToString());
    }
