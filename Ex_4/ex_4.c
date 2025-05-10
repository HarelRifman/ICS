/*****************
 * Created by Harel
 * id: 217398338
 * Assignment: ex_4
******************/
#include <stdlib.h>
#include <stdio.h>
int main(){
    int *p = (int*)(malloc(3* sizeof(int)));

    for(int i = 0; i <3 ; i++){
        printf("Enter a number\n");
        scanf("%d",p+i);
    }
    for (int i = 0; i < 3; ++i) {
        printf("%d",*(p+i));
    }

    p = (int*) realloc(p,4*sizeof(int));

    for(int i = 0; i <4 ; i++){
        printf("Enter a number\n");
        scanf("%d",p+i);
    }
    for (int i = 0; i < 4; ++i) {
        printf("%d",*(p+i));
    }
    return  0;
}