```python
pred = a < b
def run_if_true():
  return tf.add(3,3)

def run_if_false():
  return tf.square(3)
  
out = tf.cond(pred, run_if_true, run_if_false)

```
