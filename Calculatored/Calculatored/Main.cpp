#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <cstring>

struct Elem {
	Elem *next;
	Elem *prev;
	char sign;
	double value;
};

typedef struct Elem Node;

Node *head;//head of the list
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
//main function
int main(void) {

	head = NULL;

	getLine();
	Node *tempp = head;
	while (tempp) {
		printf("List element: %f %c\n", tempp->value, tempp->sign);
		tempp = tempp->next;
	}
	doMath();

	printResult();

	system("PAUSE");
	return 0;
}
//getting the expression
void getLine(void) {
	char sign[100];
	memset(&sign[0], '0', sizeof(sign));
	//setting whole table with zeros by "memset" method
	printf("Enter character or number.\n"
		"If you want to submit your equation press 'Enter'.\n"
		"Remember, that the equation must end with '=' sign.\n");

	scanf("%s", sign);

	//taking whole equation
	int i = 0;
	int prevBound = 0;
	//setting the counter for expression
	while (sign[i] != '\0') {
		//exclusion some characters that are not to be in the list
		if (sign[i] == '\0') break;
		//checking if any of operators were in input string
		if (sign[i] == '+') {
			int j = 0;
			if (prevBound != 0) j = prevBound;
			if (sign[i - 1] == ')') {
				insertNode(elem_Init_For_Sign(sign[i]));
				prevBound = i + 1;
				i += 1;
				continue;
			}
			char tab[100];
			memset(&tab[0], '0', sizeof(tab));
			for (true; j < i; ++j) {
				tab[j] = sign[j];
			}
			tab[i] = '\0';
			char *ptr = (char*)calloc(1, strlen(tab));
			strcpy(ptr, tab);
			double var = strtod(ptr, NULL);
			insertNode(elem_Init_For_Num(var));
			insertNode(elem_Init_For_Sign(sign[i]));
			prevBound = i + 1;
		}
		if (sign[i] == '-') {
			int j = 0;
			if (prevBound != 0) j = prevBound;
			if (sign[i - 1] == ')') {
				insertNode(elem_Init_For_Sign(sign[i]));
				prevBound = i + 1;
				i += 1;
				continue;
			}
			char tab[100];
			memset(&tab[0], '0', sizeof(tab));
			for (true; j < i; ++j) {
				tab[j] = sign[j];
			}
			tab[i] = '\0';
			char *ptr = (char*)calloc(1, strlen(tab));
			strcpy(ptr, tab);
			double var = strtod(ptr, NULL);
			insertNode(elem_Init_For_Num(var));
			insertNode(elem_Init_For_Sign(sign[i]));
			prevBound = i + 1;
		}
		if (sign[i] == '*') {
			int j = 0;
			if (prevBound != 0) j = prevBound;
			if (sign[i - 1] == ')') {
				insertNode(elem_Init_For_Sign(sign[i]));
				prevBound = i + 1;
				i += 1;
				continue;
			}
			char tab[100];
			memset(&tab[0], '0', sizeof(tab));
			for (true; j < i; ++j) {
				tab[j] = sign[j];
			}
			tab[i] = '\0';
			char *ptr = (char*)calloc(1, strlen(tab));
			strcpy(ptr, tab);
			double var = strtod(ptr, NULL);
			insertNode(elem_Init_For_Num(var));
			insertNode(elem_Init_For_Sign(sign[i]));
			prevBound = i + 1;
		}
		if (sign[i] == '/') {
			int j = 0;
			if (prevBound != 0) j = prevBound;
			if (sign[i - 1] == ')') {
				insertNode(elem_Init_For_Sign(sign[i]));
				prevBound = i + 1;
				i += 1;
				continue;
			}
			char tab[100];
			memset(&tab[0], '0', sizeof(tab));
			for (true; j < i; ++j) {
				tab[j] = sign[j];
			}
			tab[i] = '\0';
			char *ptr = (char*)calloc(1, strlen(tab));
			strcpy(ptr, tab);
			double var = strtod(ptr, NULL);
			insertNode(elem_Init_For_Num(var));
			insertNode(elem_Init_For_Sign(sign[i]));
			prevBound = i + 1;
		}
		if (sign[i] == '^') {
			int j = 0;
			if (prevBound != 0) j = prevBound;
			if (sign[i - 1] == ')') {
				insertNode(elem_Init_For_Sign(sign[i]));
				prevBound = i + 1;
				i += 1;
				continue;
			}
			char tab[100];
			memset(&tab[0], '0', sizeof(tab));
			for (true; j < i; ++j) {
				tab[j] = sign[j];
			}
			tab[i] = '\0';
			char *ptr = (char*)calloc(1, strlen(tab));
			strcpy(ptr, tab);
			double var = strtod(ptr, NULL);
			insertNode(elem_Init_For_Num(var));
			insertNode(elem_Init_For_Sign(sign[i]));
			prevBound = i + 1;
		}
		if (sign[i] == '=') {
			int j = 0;
			if (prevBound != 0) j = prevBound;
			if (sign[i - 1] == ')') {
				insertNode(elem_Init_For_Sign(sign[i]));
				return;
			}
			char tab[100];
			memset(&tab[0], '0', sizeof(tab));
			for (true; j < i; ++j) {
				tab[j] = sign[j];
			}
			tab[i] = '\0';
			char *ptr = (char*)calloc(1, strlen(tab));
			strcpy(ptr, tab);
			double var = strtod(ptr, NULL);
			insertNode(elem_Init_For_Num(var));
			insertNode(elem_Init_For_Sign(sign[i]));
			prevBound = i + 1;
		}
		if (sign[i] == '(') {
			int j = 0;
			if (prevBound != 0) j = prevBound;
			insertNode(elem_Init_For_Sign(sign[i]));
			prevBound = i + 1;
			i += 1;
			continue;
		}
		if (sign[i] == ')') {
			int j = 0;
			if (prevBound != 0) j = prevBound;
			if (sign[i - 1] == ')') {
				insertNode(elem_Init_For_Sign(sign[i]));
				prevBound = i + 1;
				i += 1;
				continue;
			}
			char tab[100];
			memset(&tab[0], '0', sizeof(tab));
			for (true; j < i; ++j) {
				tab[j] = sign[j];
			}
			tab[i] = '\0';
			char *ptr = (char*)calloc(1, strlen(tab));
			strcpy(ptr, tab);
			double var = strtod(ptr, NULL);
			insertNode(elem_Init_For_Num(var));
			insertNode(elem_Init_For_Sign(sign[i]));
			prevBound = i + 1;
		}
		i += 1;
	}

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