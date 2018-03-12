#include <stdio.h>

struct Node
{
    int val;
    Node *next;
};

// use if you want implement selection sort
Node* remove_maximum(Node *&head) {
    if (head == NULL) {
        return NULL;
    }
    if (head->next == NULL) {
        Node *tmp = head;
        head = NULL;
        return tmp;
    }

    /*********************************
    * What if list is longer than 1? *
    **********************************/
}

// use if you want implement insertion sort
void insert(Node *&head, Node *item) {
    Node *q = new Node;
    q->next = NULL;
    q->val = item->val;
    
    if (head == NULL || head->val > item->val) {
        q->next = head;
        head = q;
        return;
    }

    /*****************************************************
    * What if item should be placed further on the list? *
    *****************************************************/
    Node *p = head;
    
    while (p->next && p->next->val < item->val) p = p->next;
    q->next = p->next;
    p->next = q;
}

Node* sort(Node *head) {
    /**********************************
    * This is the place for your code *
    ***********************************/
    Node *q = NULL;
    Node *p = head;

    while(p) {
	insert(q, p);
	p = p->next;
    }

    return q;
}

int main() {
    int Z;    
    scanf("%d", &Z);

    int val;

    while (Z--) {

        Node *head = NULL;
        Node *curr = NULL;
        
        int n, val;
        scanf("%d", &n);

        while (n--) {
            scanf("%d", &val);
            Node *temp = new Node;
            temp->val = val;
            temp->next = NULL;
            if (head == NULL) {
                head = temp;
                curr = temp;
            } else {
                curr->next = temp;
                curr = temp;
            }
        }

        Node *pr = head;
        head = sort(head);

        while (head != NULL) {
            printf("%d\n", head->val);
            curr = head;
            head = head->next;
            /**************************************
            * Hey! Remember not to litter around! *
            **************************************/
        }

    }

}
