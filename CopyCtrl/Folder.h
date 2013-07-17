#ifndef FOLDER_H
#define FOLDER_H

#include"Message.h"

class Message;

class Folder{
	public:
		void addMsg(const Message*);
		void remMsg(const Message*);


};

#endif
