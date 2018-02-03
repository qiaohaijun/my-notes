```c++
#include "capi.h"
#include "gtest/gtest.h"

TEST(CAPIVector, create) {
  //! TODO(yuyang18): Test GPU Code.
  paddle_ivector vec;
  int array[3] = {1, 2, 3};
  vec = paddle_ivector_create(array, 3, true, false);
  ASSERT_EQ(kPD_NO_ERROR, paddle_ivector_resize(vec, 1000));
  uint64_t size;
  ASSERT_EQ(kPD_NO_ERROR, paddle_ivector_get_size(vec, &size));
  ASSERT_EQ(kPD_NO_ERROR, paddle_ivector_destroy(vec));
}

TEST(CAPIVector, createNone) {
  paddle_ivector vec = paddle_ivector_create_none();
  ASSERT_EQ(kPD_NO_ERROR, paddle_ivector_destroy(vec));
}
```

这里我们看到了一个含有多个bool类型的参数的函数

```
vec = paddle_ivector_create(array, 3, true, false);
```

我完全不知道这个是什么意思.
