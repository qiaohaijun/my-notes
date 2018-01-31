```c#
public void PrintOwing(double amount)
{
PrintBanner();
	// print details
	Console.WriteLine("name:" + _name);
	Console.WriteLine("amount:" + _amount);
}
```


```c#
public void PrintOwing(double amount)
{
	PrintBanner();
	PrintDetails(amount);
}

public void PrintDetails(double amount)
{
	// print details
	Console.WriteLine("name:" + _name);
	Console.WriteLine("amount:" + _amount);
}
```
