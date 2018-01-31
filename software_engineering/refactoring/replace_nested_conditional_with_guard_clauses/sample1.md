嵌套的代码的最大的问题, 还不是不美观, 更大的问题是增加了理解逻辑的复杂度.

```
double GetPayAmount()
{
	double result;
	if(_isDead) result = deadAmount();
	else
	{
		if(_isSeparated)
		{
			result = separatedAmount();
		}
		else
		{
			if(_isRetired)
			{
				result = retiredAmount();
			}
			else
			{
				result = normalPayAmount();
			}
		}
	}
	return result;
}

```


```c++
double GetPayAmount()
{
	if(_isDead)
	{
		return deadAmount();
	}
	if(_isSeparated)
	{
		return separatedAmount();
	}
	if(_isRetired)
	{
		return retiredAmount();
	}
	return normalPayAmount();
}
```
