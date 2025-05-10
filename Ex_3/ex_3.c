/*****************
 * Created by Harel
 * id: 217398338
 * Assignment: ex_3
******************/

#include <stdio.h>

///the method prints the two arrays together, sorted as one.
//the method prints the two arrays together, sorted as one.
void mergePrint(int a1[], int a2[], int start1, int start2, int end1, int end2)
{
    if (start1 > end1 && start2 > end2){
        return;
    }
    if (start1 > end1){
        printf("%d ", a2[start2]);
        mergePrint(a1, a2, start1, start2 + 1, end1, end2);
        return;
    }
    if (start2 > end2){
        printf("%d ", a1[start1]);
        mergePrint(a1, a2, start1 + 1, start2, end1, end2);
        return;
    }
    if (a1[start1] <= a2[start2]){
        printf("%d ", a1[start1]);
        mergePrint(a1, a2, start1 + 1, start2, end1, end2);
        return;
    }

    printf("%d ", a2[start2]);
    mergePrint(a1, a2, start1, start2 + 1, end1, end2);
}


// Using merge print while getting two arrays from the user
void ex1(){
    int i, lenArr1;
    int valArr1[30];

    printf("Enter the length of the first worker array:\n");
    scanf("%d", &lenArr1);
    printf("Now enter the first array's elements:\n");
    for(i=0 ; i<lenArr1 ; i++){
        scanf("%d", &valArr1[i]);
    }

    int lenArr2;
    int valArr2[30];

    printf("Enter the length of the second worker array:\n");
    scanf("%d", &lenArr2);
    printf("Now enter the second array's elements:\n");
    for(i=0 ; i<lenArr2 ; i++){
        scanf("%d" , &valArr2[i]);
    }

    printf("start ");
    mergePrint(valArr1 , valArr2 , 0 , 0 , lenArr1 - 1 , lenArr2 - 1);
    printf("end\n");
}

// Returns the palindromic distance of a string
int paliDistance(char str[], int start, int end){
    if(start >= end) return 0;
    if (str[start] == str[end]) return paliDistance(str, start + 1, end - 1);
    return 1 + paliDistance(str, start + 1, end - 1);
}


//sums up the letter a in a string
int sumOfA(char str[], int n){
    if (n == -1){
        return 0;
    }
    else{
        if (str[n] == 'a'){
            return 1+sumOfA(str,n-1);
        }
        else{
            return sumOfA(str,n-1);
        }
    }
}

//sums up the letter b in a string
int sumOfB(char str[], int n){
    if (n == -1){
        return 0;
    }
    else{
        if (str[n] == 'b'){
            return 1+sumOfB(str,n-1);
        }
        else{
            return sumOfB(str,n-1);
        }
    }
}

//checks if the amount of an occurrences are equal to the amount of b occurrences
int checkBalance(char str[], int n){
    if(sumOfA(str,n) == sumOfB(str,n)){
        return 1;
    }
    else{
        return 0;
    }
}

// returns the least amount of possible rout between the number to 1 when the actions allowed are: /2 /3 and -1
int escapingTime(int n) {
    if (n == 1) {
        return 0;
    }

    int minus = escapingTime(n - 1);
    int third = minus;
    int half = minus;
    if (n % 3 == 0) {
        third = escapingTime(n / 3);
    }
    if (n % 2 == 0) {
        half = escapingTime(n / 2);
    }
    if (third<= half && third<= minus){
        return third +1;
    }
    else if(half<=third && half<= minus){
        return 1+half;
    }
    else{
        return   1+minus;
    }
}

// Recursive function to find the optimal value for a heist scenario
int heistOpt(int maxW, int optVal, int w[], int v[], int start, int len) {
    if (start == len || maxW == 0) {return optVal;}
    int excludeCurrent = heistOpt(maxW, optVal, w, v, start + 1, len);
    int includeCurrent = 0;
    if (w[start] <= maxW) { includeCurrent = heistOpt(maxW - w[start], optVal + v[start], w, v, start + 1, len);}
    return (excludeCurrent > includeCurrent) ? excludeCurrent : includeCurrent;
}

int main() {
    int option;
    int exit = 0;
    while(exit == 0)
    {
        printf("What is your desired task boss?\n");
        printf("1. merge order incomes\n");
        printf("2. find distance from symmetry\n");
        printf("3. check if the gangs are balanced\n");
        printf("4. find optimal time for escaping\n");
        printf("5. check workers efficiency\n");
        printf("6. exit\n");
        scanf("%d", &option);
        if (option == 1) {
            ex1();
        }
        else if (option == 2) {
            char str[30];
            int len;
            int i;

            printf("Enter the length of the string:\n");
            scanf("%d", &len);
            printf("Now enter the string:\n");
            i=0;
            for(; i<len ; i++){
                scanf(" %c", &str[i]);
            }

            printf("The palindrome distance is %d.\n", paliDistance(str , 0 , len - 1));
        }
        else if (option == 3) {
            int n;
            char str[30];
            printf("Enter the number of gang members:\n");
            scanf("%d", &n);
            printf("Enter the gang associations:\n");
            int i = 0;
            for (; i < n; i++) {
                scanf(" %c", &str[i]);
            }
            int isBalanced = checkBalance(str, n);
            if (isBalanced == 1) {
                printf("The army is balanced.\n");
            } else {
                printf("The army is not balanced.\n");
            }
        }
        else if (option == 4) {
            int n;
            printf("What room are you in boss?\n");
            scanf("%d", &n);
            int escapingTimeResult = escapingTime(n);  // Use a different name for the variable
            printf("Your escaping time is: %d\n", escapingTimeResult);
        }
        else if (option == 5) {
            int n, maxW;

            printf("Enter the number of objects and the maximum weight:\n");
            scanf("%d%d", &n, &maxW);

            int w[n], v[n];

            printf("Now enter the objects' values and weights:\n");
            int i = 0;
            for (; i < n; i++) {
                scanf("%d%d", &v[i], &w[i]);
            }

            int optimalValue = heistOpt(maxW, 0, w, v, 0, n);

            // Print the result
            printf("The optimal heist income value is %d\n", optimalValue);

        }
        else if (option == 6) {
            printf("goodbye boss!");
            exit = 1;
        }
        else{
            printf("Sorry Tony, I don't understand...\n");
        }
    }


    return  0;
}
