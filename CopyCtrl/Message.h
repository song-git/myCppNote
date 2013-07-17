#ifndef MESSAGE_H
#define MESSAGE_H
/**
 * 消息类,一个给定的消息可以出现在多个目录中
 * 一个目录中可以有多个消息
 */
#include<set>
#include<string>

#include"Folder.h"

class Message{
	
	public:
	Message(const std::string &str = "") : contents(str) {}
	Message(const Message&);
	Message& operator=(const Message&);
	~Message();

	void save(Folder&);
	void remove(Folder&);

	private:

	std::string contents; /* 消息的内容 */
	std::set<Folder*> folders; /* 消息出现的目录 */
	void put_Msg_in_Folders(const std::set<Folder*>&); /* 将消息放到每一个目录 */ 
	void remove_Msg_from_Folders(); /* 删除成员folders中关于本消息的记录 */
};

#endif
