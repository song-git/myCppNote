
/*
   在文件中查找单词的出现位置,有不同的查找语法
   演示面向对象的设计方法
 */

#ifndef QUERY_BASE_H
#define QUERY_BASE_H

#include<string>
#include<set>
#include<map>
#include<iostream>

// 保存文本的每一行以及各单词与所在行号的对应
class TextQuery {
	public:
		typedef std::vector<std::string>::size_type line_no;

		void read_file(std::ifstream &is)
		{ store_file(is);build_map(); }
		std::set<line_no> run_query(const std::string&) const;
		std::string text_line(line_no) const;
	private:
		void store_file(std::ifstream& );
		void build_map();
		std::vector<std::string> lines_of_text;
		std::map(std::string, std::set<line_no>) word_map;
};

/*
   Abstract class for query operation
 */
class Query_base {
	public:
		friend class Query;
	protected:
		typedef TextQuery::line_no line_no;
		virtual ~Query_base() {}
	private:
		// return the set of lines that this Query matchs
		virtual std::set<line_no> eval(const TextQuery&) const = 0;
		// prints the query
		virtual std::ostream& display(std::ostream& = std::cout) const = 0;
};


class Query{
	private:
		friend Query operator~(const Query &);
		friend Query operator|(const Query&, const Query&);
		friend Query operator&(const Query&, const Query&);
	public:
		Query(const std::string&);
		Query(const Query &c) : q(c.q), use(c.use){++*use;}
		~Query(){decr_use();}
		Query& operator=(const Query&);
		std::set<TextQuery::line_no>
			eval(const TextQuery &t) const {return q->eval(t);}

		std::ostream& display(std::ostream &os) const 
		{return q->display(os);}

	private:
		Query(Query_base *query) : q(query), 
		use(new std::size_t(1)) {}

		Query_base *q;
		std::size_t *use;
		void decr_use()
		{ if(--*use == 0) delete q; delete use; }
};

class WordQuery : public Query_base{
	private:
		friend class Query;
		WordQuery(const std::string &s) : query_word(s){}
		std::set<line_no> eval(const TextQuery &t) const
		{return t.run_query(query_word); }
		std::ostream& display(std::ostream &os) const
		{ return os << query_word; }

		std::string query_word;
};

class NotQuery : public Query_base {
	private:
		friend Query operator~(const Query &);
		NotQuery(Query q) : query(q){}

		std::set<line_no> eval(const TextQuery&)const;
		std::ostream& display(std::ostream &os) const;
		{return os << "~("<< query << ")"; }

		const Query query;
};

class BinaryQuery : public Query_base {
	protected:
		BinaryQuery(Query left, Query right, std::string op):
			lhs(left), rhs(right), oper(op){}
		std::ostream& display(std::ostream &os) const
		{ return os << "(" << lhs << " " << oper << " "
			<< rhs << ")"; }
		const Query lhs,rhs;
		const std::string oper;
};

class AndQuery : public BinaryQuery{
	private:
		friend Query operator&(const Query&,const Query&);
		AndQuery(Query left, Query right) :
			BinaryQuery(left,right,"&") {}
		std::set<line_no> eval(const TextQuery&) const;
};

class OrQuery : public BinaryQuery{
	private:
		friend Query operator|(const Query&, const Query&);
		OrQuery(Query left, Query right) :
			BinaryQuery(left,right,"|") {}
		std::set<line_no> eval(const TextQuery&) const;
};

#endif
