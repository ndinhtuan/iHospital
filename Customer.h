#pragma once
#include "CustomerLib.h"
#include <iostream>

using std::ostream;
using std::istream;

class Customer
{
	//friend ostream& operator<<(ostream &os, const Content &content);
public:
	Customer();
	~Customer();
	void getDataFromIdUsers(long long id);
	void printList();
	void getAllDataUsers();
	void saveDataOfCurrentTime();
	void menu();
private:
	ListContent m_listContent;

	char* getCurrentTime() const;
	char* getCurrentTimeForNameFile() const;
};

