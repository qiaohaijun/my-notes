```c++
#include <iostream>
int main() {
  if (NULL == nullptr) {
    std::cerr  << "1" << std::endl;
  } else {
    std::cerr << "2" << std::endl;
  }

}

```

结果是`1`,也就是说, 现在情况下, 他们是相等的.
