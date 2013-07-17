/* 抑制由构造函数定义的隐式转换 explicit关键字的用法 */

#include<string>
#include<iostream>

namespace Note{

class Explicit{
	public:
	/* 每个构造函数定义一个隐式转换 */
	Explicit(std::string str):data(str){}
	/* explicit */  Explicit(int a){ data = "int"; }
	/* 如果加上explicit关键字则不能进行隐式转换 *//

	std::string data;
};

void Explicit_func(Explicit e )
{
	std::cout<<e.data<<std::endl;
	return;
}

}

int main()
{
	Note::Explicit_func(10); // 利用构造函数进行了隐式转换
	Note::Explicit_func(std::string("ABC"));
	return 0;
}
