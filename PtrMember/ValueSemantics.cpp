#include<iostream>
using namespace std;
class HasPtr{
	public:
		HasPtr(const int &p, int i) : ptr(new int(p)), val(i) { cout<<"constructor!"<<endl; }
		HasPtr(const HasPtr &orig) : ptr(new int(*orig.ptr)), val(orig.val){cout<<"Copy!"<<endl; }

		HasPtr& operator=(const HasPtr&);

		~HasPtr(){delete ptr;}

	private:
		int *ptr;
		int val;
};

/* 赋值操作符，不需要分配新对象，但必须给其指针指向的对象赋值  */
HasPtr& HasPtr::operator=(const HasPtr &rhs)
{
	cout<<"operator="<<endl;
	*ptr = *rhs.ptr; // !!!!
	val = rhs.val;
	return *this;
}

int main()
{
	HasPtr p1(1,2);
	HasPtr p2 = p1;
	return  0;
}
