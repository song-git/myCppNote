
// general skeleton of the overloaded output operator
ostream& operator<< (ostream& os, const ClassType &object)
{
	// os << .... 
	return os;
}

istream& operator>>(istream& in,ClassType &object)
{
	// in>> ....
	if(in){
		// 判断istream的状态看是否发生错误
	}
	return in;
}

ClassType& ClassType::operator+=(const ClassType& rhs)
{
	// ...
	return *this;
}
