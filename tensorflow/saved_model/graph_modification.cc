tensorflow::Session * load_graph(const std::string &path, const std::string &device = std::string())
{
    tensorflow::GraphDef graph_def;
    tensorflow::ReadBinaryProto(tensorflow::Env::Default(), path, &graph_def);

    if(!device.empty())
    {
        for(int i = 0; i < graph_def.node_size(); ++i)
        {
            graph_def.mutable_node(i)->set_device(device);
        }
    }

    tensorflow::Session *session;
    tensorflow::NewSession(tensorflow::SessionOptions(), &session);
    session->Create(graph_def);
    return session;
}

...

tensorflow::Session *session_gpu_0 = load_graph(graph_file_path, "/gpu:0");
tensorflow::Session *session_gpu_1 = load_graph(graph_file_path, "/gpu:1");
