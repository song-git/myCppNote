

class CheckedPtr{
	public:
		CheckedPtr(int *b, int *e):beg(b), end(e), curr(b){}
		CheckedPtr& operator++(); // prefix operators
		CheckedPtr& operator--(); // 返回的是改变后对象的引用

		CheckedPtr operator++(int); // postfix operators
		CheckedPtr operator--(int); // 一个额外的int型参，
		// 返回的是对象未改变之前的一个副本
	private:
		int *beg;
		int *end;
		int *curr;
};

CheckedPtr& CheckedPtr::operator++()
{
	if(curr == end)
	  throw out_of_range("increment past the end of CheckedPtr");
	++curr;
	return *this;
}

CheckedPtr& CheckedPtr::operator--()
{
	if(curr == beg)
	  throw out_of_range("decrement past the beginning of CheckedPtr");
	--curr;
	return *this;
}

CheckedPtr CheckedPtr::operator++(int)
{
	CheckedPtr ret(*this);
	++*this;
	return ret;
}

CheckedPtr CheckedPtr::operator--(int)
{
	CheckedPtr ret(*this);
	--*this;
	return ret;
}
