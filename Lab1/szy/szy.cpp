#include <cstddef>
#include <iostream>

using namespace std;

struct node {
	int val;
	node* next;
};

void print(node* head);

void push_back(node *&head, int val) {
	node *p = head;

	node *el = new node;
	el->val = val;
	el->next = NULL;

	if (p) {
		while (p->next) p = p->next;
		p->next = el;
	} else {
		head = el;
	}
}

void split(node *head, node *&h1, node *&h2) {
	bool s = false;
	while (head) {
		//cout << head->val << endl;
		if (s) {
			push_back(h1, head->val);
		} else {
			push_back(h2, head->val);
		}
		s = !s;
		head = head->next;
	}
}

void merge(node *&head, node *h1, node *h2) {
	head = NULL;
	while (h1 && h2) {
		if (h1->val < h2->val) {
			push_back(head, h1->val);
			h1 = h1->next;
		} else {
			push_back(head, h2->val);
			h2 = h2->next;
		}
	}	
	while (h1) {
		push_back(head, h1->val);
		h1 = h1->next;
	}
	while (h2) {
		push_back(head, h2->val);
		h2 = h2->next;
	}
}

void mergeSort(node *&head) {
	node *p = NULL, *q = NULL;
	if (head && head->next) {
		split(head, p, q);
		//print(p);
		//print(q);
		mergeSort(p);
		mergeSort(q);
		merge(head, p, q);
	}
}

void print(node *head) {
	node *p = head;
	while (p) {
		cout << p->val << " ";
		p = p->next;
	}
	cout << endl;
}

int main() {
	node *head = NULL;
	push_back(head, 1);
	push_back(head, 6);
	push_back(head, 4);

	print(head);

	mergeSort(head);

	print(head);
}
