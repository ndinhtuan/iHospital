#include "Customer.h"
#include <sstream>

using std::stringstream;

#include <fstream>

using std::ifstream;
using std::ofstream;

#include <cassert>
#include <ctime>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

#include "userLib.h"
#include "User.h"
#include <string>

Customer::Customer()
{
}


Customer::~Customer()
{
}

void Customer::getDataFromIdUsers(long long id){
	stringstream ss;
	ss << "Data/" << id << ".data";
	char fileName[30];

	ss.getline(fileName, 30);
	ifstream in(fileName, std::ios::binary);

	assert(in.is_open());

	while (!in.eof()){
		Content tmp;
		in.read((char*)&tmp, sizeof(Content));

		if ((int)in.tellg() != -1){
			if (strcmp(getCurrentTime(), tmp.currentDay) == 0){
				m_listContent.pushTail(tmp);
				//cout << tmp << endl;
			}
			else{
				return;
			}
		}
	}
}

char* Customer::getCurrentTime() const{
	time_t t = time(0);
	tm *now = new tm;
	
	localtime_s(now, &t);
	stringstream ss;
	ss << now->tm_mday << "/" << now->tm_mon + 1 << "/" << now->tm_year + 1900;

	char result[30];
	ss.getline(result, 30);
	delete now;

	return result;
}

void Customer::printList(){
	NodeContent *tmp = NULL;
	int i = 0;

	if (m_listContent.getHead() == NULL){
		cout << "Data is not inited. Waiting init data ...";
		getAllDataUsers();
		cout << "done!" << endl;
	}

	if (m_listContent.getHead() == NULL){
		cout << "Today has no data for you. We 'll update for you. Thanks ..." << endl;
		return;
	}

	for (tmp = m_listContent.getHead(); tmp != m_listContent.getTail()->next
		; tmp = tmp->next, i++){
		cout << "Content " << i << " : " << endl;
		cout << tmp->data << endl;
	}
}

//ostream& operator<<(ostream &os, const Content &content){
//	os << "Day : " << content.currentDay << endl;
//	os << "Title : " << content.title << endl;
//	os << "Content : " << content.content << endl;
//
//	return os;
//}

void Customer::getAllDataUsers(){
	ifstream in("User/User.data", std::ios::binary);

	assert(in.is_open());

	DataUser tmp;
	while (!in.eof()){
		in.read((char*)&tmp, sizeof(DataUser));

		if ((int)in.tellg() != -1){
			getDataFromIdUsers(tmp.id);
			//cout << tmp << endl;
		}
	}
}

void Customer::saveDataOfCurrentTime(){
	stringstream ss;
	char timeCurrent[30];
	strcpy_s(timeCurrent, getCurrentTimeForNameFile());
	//cout << timeCurrent;
	ss << "Customer/" << timeCurrent << ".data";

	char fileName[30];
	ss.getline(fileName, 30);
	ofstream out(fileName, std::ios::binary);

	if (m_listContent.getHead() == NULL){
		cout << "Data is not inited. Waiting init data ...";
		getAllDataUsers();
		cout << "done!" << endl;
	}

	if (m_listContent.getHead() == NULL){
		cout << "Today has no data for you. We'll update for you. Thanks." << endl;
		return;
	}

	for (NodeContent *tmp = m_listContent.getHead(); tmp != m_listContent.getTail()->next
		; tmp = tmp->next){
		out.write((char*)&(tmp->data), sizeof(Content));
	}

	cout << "Save success !" << endl;
}

void Customer::menu(){
	cout << "1. View data" << endl;
	cout << "2. Save data" << endl;
	cout << "3. Exit" << endl;

	int choice;

	do{
		cout << "Enter your choice : "; cin >> choice;
	} while (choice != 1 && choice != 2 && choice != 3);

	switch (choice){
	case 1: printList(); break;
	case 2: saveDataOfCurrentTime(); break;
	case 3: exit(0); break;
	}
}

char* Customer::getCurrentTimeForNameFile() const{
	time_t t = time(0);
	tm now;
	localtime_s(&now, &t);

	stringstream ss;
	ss << now.tm_mday << "_" << now.tm_mon + 1 << "_" << now.tm_year + 1900;

	char result[30];
	ss.getline(result, 30);

	return result;
}