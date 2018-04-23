```c++
// Parses a comma separated list of gRPC channel arguments into list of
// ChannelArgument.
std::vector<GrpcChannelArgument> parseGrpcChannelArgs(
    const string& channel_arguments_str) {
  const std::vector<string> channel_arguments =
      tensorflow::str_util::Split(channel_arguments_str, ",");
  std::vector<GrpcChannelArgument> result;
  for (const string& channel_argument : channel_arguments) {
    const std::vector<string> key_val =
        tensorflow::str_util::Split(channel_argument, "=");
    result.push_back({key_val[0], key_val[1]});
  }
  return result;
}

```
parse有语法解析器的含义, 所以这个可以用在有语法解析类似的场景上.
