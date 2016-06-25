#ifndef USERLIB_H
#define USERLIB_H

struct DataUser{
	long long id;
	char user[30];
	char pass[40];
};

struct InfoUser{
	char name[40];
	int age;
};

struct Content{
	char currentDay[30]; 
	char title[30];
	char content[100];
};
#endif