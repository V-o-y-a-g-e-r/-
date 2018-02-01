#define _CRT_SECURE_NO_WARNINGS
#include "Libraries.h"
#include "Nodes.h"

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