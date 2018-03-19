#include <stdio.h>
#include <algorithm>
using namespace std;

int partition(int tab[], int left, int right) {
    int x = tab[right];
    int j = left - 1;
    int i;
    for (i=left; i<right; i++) {
        if (tab[i] <= x) {
            // przenies element do lewej podtablicy
	    j++;
	    swap(tab[i], tab[j]);
        }
    }
    j++;
    swap(tab[i], tab[j]);
    return j;
}

void quickSort(int tab[], int left, int right) {
    if (left < right) {
      // wywolaj funkcje partition()
      // wywolaj rekurencyjnie funkcje quickSort()
      int q = partition(tab, left, right);
      quickSort(tab, left, q - 1);
      quickSort(tab, q + 1, right);
    }
}

int main() {
  int Z;

  scanf("%d", &Z);

  int val;

	while (Z--) {

		int n;
		scanf("%d", &n);
    int *tab = new int[n];
		for(int i=0; i<n; i++) {
			scanf("%d", &tab[i]);
		}
        
    quickSort(tab, 0, n-1);
    for(int i=0; i<n; i++) {
      printf("%d\n", tab[i]);
    }
    delete [] tab;
    }
}
