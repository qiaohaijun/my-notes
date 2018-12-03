```c++
#include<iostream>
#include<cstdlib>
using namespace std;
int main()
{
  int a[] = {1,2,3};
  cout << a         << "  " << &a         << endl;
  cout << sizeof(a) << "  " << sizeof(&a) << endl;
  return 0;
}

```

---
### 编译器的把戏
#### a
```
sizeof(a) => sizeof(int[3])
```
#### &a
```
sizeof(&a) => sizeof(int(*)[3])
```
#### &a[0]
```
sizeof(&a[0]) => sizeof(int*)
```
