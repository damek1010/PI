#include <iostream>

// Uncomment line with "#define DEBUG" if you want to see your hashtable.
// But rememeber to send only solutions with debug turned off!
 #define DEBUG 1 

using namespace std;


struct Node
{
    string text;
    Node *next;
};

uint hashfunc(string txt) {
    /**********************
    * PLACE FOR YOUR CODE *
    **********************/
    uint sum = 0;
    for (int i = 0; i < txt.length(); i++) sum += txt[i] - 65;
    return sum;
}

void add_to_hashtable(Node** hashtable, int n, string txt) {
    /**********************
    * PLACE FOR YOUR CODE *
    **********************/
    uint hash = hashfunc(txt) % n;
    Node *p = hashtable[hash];
    Node *q = new Node;
    q->next = NULL;
    q->text = txt;
    if (p) {
    	while (p->next) p = p->next;
	p->next = q;
    } else hashtable[hash] = q;
}

bool check_if_exists(Node** hashtable, int n, string txt) {
    /**********************
    * PLACE FOR YOUR CODE *
    **********************/
    uint hash = hashfunc(txt) % n;
    Node *p = hashtable[hash];
    
    while (p && p->text != txt) p = p->next;	
    return p != NULL;
}

void free_memory(Node** hashtable, int n) {
    Node *ptr, *nxt;    
    for (int i = 0; i < n; i++) {
        ptr = hashtable[i];
        while (ptr != NULL) {
            /**********************
            * PLACE FOR YOUR CODE *
            **********************/
	    Node *tmp = ptr->next;
	    delete ptr;
	    ptr = tmp;
        }
    }
    delete[](hashtable);
}

void debug_print_hashtable(Node** hashtable, int n) {
    #ifdef DEBUG
        Node* ptr;  
        for (int i = 0; i < n; i++) {
            cout << i << ": ";
            ptr = hashtable[i];
            while (ptr != NULL) {
                cout << ptr->text << " | ";
                ptr = ptr->next;
            }
            cout << endl;
        }
    #endif
}

int main() {
    ios::sync_with_stdio(false);
    int Z;
    cin >> Z;

    while (Z--) {
        int n, k;
        string tmp;

        cin >> n;
        cin >> k;

        Node** hashtable = new Node*[n]();

        for (int i = 0; i < n; i++)
            hashtable[i] = NULL;

        for (int i = 0; i < n; i++) {
            cin >> tmp;
            add_to_hashtable(hashtable, n, tmp);
        }

        debug_print_hashtable(hashtable, n);

        for (int i = 0; i < k; i++) {
            cin >> tmp;
            if (check_if_exists(hashtable, n, tmp)) {
                cout << "YES" << endl;
            } else {
                cout << "NO" << endl;
            }
        }

        free_memory(hashtable, n);

    }

}
