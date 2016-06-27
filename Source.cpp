#include <iostream>

using std::cin;

using std::cout;
using std::endl;

#include "User.h"
#include <conio.h>
#include "Manager.h"
#include "Customer.h"
#include <Windows.h>

void forUser();
void forCustomer();
void forManager();
void forAll();

int main(){
	forAll();

	return 0;
}

void forAll(){
	cout << "1. For User" << endl;
	cout << "2. For Customer" << endl;
	cout << "3. For Manager" << endl;
	cout << "4. Exit" << endl;
	int choice;

	do{
		cout << "Enter your choice : ";
		cin >> choice;
	} while (choice != 1 && choice != 2 && choice != 3 && choice != 4);

	system("cls");

	switch (choice){
	case 1: SetConsoleTitle("Welcome, User"); forUser(); break;
	case 2: SetConsoleTitle("Welcome, Customer"); forCustomer(); break;
	case 3: SetConsoleTitle("Welcome, Manager"); forManager(); break;
	case 4: exit(0); break;
	}
}

void forManager(){
	Manager ob;
	
	while (1){
		ob.menu();
		_getch();
		system("cls");
	}
}

void forUser(){

	User ob;

	while (1){
		if (!ob.is_User()){
			ob.menuNonMember();
			system("cls");
		}

		if (ob.is_User()){
			ob.menuOfUser();
			_getch();
		}

		system("cls");
	}
	_getch();

}

void forCustomer(){
	Customer ob;

	while (1){
		ob.menu();

		_getch();
		system("cls");
	}
}
