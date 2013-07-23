
#include"Query_base.h"

using namespace std;

void TextQuery::store_file(ifstream &is)
{
	string textline;
	while( getline(is,textline) )
	  lines_of_text.push_back(text_line);
}

void TextQuery::build_map()
{
	for(line_no line_num = 0;
				line_num != lines_of_text.size();
				++line_num )
	{
		istringstream line(lines_of_text[line_num]);
		string word;
		while( line >> word )
		  word_map[word].insert(line_num);
	}
}

set<TextQuery::line_no> 
TextQuery::run_query(const string &query_word) const
{
	map< string,set<line_no> >::const_iterator loc
		= word_map.find(query_word);
	if(loc == word_map.end())
	  return set<line_no>();
	else
	  return loc->second;
}

string TextQuery::text_line(line_no line)const
{
	if(line < lines_of_text.size())
	  return lines_of_text[line];
	throw std::out_of_range("line number out of range");
}

// 一下几个友元函数使用了私有的构造函数进行隐式转换
inline Query operator&(const Query& lhs, const Query& rhs)
{
	return new AndQuery(lhs,rhs);
}

inline Query operator|(const Query& lhs, const Query& rhs)
{
	return new OrQuery(lhs,rhs);
}

inline Query operator~(const Query& oper)
{
	return new NotQuery(oper);
}

inline std::ostream& 
operator<<(std::ostream& os,const Query &q)
{
	return q.display(os);
}

set<TextQuery::line_no> 
OrQuery::eval(const TextQuery& file) const
{
	set<line_no> right = rhs.eval(file),
		ret_lines = lhs.eval(file);
	ret_lines.insert(right.begin(),right.end());
	return ret_lines;
}

set<TextQuery::line_no> 
AndQuery::eval(const TextQuery& file) const
{
	set<line_no> left = lhs.eval(file),
		right = rhs.eval(file);
	set<line_no> ret_lines;
	set_intersection(left.begin(),left.end(),
				right.begin(),right.end(),
				inserter(ret_lines,ret_lines.begin()));
	return ret_lines;

}

set<TextQuery::line_no> 
NotQuery::eval(const TextQuery& file) const 
{
	set<TextQuery::line_no> has_val = query.eval(file);
	set<line_no> ret_lines;
	for(TextQuery::line_no n = 0; n != file.size(); ++n)
	  ret_lines.insert(n);
	return ret_lines;
}
