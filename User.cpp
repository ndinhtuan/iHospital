#include "User.h"
#include <cstring>
#include <fstream>

using std::ofstream;
using std::ifstream;
using std::fstream;

#include <iostream>

using std::cin;
using std::cout;
using std::endl;

#include "userLib.h"
#include <conio.h>
#include <string>

using std::string;

#include <sstream>

using std::stringstream;

#include <cassert>
#include <ctime>

#define fileID "User/lastID.txt"
#define fileUser "User/User.data"

User::User()
{
	setLastID();
	is_user = false;
}


User::~User()
{
}

long long User::getLastID() const{
	return lastID;
}

void User::setLastID(){
	char nameFile[50];
	strcpy_s(nameFile, fileID);

	ifstream in(nameFile);

	if (!in.is_open()){ 
		cout << "Cannot access file. Creating file .... done !";
		ofstream out(nameFile);
		out << 1000000;
		out.close();
	}
	else{
		in >> lastID;
		cout << "Get last id success : " << lastID << endl;
	}

	in.close();
}

void User::updateLastID() const{
	char nameFile[50];
	strcpy_s(nameFile, fileID);

	ofstream out(nameFile);

	out << lastID + 1;
}

void User::Register(int _auto){
	setLastID();

	cout << "Register member : " << endl;

	if (!_auto){

		cout << "User name : ";
		do{
			cin.getline(this->data.user, 30);
		} while (is_existed(this->data.user));

		cout << "Pass word : ";
		enterPassword(this->data.pass);
		this->data.id = lastID;

		cout << "What is your name ? ";
		cin.getline(this->info.name, 40);

		cout << "How old are you ? "; cin >> this->info.age;
	}
	else{

		stringstream ss;
		ss << lastID;
		ss.getline(this->data.user, 30);
		ss.clear();
		ss << lastID;
		ss.getline(this->data.pass, 30);
		this->data.id = lastID;

		ss.clear();
		ss << "Autobot " << lastID;
		ss.getline(this->info.name, 40);
		this->info.age = 20;

	}

	is_user = true;

	updateLastID();
	updateDataOfMembers();
	createInfoOfMember();
	createFileDataBaseOFMember();
}

void User::createFileDataBaseOFMember() const{
	stringstream ss;
	ss << "Data/" << data.id << ".data";
	char fileName[30];
	ss.getline(fileName, 30);

	ofstream out(fileName);
}

bool User::is_existed(char *userName){
	char fileName[30];
	strcpy_s(fileName, fileUser);
	ifstream in(fileName, std::ios::binary);
	
	if (!in.is_open()){
		cout << "Cannot access data of member ! Create file storage data of member ... done !" << endl;
		creatFileDataOfMember();
		return false;
	}

	DataUser tmp;
	while (!in.eof()){
		in.read((char *)&tmp, sizeof(DataUser));

		if ((int)in.tellg() != -1){
			if (strcmp(tmp.user, userName) == 0){
				cout << "User is exist. Please enter user again. Thanks" << endl;
				return true;
			}
		}
	}

	return false;
}

void User::enterPassword(char *pass){
	char c;
	int num = 0;

	do{
		c = _getch();
		if (('0' <= c && c <= '9') || ('a' <= tolower(c) && tolower(c) <= 'z')){
			cout << "*";
			pass[num] = c;
			num++;
		}
	} while (c != 13 && num <= 40);

	pass[num] = '\0';
	cout << endl;

}


ostream& operator<<(ostream &os, DataUser &ob){
	os << "Pass word : " << ob.pass << endl
		<< "User name :" << ob.user << endl
		<< "ID : " << ob.id << endl;
	return os;
}

ostream& operator<<(ostream &os, InfoUser &ob){
	os << "Name : " << ob.name << endl
		<< "Age : " << ob.age << endl;

	return os;
}

void User::creatFileDataOfMember(){
	char fileName[40];
	strcpy_s(fileName, fileUser);

	ofstream out;

	do{
		out.open(fileName);
	} while (!out.is_open());
}

void User::createInfoOfMember() const{
	stringstream ss;
	ss << "User/";
	ss << this->data.id;
	ss << ".info";

	char fileName[40];
	ss.getline(fileName, 40);

	ofstream out(fileName, std::ios::binary);
	out.write((char *)&info, sizeof(InfoUser));
}

void User::updateDataOfMembers() const{
	char fileName[40];
	strcpy_s(fileName, fileUser);

	ofstream out(fileName, std::ios::app | std::ios::binary);
	out.write((char *)&(this->data), sizeof(DataUser));
}

void User::showInfo() const{
	stringstream ss;
	ss << "User/";
	ss << this->data.id;
	ss << ".info";

	char fileName[40];
	ss.getline(fileName, 40);

	InfoUser tmp;
	ifstream in(fileName, std::ios::binary);
	in.read((char *)&tmp, sizeof(InfoUser));

	cout << "Name : " << tmp.name << endl
		<< "Age  : " << tmp.age << endl;

}

void User::createDataBase() const{
	stringstream ss;
	ss << "Data/";
	ss << this->data.id << ".info";

	char fileName[40];
	ss.getline(fileName, 40);

	ifstream in(fileName);

	if (in.is_open()){
		cout << "Data of " << this->data.id << " has created !" << endl;
		in.close();
		return;
	}
	else{
		ofstream out(fileName);
	}

	in.close();
}

void User::login(){
	char c = 0;

	do{
		cout << "Enter username : ";
		cin.getline(data.user, 30);
		cout << "Enter password : ";
		enterPassword(data.pass);

		if (login_success(data)){
			cout << "Login success !" << endl;
			is_user = true;
		}
		else{
			cout << "Not successing .Press Enter if you want to login again." << endl;
			c = _getch();
		}
	} while (c == 13 && !is_user);

}

bool User::login_success(DataUser &_data){
	ifstream in(fileUser, std::ios::binary);

	while (!in.eof()){
		DataUser tmp;
		in.read((char*)&tmp, sizeof(DataUser));

		if ((int)in.tellg() != -1){
			if ((strcmp(_data.user, tmp.user) == 0) && (strcmp(_data.pass, tmp.pass) == 0)){
				_data.id = tmp.id;
				getInfoAfterLoginSuccess();
				cout << info;
				return true;
			}
		}
	}

	return false;
}

void User::getInfoAfterLoginSuccess(){
	stringstream ss;
	ss << "User/" << data.id << ".info";

	char fileName[30];
	ss.getline(fileName, 30);

	ifstream in(fileName, std::ios::binary);
	in.read((char*)&info, sizeof(InfoUser));
}

void User::editPass(){
	char currentPass[40];
	cout << "Enter current password : ";
	enterPassword(currentPass);

	if (strcmp(currentPass, data.pass) == 0){
		char newPass[40];
		char againPass[40];

		do{
			cout << "New pass : ";
			enterPassword(newPass);
			cout << "Please enter pass again (Like new pass) : ";
			enterPassword(againPass);
		} while (strcmp(newPass, againPass) != 0);

		strcpy_s(data.pass, newPass);
		fstream in(fileUser, std::ios::binary | std::ios::in | std::ios::out);
		DataUser tmp;

		while (!in.eof()){
			in.read((char*)&tmp, sizeof(DataUser));

			if ((int)in.tellg() != -1){
				if (strcmp(tmp.user, data.user) == 0){
					cout << "Found user to change password !" << endl;
					in.seekg(-(int)sizeof(DataUser), std::ios::cur);
					in.write((char*)&data, sizeof(DataUser));
					cout << "Edit password success !" << endl;

					return;
				}
			}
		}

	}
	else{
		cout << "Current password is wrong !" << endl;
	}
}

void User::editInfo(){
	assert(is_user);

	cout << "Current Your Information : " << endl;
	cout << "Name : "; cout << info.name << endl;
	cout << "Age  : "; cout << info.age << endl;

	char choice;
	cout << "Do you want to chance your information ? <Press Enter>" << endl;
	choice = _getch();

	if (choice != 13){
		return;
	}

	cin.ignore();
	cout << "Enter new name : "; cin.getline(info.name, 40);
	cout << "Enter new age  : "; cin >> info.age;

	cout << "Edit information success ! " << endl;
}

void User::menuNonMember(){
	assert(!is_user);

	cout << "1. Register" << endl;
	cout << "2. Login" << endl;
	cout << "3. Exit" << endl;

	int choice;
	do{
		cout << "Enter your choice : "; cin >> choice;
	} while (choice != 1 && choice != 2 && choice != 3);

	cin.ignore();

	switch (choice){
	case 1: Register(NOT_AUTO); break;
	case 2: login(); break;
	case 3: exit(0); break;
	}
}

char* User::getCurrentTime() const{
	time_t t = time(0);

	tm *now = new tm;
	localtime_s(now, &t);
	int year = now->tm_year + 1900;
	int month = now->tm_mon + 1;
	int day = now->tm_mday;

	stringstream ss;
	ss << day << "/" << month << "/" << year;

	char result[30];
	ss.getline(result, 30);
	delete now;

	return result;
}

//---------------------------- Work with database file of doctor ----------------------
ostream& operator<<(ostream &os, const Content &ob){
	os << "Day : " << ob.currentDay << endl;
	os << "Title : " << ob.title << endl;
	os << "Content : " << ob.content << endl;

	return os;
}

void User::updateDataBase(){
	if (!is_user){
		cout << "You are not user ! Please register to be member !" << endl;
		return;
	}

	cout << "Enter title : "; 
	cin.getline(content.title, 30);
	cout << "Enter content : ";
	cin.getline(content.content, 100);

	strcpy_s(content.currentDay, getCurrentTime());
	stringstream ss;
	ss << "Data/" << data.id << ".data";
	char fileName[30];
	ss.getline(fileName, 30);

	ofstream out(fileName, std::ios::app);

	if (!out.is_open()){
		cout << "Cannot access file database!" << endl;
		return;
	}
	else{
		out.seekp(0, std::ios::beg);
		out.write((char*)&content, sizeof(Content));
	}
		
}

void User::menuOfUser(){
	assert(is_user);

	cout << "1. Edit pass" << endl;
	cout << "2. Update database" << endl;
	cout << "3. Edit Information" << endl;
	cout << "4. Show Information" << endl;
	cout << "5. Show database" << endl;
	cout << "6. Exit" << endl;

	int choice;
	do{
		cout << "Your choice : "; cin >> choice;
	} while (choice != 1 && choice != 2 && choice != 3 && choice != 4 
		     && choice != 5 && choice != 6);

	switch (choice){
	case 1: editPass(); break;
	case 2: cin.ignore();  updateDataBase(); cout << content;  break;
	case 3: editInfo(); break;
	case 4: cout << info; break;
	case 5: showDataBase();  break;
	case 6: is_user = false; cout << "Exit success !"; break;
	}
}

void User::showDataBase(){
	stringstream ss;
	ss << "Data/" << data.id << ".data";

	char fileName[30];
	ss.getline(fileName, 30);
	ifstream in(fileName, std::ios::binary);

	if (!in.is_open()){
		cout << "Cannot access database of user, who has id : " << data.id << endl;
		return;
	}

	Content tmp;
	int num = 0;

	while (!in.eof()){
		
		in.read((char*)&tmp, sizeof(Content));
		
		if ((int)in.tellg() != -1){

			num++;

			cout << "Content " << num << " : " << endl;
			cout << tmp << endl;
		}
	}

	if (!num){
		cout << "No content !" << endl;
	}
}