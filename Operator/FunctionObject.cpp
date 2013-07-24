
// 函数对象
struct absInt{
	// public:
	int operator()(int val)
	{
		return val < 0 ? -val : val;
	}
};

// 函数对象经常用作通用算法的实参

bool GT6(const string &s)
{
	return s.size() >= 6;
}
// vector<string>::size_type wc = count_if(words.begin(),words.end(),GT6);

//函数对象
class GT_cls{
	public:
		GT_cls(size_t val = 0) : bound(val){}
		bool operator()(const string &s){ return s.size() >= bound; }
	private:
		std::string::size_type bound;
};
// 函数对象的用法
// vector<string>::size_type wc = count_if(words.begin(),words.end(),GT_cls(6));


