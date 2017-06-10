#include <stdio.h>
#include <stdlib.h>

int main()
{
    int arr[4][4];
    int **arrp = (int**) malloc (4* sizeof(int));
    for (int i = 0; i < 4; i++){
        arrp[i] = (int*) malloc(4*sizeof(int));
    }

    printf("%d\n",arr[0][0]);
    arrp[0][0] = 1;
    printf("%d \n",arrp[0][0]);
    return 0;
}
