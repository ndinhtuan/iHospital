#ifndef MANAGERLIB_H
#define MANAGERLIB_H
#include "userLib.h"

struct Node{
	DataUser data;
	InfoUser info;
	Node *next;
};

class ListMember{
public:
	ListMember();
	void push(const DataUser &, const InfoUser &);
	void getAllMembers();
	void displayDataUser() const;
	void displayInfoUser() const;
	Node* getHead() const{
		return head;
	}
	Node* getTail() const{
		return tail;
	}
	void popWithId(long long id);
	void delAllNodes();
	void popTail();
	
private:
	Node *head;
	Node *tail;

	void getInfoFromData(const DataUser &data, InfoUser &info);
};
#endif