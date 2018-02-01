#include "Libraries.h"
#include "Nodes.h"

Node *head;//head of the list

//"made up" constructor of the list which stores
//characters used to do some math stuff
Node* elem_Init_For_Sign(const char sign) {

	Node *ptr = (Node*)malloc(sizeof(Node));
	if (!ptr) {

		perror("ptr");
	}
	ptr->value = NULL;
	ptr->sign = sign;
	ptr->next = NULL;
	ptr->prev = NULL;
	return ptr;
}
//"made up" constructor of the list which stores
//numbers in double to perform math
Node* elem_Init_For_Num(const double var) {

	Node *ptr = (Node*)malloc(sizeof(Node));
	if (!ptr) {

		perror("ptr");
	}
	ptr->sign = '\0';
	ptr->value = var;
	ptr->next = NULL;
	ptr->prev = NULL;
	return ptr;
}


//////////////////////////////////////////////////inserting to the list
//inserting character at the beginning of the list
/*
void insertNode(Node *ptr) {
if (!head) {
head = ptr;
return;
}
head->prev = ptr;
ptr->next = head;
head = ptr;
}
*/
//THOSE TWO WAYS ARE GOOD IT IS THE USER DECISION,
//IF HE WANTS TO ALLOCATE NODE AT THE BEGINNING OR END
//OF THE LIST
//inserting character at the end of the list


void insertNode(Node *ptr) {
	if (!head) { head = ptr; return; }
	//temporary pointer, not in the stack whatsoever
	Node *temp = head;
	//going through the whole list, to the end
	while (temp->next) { temp = temp->next; }
	//adding the node to the end
	temp->next = ptr;
	ptr->prev = temp;
}
