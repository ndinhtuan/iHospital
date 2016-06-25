#ifndef USER_H
#define USER_H
#include "userLib.h"
#include <iostream>

using std::ostream;
using std::istream; 
using std::endl;

#define AUTO 1
#define NOT_AUTO 0

class User
{
	friend ostream& operator<<(ostream &os, DataUser &ob);
	friend ostream& operator<<(ostream &os, InfoUser &ob);
	friend ostream& operator<<(ostream &os, const Content &ob);
public:
	User();
	~User();
	long long getLastID() const;
	void updateLastID() const;
	void setLastID();
	void Register(int _auto);
	void login(); // set up is_user 
	DataUser getData() const{
		return data;
	}
	void createInfoOfMember() const;
	InfoUser getInfo() const{
		return info;
	}
	void showInfo() const;
	void createDataBase() const;
	void updateDataBase();
	void editPass();
	void editInfo();
	void getInfoAfterLoginSuccess(); // for login()
	bool is_User() const{
		return is_user;
	}
	// DONE
	void menuOfUser();
	void menuNonMember();
	void showDataBase();
private:
	long long lastID;
	DataUser data;
	InfoUser info;
	Content content;

	bool is_user; // is used attributed of system, with registered member or login success

	// this function check whether userName is existed in User.data 
	bool is_existed(char *userName);

	// this function enter pass word
	void enterPassword(char *pass);
	void creatFileDataOfMember();
	void updateDataOfMembers() const;

	// create file data base for member, which save data for doctors
	void createFileDataBaseOFMember() const;

	// check login success in User.data
	bool login_success(DataUser &);

	char* getCurrentTime() const;
};

#endif