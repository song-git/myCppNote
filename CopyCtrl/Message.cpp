#include"Message.h"

using namespace std;
/* 拷贝构造函数 */
Message::Message(const Message &m) :
	contents(m.contents),folders(m.folders)
{
	// 在复制的时候，需要在folders中添加消息，
	// 这是默认的复制构造函数不能完成的
	put_Msg_in_Folders(folders);
}

void Message::put_Msg_in_Folders(const set<Folder*> &rhs)
{
	for(std::set<Folder*>::const_iterator beg = rhs.begin();
				beg != rhs.end(); ++beg )
	  (*beg)->addMsg(this);
}

Message& Message::operator=(const Message &rhs)
{
	if(&rhs != this){
		remove_Msg_from_Folders(); // 原来的Message被删除
		contents = rhs.contents;   // 内容被覆盖
		folders = rhs.folders;
		put_Msg_in_Folders(rhs.folders);
	}
	return *this;
}

void Message::remove_Msg_from_Folders()
{
	for(std::set<Folder*>::const_iterator beg = 
				folders.begin(); beg != folders.end(); ++beg)
	  (*beg)->remMsg(this);
}

Message::~Message()
{
	remove_Msg_from_Folders();
}
