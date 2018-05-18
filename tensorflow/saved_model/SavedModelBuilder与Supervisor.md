```
#!/usr/bin/env python2.7

import tensorflow as tf

from tensorflow.python.saved_model import utils
from tensorflow.examples.tutorials.mnist import input_data
from tensorflow.contrib.session_bundle import exporter


tf.app.flags.DEFINE_string("ps_hosts", "", "Comma-separated list of hostname:port pairs")

tf.app.flags.DEFINE_string("worker_hosts", "", "Comma-separated list of hostname:port pairs")

tf.app.flags.DEFINE_string("job_name", "", "One of 'ps', 'worker'")

tf.app.flags.DEFINE_integer("task_index", 0, "Index of task within the job")
tf.app.flags.DEFINE_integer("batch_size", 100, "Index of task within the job")

tf.app.flags.DEFINE_integer('training_iteration', 2,
                            'number of training iterations.')
tf.app.flags.DEFINE_integer('model_version', 1, 'version number of the model.')
tf.app.flags.DEFINE_string('work_dir', 'model/', 'Working directory.')
tf.app.flags.DEFINE_string('train_dir', 'MNIST_data/', 'Working directory.')


FLAGS = tf.app.flags.FLAGS


def main(_):
    ps_hosts = FLAGS.ps_hosts.split(",")

    worker_hosts = FLAGS.worker_hosts.split(",")
    cluster = tf.train.ClusterSpec({"ps": ps_hosts, "worker": worker_hosts})
    server = tf.train.Server(cluster, job_name=FLAGS.job_name, task_index=FLAGS.task_index)

    if FLAGS.job_name == "ps":
        server.join()
    elif FLAGS.job_name == "worker":
        train(server, cluster)


def train(server, cluster):
    # Train model
    print('Training model...')
    is_chief = (FLAGS.task_index == 0)
    with tf.device(
            tf.train.replica_device_setter(worker_device="/job:worker/task:%d" % FLAGS.task_index, cluster=cluster)):
        mnist = input_data.read_data_sets(FLAGS.train_dir, one_hot=True)
        serialized_tf_example = tf.placeholder(tf.string, name='tf_example')
        feature_configs = {'x': tf.FixedLenFeature(shape=[784], dtype=tf.float32), }
        tf_example = tf.parse_example(serialized_tf_example, feature_configs)

        x = tf.identity(tf_example['x'], name='x')  # use tf.identity() to assign name
        y_ = tf.placeholder('float', shape=[None, 10])

        w = tf.Variable(tf.zeros([784, 10]))
        b = tf.Variable(tf.zeros([10]))

        y = tf.nn.softmax(tf.matmul(x, w) + b, name='y')
        cross_entropy = -tf.reduce_sum(y_ * tf.log(y))

        global_step = tf.Variable(0)
        train_step = tf.train.GradientDescentOptimizer(0.01).minimize(cross_entropy, global_step=global_step)
        correct_prediction = tf.equal(tf.argmax(y, 1), tf.argmax(y_, 1))
        accuracy = tf.reduce_mean(tf.cast(correct_prediction, 'float'))

        summary_op = tf.summary.merge_all()
        init_op = tf.global_variables_initializer()
        saver = tf.train.Saver(sharded=True)
        model_version = tf.constant(FLAGS.model_version)
        model_exporter = exporter.Exporter(saver)
        tensor_info_x = utils.build_tensor_info(x)
        tensor_info_y = utils.build_tensor_info(y)
        model_exporter.init(
            tf.get_default_graph().as_graph_def(),
            clear_devices=True,

            named_graph_signatures={
                'inputs':
                    exporter.generic_signature({"images": tensor_info_x}),
                'outputs':
                    exporter.generic_signature({"scores": tensor_info_y})
            })

        sv = tf.train.Supervisor(is_chief=is_chief, logdir="train_logs", init_op=init_op,
                                 summary_op=summary_op, saver=saver, global_step=global_step, save_model_secs=600)

        with sv.managed_session(server.target) as sess:
            step = 0

            while not sv.should_stop() and step < 100000:
                batch_xs, batch_ys = mnist.train.next_batch(FLAGS.batch_size)
                train_feed = {x: batch_xs, y_: batch_ys}

                _, step = sess.run([train_step, global_step], feed_dict=train_feed)

                if step % 1000 == 0:
                    print("global step: {} , accuracy:{}".format(step, sess.run(accuracy,
                                                                                feed_dict=train_feed)))

            print('training accuracy %g' % sess.run(
                accuracy, feed_dict={x: mnist.test.images,
                                     y_: mnist.test.labels}))
            print('Done training!')

            if is_chief:
                model_exporter.export(FLAGS.work_dir,model_version
                                      , sess)
                print('Done exporting!')


if __name__ == '__main__':
    tf.app.run()
```

### 解决方案
1. https://github.com/tensorflow/serving/issues/373
2. https://github.com/tensorflow/tensorflow/issues/11549
