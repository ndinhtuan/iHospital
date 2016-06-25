#pragma once
#include "ManagerLib.h"
#include <iostream>

using std::cout;
using std::cin;
using std::endl;

class Manager
{
public:
	Manager();
	~Manager();
	void getData(){
		list.getAllMembers();
	}
	void display(){
		if (list.getHead() == NULL){
			cout << "Data of list hasn't set up or Your system has no member. \nWaiting system get data from database for you ...." << endl;
			getData();

			if (list.getHead() == NULL){
				cout << "Your system has no member from database. " << endl;
				return;
			}
		}
		list.displayDataUser();
		cout << "+++++++++++++++++++++" << endl;
		list.displayInfoUser();
	}
	void delUser();
	void delAll();
	void editLastID() const;
	void createDataForUsers() const;
private:
	ListMember list;

	bool id_is_existed(long long id);
	void delIdInfo(long long id) const;
	void delIdData(long long id) const;
};

