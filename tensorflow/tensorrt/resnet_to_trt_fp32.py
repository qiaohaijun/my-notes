import tensorflow as tf
from tensorflow.contrib import tensorrt as trt 
from tensorflow.core.protobuf import config_pb2 as cpb2
from tensorflow.core.protobuf import rewriter_config_pb2 as rwpb2
from tensorflow.python.client import session as csess
from tensorflow.python.framework import constant_op as cop 
from tensorflow.python.framework import dtypes as dtypes
from tensorflow.python.framework import importer as importer
from tensorflow.python.framework import ops as ops 
from tensorflow.python.ops import array_ops as aops
from tensorflow.python.ops import math_ops as mops
from tensorflow.python.ops import nn as nn
from tensorflow.python.ops import nn_ops as nn_ops

graph_pb = './resnet.pb'

graph_def=tf.GraphDef()
with tf.gfile.GFile(graph_pb, "rb") as f:
    graph_def.ParseFromString(f.read())

gpu_options=tf.GPUOptions(per_process_gpu_memory_fraction=0.5)

trt_graph=trt.create_inference_graph(
        input_graph_def = graph_def,
        outputs = ["ArgMax"],
        max_batch_size = 1,
        max_workspace_size_bytes=1<<25,
        precision_mode = "FP32"
        )   
