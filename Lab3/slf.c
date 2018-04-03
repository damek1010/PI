#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <limits.h>

typedef struct Node {
    int val;
    int height;
    struct Node** next;
} Node;

typedef struct SkipList {
    int max_height;
    Node* start;
    Node* end;
} SkipList;

int getHeight(int max_h) {
    int h = 1;
    float p = 0.8;
    while (h < max_h && rand() / (RAND_MAX + 1.) < p) h++;
    return h;
}

/*
 * paste here your pretty code from previous task
 */
Node* newNode(int val, int max_height) {
    Node* n = malloc(sizeof(Node));// allocate
    n->val = val;
    n->height = getHeight(max_height);
    n->next = malloc(sizeof(Node) * max_height);// allocate, set all pointers to NULL
    return n;
}

void deleteNode(Node* n) {
    for (int i = 0; i < n->height; i++) {
    	n->next[i] = NULL;
	free(n->next[i]);
    }
    free(n);
}

SkipList* newSkipList(int max_height) {
    SkipList* list = malloc(sizeof(SkipList));// allocate
    list->max_height = max_height;
    
    // allocate list->start and list->end
    // initialize height and next for each one
    list->start = malloc(sizeof(Node));
    list->start->val = INT_MIN;
    list->end = malloc(sizeof(Node));
    list->start->height = max_height;
    list->end->height = max_height;
    list->end->val = INT_MAX;
    list->start->next = malloc(sizeof(Node) * max_height);
    list->end->next = calloc(max_height, sizeof(Node));

    for(int i=0; i<max_height; i++) {
        list->start->next[i] = list->end;
        list->end->next[i] = NULL;
    }

    return list;
}

void deleteSkipList(SkipList* list) {
    // call deleteNode() on every node in skiplist
    // call free() on list
    Node *p = list->start;
    while (p->next[0] != NULL) {
    	Node *tmp = p->next[0];
	deleteNode(p);
	p = tmp;
    }
    free(list);
}

void insert(SkipList* list, Node* node) {
    Node* tmp = list->start;
    int i = list->max_height - 1;
    while (i >= 0) {
        // while value of tmp->next[i] is less than value of given node, go ahead
        // if i isn't too high - insert (plug) given node on level 'i'
	while (tmp->next != NULL && tmp->next[i]->val < node->val) tmp = tmp->next[i];
	if (i <= node->height) {
	    node->next[i] = tmp->next[i];
	    tmp->next[i] = node;
	}
        i--;
    }
}

Node* find(SkipList* list, int val) {
    Node* tmp = list->start;
    int i = list->max_height - 1;
    while (i >= 0) {
        // while value of tmp->next[i] is less than value of given node, go ahead
        while (tmp->next[i] != NULL && tmp->next[i]->val < val) tmp = tmp->next[i];
	if (tmp->next[i] && tmp->next[i]->val == val) return tmp;
        i--;
    }
    return NULL;
    // return desired node or NULL if such value doesn't exist in the skiplist
}

int main(int argc, char** argv) {
    /*
     * test data:
     * Z - number of test cases
     * h, I, F - max height of single node (h), number of values to insert (I) and find (F)
     * I values to insert
     * F values to find
     * Output:
     * F lines, "y" or "n" in each one - depending on whether given value is present in the skiplist or not
    */
    srand(time(NULL));
    int Z;
    scanf("%d", &Z);

    for (int i=0; i<Z; i++) {
        int h, I, F;
        scanf("%d", &h);
        scanf("%d", &I);
        scanf("%d", &F);

        SkipList* list = newSkipList(h);
        int x;
        // insert
        for(int j=0; j<I; j++) {
            scanf("%d", &x);
            insert(list, newNode(x, h));
        }
        // find
        for(int j=0; j<F; j++) {
            scanf("%d", &x);
            printf("%s\n", find(list, x) == NULL ? "n" : "y");
        }

        // cleanup
        deleteSkipList(list);
    }
}
