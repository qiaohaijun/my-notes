### 依赖的lib
1. abseil::string_view
2. rapidJson

### 持有的数据
1. json_body接收到的json
2. request_id
3. HttpResponseMsg
4. map<string, tensor>
5. output_json

### 生命周期
接受到json 到处理完成.

PipeTask跨越了整个流水线.

```cpp
class PipeTask {
  private:
    abseil::string_view body_json;
    int request_id;
    HttpResponseMsg http_resp_msg;
    map<std::string, tensorflow::tensor> tf_input_map;
    map<std::string, tensorflow::tensor> tf_output_map;
    abseil::string_view output_json;
}
```
