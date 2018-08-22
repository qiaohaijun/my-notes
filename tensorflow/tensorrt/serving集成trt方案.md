https://github.com/tensorflow/serving/blob/master/tensorflow_serving/model_servers/BUILD#L283

add a line

"@org_tensorflow//tensorflow/contrib/tensorrt:trt_engine_op_kernel",
SUPPORTED_TENSORFLOW_OPS = [ 
    "@org_tensorflow//tensorflow/contrib:contrib_kernels",
    "@org_tensorflow//tensorflow/contrib:contrib_ops_op_lib",
    "@org_tensorflow//tensorflow/contrib/tensorrt:trt_engine_op_kernel",
]
then , I find TensorRT in dynamic link so file.

0000000006ec8f60 V _ZTSN10tensorflow8tensorrt10TRTCalibOpE
0000000006ec9160 V _ZTSN10tensorflow8tensorrt11TRTEngineOpE
0000000006ec9320 V _ZTSN10tensorflow8tensorrt17TRTInt8CalibratorE
0000000006ec8fa0 V _ZTSN10tensorflow8tensorrt22TRTCalibrationResourceE
hope useful.
