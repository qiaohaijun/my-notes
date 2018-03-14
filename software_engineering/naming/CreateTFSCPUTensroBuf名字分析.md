 ```cxx
 TFSCPUTensorBuf * my_tfs_buf = TFSCPUTensorBuf::CreateTFSCPUTensroBuf();
 ```
 
 这个API有`信息冗余`的问题.
 
 ```cxx
 TFSCPUTensorBuf * my_tfs_buf = TFSCPUTensorBuf::Create();
 ```
 
 这样是不是好了很多.
