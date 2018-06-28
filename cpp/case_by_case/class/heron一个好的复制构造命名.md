```c++
NetworkOptions::NetworkOptions(const NetworkOptions& _copyFrom) {
  host_ = _copyFrom.get_host();
  port_ = _copyFrom.get_port();
  max_packet_size_ = _copyFrom.get_max_packet_size();
  socket_family_ = _copyFrom.get_socket_family();
  high_watermark_ = _copyFrom.get_high_watermark();
  low_watermark_ = _copyFrom.get_low_watermark();
  sin_path_ = _copyFrom.get_sin_path();
}
```

_copyFrom非常显式的将命名告诉了我们.

以后就要这么命名.
