/*
 * 重载箭头操作符：
 * 1 point->action()  即 (point->action)()
 * 2 point->action: 如果point是一个指针类型，则运算结果指向名为action的成员
 *					如果point是一个类的对象，则相当于调用 point.operator->()->action
 *					[CS_IPT] 所以，当重载的箭头运算返回对象或者指针的话，继续进行上面的判断
 */

#include<iostream>

class Arrow
{
	public:
	Arrow* operator->();
	int value;
};

Arrow* Arrow::operator->()
{
	return this;
}


int main()
{
	Arrow a;
	a.value = 100;
	std::cout<<a->value<<std::endl;
	return 0;
}
