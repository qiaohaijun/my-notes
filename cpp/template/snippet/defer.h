template <typename Func>
class deferred_action {
    Func _func;
    bool _cancelled = false;
public:
    deferred_action(Func&& func) : _func(std::move(func)) {}
    ~deferred_action() { if(!_cancelled)_func(); }
    void cancel() { _cancelled = true; }
};

template <typename Func>
inline deferred_action<Func> defer(Func&& func) {
    return deferred_action<Func>(std::forward<Func>(func));
}

作者：Anran Wang
链接：https://www.zhihu.com/question/37692782/answer/73384708
来源：知乎
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
