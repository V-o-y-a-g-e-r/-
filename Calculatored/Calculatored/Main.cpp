#define _CRT_SECURE_NO_WARNINGS
#include "Libraries.h"
#include "Nodes.h"

extern Node *head;//head of the list

		   //prototypes of functions
void getLine(void);
void doMath(void);
void checkBrackets(void);
void printResult(void);
void insertNode(Node*);//insterting node to the list
void addF(Node*&);//math functions
void subF(Node*&);//for simple examples
void multF(Node*&);//as a parameter
void divF(Node*&);//functions gets
void powF(Node*&);//temp pointer to the operand


//main function
int main(void) {

	head = NULL;

	getLine();
	doMath();

	printResult();

	system("PAUSE");
	return 0;
}

//////print the result of the expression
void printResult(void) {
	if (!head) {
		printf("You entered wrong expression.\n");
		printf("Please, next time double check the input.\n");
		return;
	}
	Node *ptr = head;
	while (ptr->next->next) { ptr = ptr->next; }
	printf("The result is: %f\n", ptr->value);
}
//math operations on the list which represents entire expression
void doMath(void) {
	//defining temp pointer to go through the list
	Node *temp = head;
	//program checks for extra parenthesis
	checkBrackets();
	//first, program checks if there are operators in higher state
	while (temp) {

		if (temp->sign == '^') {
			powF(temp);
		}
		//separate power loop
		else if (temp->sign == '*') {
			multF(temp);
		}

		else if (temp->sign == '/') {
			divF(temp);
		}
		temp = temp->next;
	}
	temp = head;
	//now, program checks for lower - state operators
	while (temp) {

		if (temp->sign == '+') {
			addF(temp);
		}

		else if (temp->sign == '-') {
			subF(temp);
		}

		temp = temp->next;
	}
}
//////////////math functions/////////////////////
void addF(Node *&temp) {
	double result;

	result = temp->prev->value + temp->next->value;
	Node *ptr = NULL;

	ptr = elem_Init_For_Num(result);
	if (head == temp->prev) head = ptr;
	else {
		temp->prev->prev->next = ptr;
	}
	ptr->next = temp->next->next;
	temp->next->next->prev = ptr;

	temp = ptr;
}

void subF(Node *&temp) {
	double result;

	result = temp->prev->value - temp->next->value;
	Node *ptr = NULL;

	ptr = elem_Init_For_Num(result);
	if (head == temp->prev) head = ptr;
	else {
		temp->prev->prev->next = ptr;
	}
	ptr->next = temp->next->next;
	temp->next->next->prev = ptr;

	temp = ptr;
}

void multF(Node *&temp) {
	double result;

	result = temp->prev->value * temp->next->value;
	Node *ptr = NULL;

	ptr = elem_Init_For_Num(result);
	if (head == temp->prev) head = ptr;
	else {
		temp->prev->prev->next = ptr;
	}
	ptr->next = temp->next->next;
	temp->next->next->prev = ptr;

	temp = ptr;
}

void divF(Node *&temp) {
	double result;

	result = temp->prev->value / temp->next->value;
	Node *ptr = NULL;

	ptr = elem_Init_For_Num(result);
	if (head == temp->prev) head = ptr;
	else {
		temp->prev->prev->next = ptr;
	}
	ptr->next = temp->next->next;
	temp->next->next->prev = ptr;

	temp = ptr;
}


void powF(Node *&temp) {
	double result = 1;
	double pow = temp->next->value;
	double base = temp->prev->value;

	while (pow != 0) {
		result *= base;
		pow -= 1;
	}
	if (temp->next->value == 1) result = result;
	if (temp->next->value == 0) result = 1;

	Node *ptr = NULL;

	ptr = elem_Init_For_Num(result);
	if (head == temp->prev) head = ptr;
	else {
		temp->prev->prev->next = ptr;
	}
	ptr->next = temp->next->next;
	temp->next->next->prev = ptr;

	temp = ptr;
}
/////////////////////////////////////////////////
////////end of math functions////////////////////
void checkBrackets(void) {
	Node *temp = head;
	//going untill we find closing bracket
	while (temp != NULL) {

		if (temp->sign == ')') {
			Node *_prev = NULL;
			Node *_sign = NULL;
			Node *_next = NULL;
			//checking if the whole exression in brackets was calculated
			if (temp->prev->prev->sign == '(') {
				Node *ptr = temp->prev;
				Node *next = temp->next;
				if (head == temp->prev->prev) {
					head = ptr;
					ptr->prev = head;
				}
				if (head != temp->prev->prev) {
					temp->prev->prev->prev->next = ptr;
					ptr->prev = temp->prev->prev->prev;
				}

				ptr->next = next;
				next->prev = ptr;
				temp = head;
				continue;
			}
			Node *checkBrackets = head;
			bool flagCheck = true;
			while (checkBrackets) {
				if (checkBrackets->sign == ')') {
					flagCheck = false;
					break;
				}
				checkBrackets = checkBrackets->next;
			}
			if (flagCheck) return;
			Node *ptr = temp;
			while (ptr->sign != '(' && ptr != NULL) {
				Node *_prev = ptr->prev->prev;
				if (ptr->sign == '^') {
					powF(ptr);
					ptr->prev = _prev;
				}
				//separate while loop for power 
				else if (ptr->sign == '*') {
					multF(ptr);
					ptr->prev = _prev;
				}

				else if (ptr->sign == '/') {
					divF(ptr);
					ptr->prev = _prev;
				}
				else ptr = ptr->prev;

			}//while closure
			ptr = temp;
			while (ptr->sign != '(' && ptr != NULL) {
				Node *_prev = ptr->prev->prev;
				if (ptr->sign == '+') {
					addF(ptr);
					ptr->prev = _prev;
				}
				//make separate while loop for power 
				else if (ptr->sign == '-') {
					subF(ptr);
					ptr->prev = _prev;
				}
				else ptr = ptr->prev;
			}//while closure
			temp = head;
		}//big if closure
		temp = temp->next;
	}//while closure
	return;
}