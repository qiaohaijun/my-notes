template<typename ...T>
using Tp=std::tuple<T...>;

template<typename ...T>
static std::tuple<T...> mk_Tp(T... arr){
    return std::make_tuple(arr...);
}

template<typename Tuple, typename F, int... stack>
struct _match_Tp_helper{
    static void _match(const Tuple& tp, const F& func);
};


template<typename Tuple, typename F, int... stack>
struct _match_Tp_helper<Tuple, F, 0, stack...> {
    static void _match(const Tuple &tp, const F &func) {
        func(std::get<0>(tp), std::get<stack>(tp)...);
    }
};

template<typename Tuple, typename F, int x, int... stack>
struct _match_Tp_helper<Tuple, F, x, stack...>{
    static void _match(const Tuple& tp, const F& func){
        return _match_Tp_helper<Tuple,F,x-1,x,stack...>::_match(tp,func);
    }
};

template<typename F, typename ...T>
static void match_Tp(const std::tuple<T...>& tp, const F& func){
    const int tplen=sizeof...(T);
    _match_Tp_helper<std::tuple<T...>,F,tplen-1>::_match(tp, func);
}
