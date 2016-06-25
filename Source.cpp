#include <iostream>

using std::cin;

using std::cout;
using std::endl;

#include "User.h"
#include <conio.h>
#include "Manager.h"

void forUser();

int main(){
	forUser();
	return 0;
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
