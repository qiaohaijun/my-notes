A method has conditional behavior that does not make clear what the normal path of execution is 
**Use Guard Clauses for all the special cases**

```cxx
double getPayAmount() {
  double result;
  if (_isDead) result = deadAmount();
  else {
    if (_isSeparated) result = separatedAmount();
    else {
      if (_isRetired) result = retiredAmount();
      else result = normalPayAmount();
    };
  }
  return result;
};  

```

使用`Guard Clause`来减少`if-else`

```cxx
double getPayAmount() {
  if (_isDead) return deadAmount();
  if (_isSeparated) return separatedAmount();
  if (_isRetired) return retiredAmount();
  return normalPayAmount();
};  
```

---
 
这个例子很不合理, 为什么要在一个`getPayAmount()`函数里进行这种角色的判断.

### link
- https://refactoring.com/catalog/replaceNestedConditionalWithGuardClauses.html
