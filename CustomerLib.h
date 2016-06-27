#ifndef CUSTOMERLIB_H
#define CUSTOMERLIB_H
#include "userLib.h"

struct NodeContent{
	Content data;
	NodeContent *next;

	Content& operator=(const Content &ob){
		data = ob;
	}
};

class ListContent{
public:
	ListContent();
	~ListContent();
	void pushHead(Content &content);
	void pushTail(Content &content);
	void popNth(int pos);
	int getLength() const;
	void delList();

	NodeContent* getHead() const{
		return head;
	}

	NodeContent*getTail() const{
		return tail;
	}

private:
	NodeContent *head;
	NodeContent *tail;
};

#endif