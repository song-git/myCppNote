
#include<iostream>
using std::cout;
using std::endl;
/* 函数对象适配器的实现  */

bool greater(int a, int b)
{
	return a > b;
}

typedef bool (*func_type)(int , int);

struct binder{
	binder(func_type f,int a) : func(f), val(a) {}
	bool operator()(int);

	func_type func;
	int val;
};

bool binder::operator()(int a)
{
	return func(a,val);
}

int main()
{
	binder b(greater,10);
	cout<<"b(100): "<<b(100)<<endl<<"b(5): "<<b(5)<<endl;
	return 0;
}
