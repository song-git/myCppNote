/* C++中的可变数据成员 */

namespace Note
{

class Mutable{
	public:

	/* const成员函数可以修改mutable变量的值 */
	inline int cfunc(void) const {data_m++;return data_m}// data++;}
	
	inline void func(void){data_m++;data++;}
	private:

	mutable int data_m;
	int data;
};


}

int main()
{
	Note::Mutable m;

	return 0;
}
