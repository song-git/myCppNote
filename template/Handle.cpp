#include"Handle.h"

template<typename T>
inline Handle<T>& Handle<T>::operator=(const Handle &rhs)
{
	++*rhs.use;
	rem_ref();
	ptr = rhs.ptr;
	use = rhs.use;
	return *this;
}


template<typename T>
inline T& Handle<T>::operator*()
{
	if(ptr) return *ptr;
	throw std::runtime_error("dereference of unbound Handle");
}

template<typename T>
inline T* Handle<T>::operator->()
{
	if(ptr) return ptr;
	throw std::runtime_error("access through unbound Handle");
}
