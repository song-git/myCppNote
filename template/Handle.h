
#ifndef HANDLE_H
#define HANDLE_H

// 范型句柄类
template<typename T> class Handle {
	public:
		Handle(T *p = 0) : ptr(p), use( new size_t(1) ) {}

		T& operator*();
		T* operator->();
		const T& operator*() const;
		const T* operator->() const;
		Handle(const Handle& h) : ptr(h.ptr), use(h.use) { ++*use; }

		Handle& operator=(const Handle&);
		~Handle(){ rem_ref(); }
	private:
		T* ptr;
		size_t *use;
		void rem_ref() { if(--*use == 0) {delete ptr; delete use;} }
};

#endif
