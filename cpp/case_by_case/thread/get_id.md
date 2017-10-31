### thread_id
```

  /// thread
  class thread
  {
  public:
    typedef __gthread_t			native_handle_type;
    struct _Impl_base;
    typedef shared_ptr<_Impl_base>	__shared_base_type;

    /// thread::id
    class id
    {
      native_handle_type	_M_thread;

    public:
      id() noexcept : _M_thread() { }

      explicit
      id(native_handle_type __id) : _M_thread(__id) { }

    private:
      friend class thread;
      friend class hash<thread::id>;

      friend bool
      operator==(thread::id __x, thread::id __y) noexcept
      { return __gthread_equal(__x._M_thread, __y._M_thread); }

      friend bool
      operator<(thread::id __x, thread::id __y) noexcept
      { return __x._M_thread < __y._M_thread; }

      template<class _CharT, class _Traits>
	friend basic_ostream<_CharT, _Traits>&
	operator<<(basic_ostream<_CharT, _Traits>& __out, thread::id __id);
    };
```
thread id 不是一个基本类型. 在gcc中间, 这个id是一个`class`.
