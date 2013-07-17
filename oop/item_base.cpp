
class Item_base{
	public:
		Item_base(const std::string &book = "", double sales_price = 0.0):
			isbn(book), price(sales_price) {}
		std::string book() const {return isbn; }

		// virtual关键字表示函数将动态绑定
		virtual double net_price( std::size_t n )const {return n * price; }
		virtual ~Item_base(){}

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
	private:
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
};

double Bulk_item::net_price(size_t cnt)const
{
	if(cnt >= min_qty)
	  return cnt * (1 - discount) * price;
	else
	  return cnt * price;
}
