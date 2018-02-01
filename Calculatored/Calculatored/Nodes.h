#pragma once

struct Elem {
	Elem *next;
	Elem *prev;
	char sign;
	double value;
};

typedef struct Elem Node;

Node* elem_Init_For_Sign(const char sign);
Node* elem_Init_For_Num(const double var);
void insertNode(Node *ptr);