#include<string>
#include<stdexcept>
#include<set>
using namespace std;


class Item_base{
	public:
		Item_base(const std::string &book = "", double sales_price = 0.0):
			isbn(book), price(sales_price) {}
		std::string book() const {return isbn; }

		// virtual关键字表示函数将动态绑定
		virtual double net_price( std::size_t n )const {return n * price; }
		virtual ~Item_base(){}

		// clone函数体现了虚函数的一个规则：参见note第7条
		// 为了支持句柄类
		virtual Item_base* clone() const {
			return new Item_base(*this); 
		}
	private:
		std::string isbn;
	protected:
		double price;
};

class Disc_item : public Item_base {
	public:
		Disc_item(const std::string& book = "", double sales_price = 0.0,
					std::size_t qty = 0, double disc_rate = 0.0) :
			Item_base(book,sales_price), // 初始化基类部分的方法
			quantity(qty),discount(disc_rate) {}

		virtual Disc_item* clone() const {
			return new Disc_item(*this);
		}
	protected:
		std::size_t quantity;
		double discount;

};

// Bulk_item 有一个直接基类 Disc_item 和一个间接基类 Item_base
// 只能初始化直接基类，通过直接基类初始化间接基类
class Bulk_item : public Disc_item{
	public:
		Bulk_item(const std::string& book = "",
					double sales_price = 0.0, 
					std::size_t qty = 0, 
					double disc_rate = 0.0) : Disc_item(book,sales_price,qty,disc_rate) {}
		// 可以在前面加上virtual,但无论如何该函数都动态绑定
		double net_price(std::size_t)const; // 重新定义的函数

		virtual Bulk_item* clone() const {
			return new Bulk_item(*this);
		}
};

double Bulk_item::net_price(size_t cnt)const
{
	if(cnt >= quantity)
	  return cnt * (1 - discount) * price;
	else
	  return cnt * price;
}

// 指针型句柄类,使用计数式复制控制
class Sales_item {
	public:
		Sales_item() : p(0), use(new std::size_t(1)) {}

		// 该构造函数：不知道参数的实际类型
		// 解决办法：添加clone函数
		Sales_item(const Item_base& );
		
		Sales_item(const Sales_item& i) : p(i.p), use(i.use) { ++*use; }

		~Sales_item() { decr_use(); }
		Sales_item& operator=(const Sales_item&);

		const Item_base* operator->() const { 
			if(p) 
			  return p; 
			else 
			  throw std::logic_error("unbound Sales_item");
		}

		const Item_base& operator*() const {
			if(p)
			  return *p;
			else
			  throw std::logic_error("unbound Sales_item");
		}
	private:
		Item_base *p;
		std::size_t *use;

		void decr_use()
		{
			if(--*use == 0){
				delete p;
				delete use;
			}
		}
};

/* 调用形参的虚函数clone来产生实际对象的副本,并初始化计数 */
Sales_item::Sales_item(const Item_base &item) : p(item.clone()), use(new std::size_t(1)){}

Sales_item& Sales_item::operator=(const Sales_item &rhs)
{
	++*rhs.use;
	decr_use();
	p = rhs.p;
	use = rhs.use;
	return *this;
}

inline bool compare(const Sales_item &lhs, const Sales_item &rhs)
{
	return lhs->book() < rhs->book();
}

class Basket {
	typedef bool (*Comp) (const Sales_item&, const Sales_item&);
	public:
	typedef std::multiset<Sales_item,Comp> set_type;
	typedef set_type::size_type size_type;
	typedef set_type::const_iterator const_iter;

	Basket() : items(compare) {}
	void add_item(const Sales_item &item) { items.insert(item); }
	size_type size(const Sales_item &i) const { return items.count(i); }
	double total() const;
	private:
	set_type items;
};

double Basket::total() const 
{
	double sm = 0.0;
	for(const_iter iter = items.begin(); 
				iter != items.end(); 
				iter = items.upper_bound(*iter) ) // 注意，该表达式依赖于multiset中的元素是排序的
	{
		// 重载的箭头操作符返回Item_base*类型
		sum += (*iter)->net_price(items.count(*iter));
	}
	return sum;
}

int main()
{
	return 0;
}
