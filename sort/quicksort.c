#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void sort(int *a, int left, int right)
{
    if (left >= right) {
        return;
    }

    int i = left;
    int j = right;
    int key = a[left];
    int tmp = 0;

    while (i < j) {
        while (i < j && key <= a[j]) {
            j--;
        }
        tmp = a[i];
        a[i]= a[j];
        a[j] = tmp;

        while( i < j && key >= a[i]) {
            i++;
        }
       tmp = a[j];
       a[j] = a[i];
       a[i] = tmp;
    }

    sort(a, left, i - 1);
    sort(a, i + 1, right);
}

int main(int argc, char *argv[])
{
    int arry[] = {49, 3, 97, 233, 2, 4, 5, 50, 70};
    for (int i = 0; i < 9; i++) {
        printf("%d ", arry[i]);
    }
    printf("\n");
    sort(arry, 0, 8);
    for (int i = 0; i < 9; i++) {
        printf("%d ", arry[i]);
    }
    printf("\n");
    return 0;
}
