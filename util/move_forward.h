#include <type_traits>

template<class S>
S&& forward(typename std::remove_reference<S>::type& a) noexcept
{
	return static_cast<S&&>(a);
}

template<class T>
typename std::remove_reference<T>::type&&
move(T&& a) noexcept
{
	typedef typename std::remove_reference<T>::type&& RvalRef;
	return static_cast<RvalRef>(a); // hiding name
}
// struct X{};
// static_cast<X&&>(x);