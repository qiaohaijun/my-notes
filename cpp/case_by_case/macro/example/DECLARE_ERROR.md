```cxx
// Convenience functions for generating and using error status.
// Example usage:
//   status.Update(errors::InvalidArgument("The ", foo, " isn't right."));
//   if (errors::IsInvalidArgument(status)) { ... }
//   switch (status.code()) { case error::INVALID_ARGUMENT: ... }

#define DECLARE_ERROR(FUNC, CONST)                                       \
  template <typename... Args>                                            \
  ::tensorflow::Status FUNC(Args... args) {                              \
    return ::tensorflow::Status(::tensorflow::error::CONST,              \
                                ::tensorflow::strings::StrCat(args...)); \
  }                                                                      \
  inline bool Is##FUNC(const ::tensorflow::Status& status) {             \
    return status.code() == ::tensorflow::error::CONST;                  \
  }

DECLARE_ERROR(Cancelled, CANCELLED)
DECLARE_ERROR(InvalidArgument, INVALID_ARGUMENT)
DECLARE_ERROR(NotFound, NOT_FOUND)
DECLARE_ERROR(AlreadyExists, ALREADY_EXISTS)
DECLARE_ERROR(ResourceExhausted, RESOURCE_EXHAUSTED)
DECLARE_ERROR(Unavailable, UNAVAILABLE)
DECLARE_ERROR(FailedPrecondition, FAILED_PRECONDITION)
DECLARE_ERROR(OutOfRange, OUT_OF_RANGE)
DECLARE_ERROR(Unimplemented, UNIMPLEMENTED)
DECLARE_ERROR(Internal, INTERNAL)
DECLARE_ERROR(Aborted, ABORTED)
DECLARE_ERROR(DeadlineExceeded, DEADLINE_EXCEEDED)
DECLARE_ERROR(DataLoss, DATA_LOSS)
DECLARE_ERROR(Unknown, UNKNOWN)
DECLARE_ERROR(PermissionDenied, PERMISSION_DENIED)
DECLARE_ERROR(Unauthenticated, UNAUTHENTICATED)

#undef DECLARE_ERROR
```

这段代码是 `tensorflow` 中的`errors.h`. 

这段代码用macro来实现
1. 代码简洁, 清晰
2. 避免冗余
3. 只使用了 macro 的字符串展开功能.
