/* 具有指针成员的类一般需要定义复制控制成员 */
/* 1 复制构造函数 2 赋值操作符 3 析构函数  */

// 使用计数类，定义智能指针

class U_Ptr{
	friend class HasPtr;
	int *ip;
	size_t use;
	U_Ptr(int* p) : ip(p),use(1){}
	~U_Ptr(){delete ip}
};


class HasPtr{
	public:
		HasPtr(int *p, int i) : ptr(new U_Ptr(p)),val(i){}
		
		/* 拷贝构造函数 */
		HasPtr(const HasPtr &orig):
			ptr(orig.ptr),val(orig.val){ ++ptr->use; }
		/* 赋值操作符 */
		HasPtr& operator=(const HasPtr& );

		/* 析构函数  */
		~HasPtr(){ if(--ptr->use == 0) delete ptr; }
	private:
		U_Ptr *ptr;
		int val;
};

HasPtr& HasPtr::operator=(const HasPtr &rhs)
{
	/* 防止自身赋值 */
	++rhs.ptr->use;
	if(--ptr->use == 0)
	  delete ptr;
	ptr = rhs.ptr;
	val = rhs.val;

	return *this;
}
