#include "CustomerLib.h"
#include <iostream>
#include "User.h"

ListContent::~ListContent(){
	delList();
}

ListContent::ListContent(){
	head = tail = NULL;
}

void ListContent::pushHead(Content &content){
	NodeContent *tmp = new NodeContent;
	tmp->data = content;
	tmp->next = NULL;

	if (head == NULL){
		head = tail = tmp;
	}
	else{
		tmp->next = head;
		head = tmp;
	}
}

void ListContent::pushTail(Content &content){
	NodeContent *tmp = new NodeContent;
	tmp->data = content;
	tmp->next = NULL;

	if (head == NULL){
		head = tail = tmp;
	}
	else{
		tail->next = tmp;
		tail = tail->next;
	}
}

void ListContent::popNth(int pos){
	if (pos <= 0){

	}
	else{

		if (pos == 1){
			NodeContent *tmp = head;
			head = head->next;

			delete tmp;
		}
		else{
			NodeContent *tmp = NULL;
			int i;

			for (tmp = head, i = 1; i <= pos - 2; tmp = tmp->next){

			}

			NodeContent *tmpNode = tmp->next->next;
			delete tmp->next;

			tmp->next = tmpNode;

		}

	}
}

int ListContent::getLength() const{
	int len = 0;
	NodeContent *tmp = head;

	while (tmp != tail->next){
		len++;
		tmp = tmp->next;
	}

	return len;
}

void ListContent::delList(){
	if (head == NULL){
		return;
	}

	NodeContent *tmp = head;
	int i = 0;

	while (tmp != NULL){ // ko dung dc tmp != tail->next
		head = head->next;

		delete tmp;
		tmp = head;
	}

}