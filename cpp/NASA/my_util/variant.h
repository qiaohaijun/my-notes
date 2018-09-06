#include <typeindex>
#include <iostream>
#include <type_traits>
using namespace std;

template<typename T, typename... Args>
struct MaxType : std::integral_constant<int,
(sizeof(T)>MaxType<Args...>::value ? sizeof(T) : MaxType<Args...>::value) > 

{};

template<typename T>
struct MaxType<T> : std::integral_constant<int, sizeof(T) >{};

template < typename T, typename... List >
struct Contains : std::true_type {};

template < typename T, typename Head, typename... Rest >
struct Contains<T, Head, Rest...>
: std::conditional< std::is_same<T, Head>::value, std::true_type, Contains<T, 

Rest...>>::type{};

template < typename T >
struct Contains<T> : std::false_type{};

template<typename... Args>
struct VariantHelper;

template<typename T, typename... Args>
struct VariantHelper<T, Args...> {
inline static void Destroy(type_index id, void * data)
{
if (id == type_index(typeid(T)))
((T*) (data))->~T();
else
VariantHelper<Args...>::Destroy(id, data);
}
};

template<> struct VariantHelper<>  {
inline static void Destroy(type_index id, void * data) { }
};

template<typename... Types>
class Variant
{
typedef VariantHelper<Types...> Helper_t;
public:

Variant(void) :m_typeIndex(typeid(void))
{
}

~Variant()
{
Helper_t::Destroy(m_typeIndex, &m_data);
}

template<typename T>
bool Is()
{
return (m_typeIndex == type_index(typeid(T)));
}

template<typename T>
T& Get()
{
if (!Is<T>())
{
cout << typeid(T).name() << " is not defined. " << "current type is " << 

m_typeIndex.name() << endl;
throw std::bad_cast();
}

return *(T*) (&m_data);
}

    template <class T, 
    class = typename std::enable_if<Contains<typename 

std::remove_reference<T>::type, Types...>::value>::type>
    Variant(T&& value) : m_typeIndex(type_index(typeid(void)))
    {
        Helper_t::Destroy(m_typeIndex, &m_data);
        typedef typename std::remove_reference<T>::type U;
        new(m_data) U(std::forward<T>(value));
　　　　 m_typeIndex =type_index(typeid(T));
　 } 


 template<typename F>
	void Visit(F&& f)
	{
		　　using T = typename function_traits<F>::arg<0>::type;
		　　if (Is<T>())
			　　　　f(Get<T>());
	}
	template<typename F, typename... Rest>
	void Visit(F&& f, Rest&&... rest)
	{
		　　using T = typename function_traits<F>::arg<0>::type;
		　　if (Is<T>())
			　　　　Visit(std::forward<F>(f));
		　　else 
			　　　　Visit(std::forward<Rest>(rest)...);
	}
private: char m_data[MaxType<Types...>::value]; 
std::type_index m_typeIndex; 
};
