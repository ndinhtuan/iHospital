#include "Manager.h"
#include "User.h"
#include "userLib.h"
#include <fstream>

using std::ofstream;
using std::ifstream;

#include <sstream>

using std::stringstream;

#define fileUser "User/User.data"
#define fileID "User/lastID.txt"

Manager::Manager()
{
	getData();
}


Manager::~Manager()
{
}

void Manager::delUser(){
	long long idTarget;
	cout << "Enter id, which you want to delete .";
	cin >> idTarget;
	
	if (id_is_existed(idTarget)){

		//ofstream out("User/User.data", std::ios::binary);

		list.popWithId(idTarget);
		delIdInfo(idTarget);
		delIdData(idTarget);

		ofstream out("User/User.data", std::ios::binary);
		for (Node *tmp = list.getHead(); tmp != list.getTail()->next; tmp = tmp->next){
			out.write((char*)&(tmp->data), sizeof(DataUser));
		}
		
		cout << "Delete " << idTarget << " success !" << endl;
	}
	else{
		cout << "ID " << idTarget << " is not existed." << endl;
	}
}

bool Manager::id_is_existed(long long id){
	if (list.getHead() == NULL){
		cout << "List has no member or you haven't got data from database yet. \nWaiting system get data for you ..." << endl;
		getData();

		if (list.getHead() == NULL){
			cout << "Your list has no member." << endl;
			return false;
		}
	}
	else{
		for (Node *tmp = list.getHead(); tmp != list.getTail()->next; tmp = tmp->next){
			if (id == tmp->data.id){
				return true;
			}
		}
	}

	return false;
}

void Manager::delIdInfo(long long id) const{
	stringstream ss;
	ss << "User/" << id << ".info";

	char fileName[30];
	ss.getline(fileName, 30);

	remove(fileName);
}

void Manager::delIdData(long long id) const{
	stringstream ss;
	ss << "Data/" << id << ".data";

	char fileName[30];
	ss.getline(fileName, 30);

	remove(fileName);
}

void Manager::delAll(){
	if (list.getHead() == NULL){
		cout << "List has no member !" << endl;
		return;
	}

	for (Node *tmpNode = list.getHead(); tmpNode != list.getTail()->next
		 ; tmpNode = tmpNode->next){

		cout << "Removing user has id : " << tmpNode->data.id << " ... ";
		delIdInfo(tmpNode->data.id);
		delIdData(tmpNode->data.id);
		cout << "done!" << endl;
		//list.popWithId(tmpNode->data.id);
	}
	list.delAllNodes();

	ofstream out(fileUser);
}

void Manager::editLastID() const{
	ifstream in(fileID);
	int lastId;
	in >> lastId;
	in.close();

	cout << "Current last id : " << lastId << endl;
	
	int newId;
	do{
		cout << "Enter new id : "; cin >> newId;
	} while (15000000 > newId);

	ofstream out(fileID);
	out << newId;
}

void Manager::createDataForUsers() const{
	if (list.getHead() == NULL){
		cout << "List has no member !" << endl;
		return;
	}

	for (Node *tmpNode = list.getHead(); tmpNode != list.getTail()->next; tmpNode = tmpNode->next){
		stringstream ss;
		ss << "Data/" << tmpNode->data.id << ".data";
		char fileName[40];
		ss.getline(fileName, 40);

		ofstream out(fileName, std::ios::app);
		out.close();
	}
}

void Manager::menu(){
	cout << "1. Display User" << endl;
	cout << "2. Creat Data For All Of Users" << endl;
	cout << "3. Edit Last ID" << endl;
	cout << "4. Delete User" << endl;
	cout << "5. Delete All of Users" << endl;
	cout << "6. Exit" << endl;

	int choice;

	do
	{
		cout << "Enter your choice : "; cin >> choice;
	} while (choice != 1 && choice != 2 && choice != 3
		     && choice != 4 && choice != 5 && choice != 6);

	switch (choice){
	case 1: display(); break;
	case 2: createDataForUsers(); break;
	case 3: editLastID(); break;
	case 4: delUser(); break;
	case 5: delAll(); break;
	case 6: exit(0); break;
	}
}