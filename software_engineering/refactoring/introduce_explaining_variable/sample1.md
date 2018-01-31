```c++
if((platform.ToUpper().IndexOf("MAC") > -1) && (browser.ToUpper().IndexOf("IE") > -1) && wasInitialized() && resize > 0)
{
	// do something
}
```


```c++
bool isMacOs = platform.ToUpper().IndexOf("MAC") > -1;
bool isIE = browser.ToUpper().IndexOf("IE") > -1;
bool wasResized = resize > 0;

if(isMacOs && isIE && wasInitialized() && wasResized)
{
	// do something
}
```
