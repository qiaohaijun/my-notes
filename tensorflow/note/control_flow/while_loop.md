```python
def cond(i, val):
  return i < 100
def body(i, val):
  return i+1, val+5
 
loop=tf.while_loop(cond,body, (0,0)) 
```
