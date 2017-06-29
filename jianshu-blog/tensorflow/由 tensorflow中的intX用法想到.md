这里的X 是一个数值, 8,16,32,64
1. int8
2. int16
3. int32
4. int64

显而易见, 这个表示的是用几个字节来表示一个int型数值.
---
今天在看 tensorflow 的 proto 文件, 后面再说为什么看这些个文件.

```proto

syntax = "proto3";

package tensorflow;
// option cc_enable_arenas = true;
option java_outer_classname = "AllocationDescriptionProtos";
option java_multiple_files = true;
option java_package = "org.tensorflow.framework";

message AllocationDescription {
  // Total number of bytes requested
  int64 requested_bytes = 1;

  // Total number of bytes allocated if known
  int64 allocated_bytes = 2;

  // Name of the allocator used
  string allocator_name = 3;

  // Identifier of the allocated buffer if known
  int64 allocation_id = 4;

  // Set if this tensor only has one remaining reference
  bool has_single_reference = 5;

  // Address of the allocation.
  uint64 ptr = 6;
};
```
在文件中发现用的是intX, 没有用我们常见的 int, 而且前一段时间同事和我讨论了一个问题, 32位机器和64位机器的指针的大小是不同的.
一个32bit一个64bit, 因为没有考虑这个情况, 所以后来的时候代码遇到点移植的问题, 不过64位是兼容32位的, 所以在编译的时候加上一个编译选项就可以了.

---

如果只在一个不变的平台和操作系统上写代码, 其实不用具体的考虑int 到底需要几个字节. 

但是如果你需要考虑不同的处理器, 不同的操作系统的情况下, 如果明确指明int需要的字节数, 那么就会遇到意想不到的问题.

---

为什么看proto文件
1. 学习谷歌proto的规范
2. tensorflow很多情况下拿proto文件当做类似java的bean的机制. 所以看proto可以了解到tensorflow,内部的一些数据结构. 

需要说的是, 这个方法读源码是不好的, 因为方法不对路, 浪费时间和精力.

如果学习tensorflow 源码, 可以先看看 mxnet 是如何实现功能的. 
推荐mxnet, 因为代码少, 读起来没那么费劲
