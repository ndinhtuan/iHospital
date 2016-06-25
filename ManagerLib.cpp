#include "ManagerLib.h"
#include <cstring>

#define fileUser "User/User.data"

#include <fstream>

using std::ifstream;
using std::ofstream;

#include <iostream>

using std::cin;
using std::cout;
using std::endl;

#include <sstream>

using std::stringstream;

ListMember::ListMember(){
	head = tail = nullptr;
}

void ListMember::push(const DataUser &data, const InfoUser &info){
	Node *tmp = new Node;
	tmp->data = data;
	tmp->info = info;
	tmp->next = nullptr;

	if (head == nullptr){
		head = tail = tmp;
	}
	else{
		tail->next = tmp;
		tail = tail->next;
	}
}

void ListMember::getAllMembers(){
	char fileName[40];
	strcpy_s(fileName, fileUser);

	ifstream in(fileName);

	if (!in.is_open()){
		cout << "Cannot access file of data members. Try again !" << endl;
		return;
	}

	DataUser tmpData;
	InfoUser tmpInfo;
	while (!in.eof()){
		in.read((char *)&tmpData, sizeof(DataUser));

		if ((int)in.tellg() != -1){
			getInfoFromData(tmpData, tmpInfo);
			push(tmpData, tmpInfo);
		}
	}
}

void ListMember::getInfoFromData(const DataUser &data, InfoUser &info){
	stringstream ss;
	ss << "User/" << data.id << ".info";

	char fileName[30];
	ss.getline(fileName, 30);
	ifstream in(fileName, std::ios::binary);

	if (!in.is_open()){
		cout << "Cannot access file of user, who has id : " << data.id << endl;
		return;
	}
	in.read((char*)&info, sizeof(InfoUser));
}

void ListMember::displayDataUser() const{
	cout << "Data of users : " << endl;
	int num = 1;
	
	for (Node *tmp = head; tmp != tail->next; tmp = tmp->next){

		cout << "User " << num++ << " : " << endl;

		cout << tmp->data.id << endl
			<< tmp->data.user << endl
			<< tmp->data.pass << endl;
		cout << "----------------------------" << endl;
	}
}

void ListMember::displayInfoUser() const{
	cout << "Info of users : " << endl;
	int num = 1;

	for (Node *tmp = head; tmp != tail->next; tmp = tmp->next){

		cout << "User " << num++ << " : " << endl;

		cout << tmp->info.name << endl
			<< tmp->info.age << endl;
		cout << "----------------------------" << endl;
	}
}

void ListMember::popWithId(long long id){
	if (head->data.id == id){
		Node *tmp = head;
		head = head->next;
		delete tmp;
	}
	else{
		for (Node *tmpNode = head; tmpNode != tail; tmpNode = tmpNode->next){
			if (tmpNode->next != tail /*&& tmpNode->next->data.id == id*/){

				if (tmpNode->next->data.id == id){
					Node *temp = tmpNode->next;
					tmpNode->next = temp->next;
					delete temp;

					return;
				}
				
			}
			else{
				if (tmpNode->next == tail){
					tail = tmpNode;
					delete tail->next;
					tail->next = NULL;

					return;
				}
			}
		}
	}
}

void ListMember::delAllNodes(){
	Node *tmpNode = head;

	while (tmpNode != tail->next && tmpNode != NULL){
		Node *tmp = tmpNode;
		tmpNode = tmpNode->next;

		delete tmp;
	}

	head = tail = NULL;
}

void ListMember::popTail(){
	if (tail != NULL){

		Node *tmpNode;
		for (tmpNode = head; tmpNode->next != tail; tmpNode = tmpNode->next){};

		delete tmpNode->next;
		
		tail = tmpNode;
		tail->next = NULL;
	}
}