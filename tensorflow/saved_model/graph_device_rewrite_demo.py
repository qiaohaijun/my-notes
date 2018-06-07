from google.protobuf import text_format
import tensorflow as tf

hello = tf.constant('Hello, TensorFlow!')
tf.train.write_graph(tf.get_default_graph(), '/tmp', 'g1')

with open('/tmp/g1', 'rb') as f:
  graph_text = f.read()
print(graph_text)
print('-' * 100)

graphs = []
for g in range(2):
  graphs.append(tf.Graph())
  with graphs[g].as_default():
    graph_def = tf.GraphDef()
    text_format.Merge(graph_text, graph_def)
    with tf.device('/gpu:' + str(g)):
      tf.import_graph_def(graph_def, name='')
    print(tf.get_default_graph().as_graph_def())
    print('-' * 100)
