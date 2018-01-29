

```python
a = (prev < 0, lambda: prev+3)
b = (prev < 10, lambda: prev*3)
c = (prev < 20, lambda: prev-3)

pairs = [a,b,c]
default = lambda: prev/3
out = tf.case(pairs, default)
```
