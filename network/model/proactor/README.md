I/O 多路复用往往对应 Reactor 模式，异步 I/O 往往对应 Proactor。

Proactor 在 *nix 中没有很好的实现，但是在 Windows 上大放异彩（例如 IOCP 模型）。
