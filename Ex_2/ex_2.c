/*****************
 * Created by Harel
 * id: 217398338
 * Assignment: ex_2
******************/
#include <stdio.h>
typedef enum {false,true} bool;

//Receives the number "n" from the user and prints the FizzBuzz game up to and including the number "n".
int ex1() {
    float num1;
    int num;
    printf("Enter a number: ");
    scanf("%f", &num1);

    if ((int)num1 != num1){
        printf("Foolish mortal! You cannot solve Thanos's quest with an input that isn't a natural number\n");
        return 0;
    }

    int intNum = (int)num1;


    if (intNum <= 0) {
        printf("Foolish mortal! You cannot solve Thanos's quest with an input that isn't a number bigger than 1\n\n");
        return 0;
    }
    num = 1;
    while (intNum >= num) {
        if(num % 5 == 0 && num % 3 == 0){
            printf("FizzBuzz\n");
        }
        else if (num % 5 == 0) {
            printf("Buzz\n");
        }
        else if (num % 3 == 0) {
            printf("Fizz\n");
        } else {
            printf("%d\n", num);
        }
        num = num + 1;
    }
    printf("\n");
    return  1;
}

// Receives a number "n" from the user and prints the first "n" Fibonacci numbers
int ex2(){
    int first = 0;
    int second = 1;
    int n;
    printf("Enter a number: ");
    scanf("%d",&n);
    if (n < 0) {
        printf("Foolish mortal! You cannot solve Thanos's quest with an input that isn't a number bigger than 1\n\n");
        return 0;
    }
    if (n == 1){
        printf("0");
    }

    else if (n >= 2){
        printf("0 1 ");
    }
    int temp = 0;
    for(int i = 3; i<=n ;i++){
        printf("%d ",first+second);
        temp = first;
        first =second;
        second = temp +second;
    }
    printf("\n\n");
    return 1;
}

//Receives from the user a number "n" and calculates the sum of all the initial numbers up to and including "n".
int ex3(){
    int n;
    printf("Enter a number: ");
    scanf("%d",&n);
    if (n<=1){
        printf("Foolish mortal! You cannot solve Thanos's quest with an input that isn't a number bigger than 1\n\n");
        return 0;
    }
    int sum = 0;
    bool isPrime = true;
    for(int i =2;i<=n;i++){
        for(int j = 2; j<i;j++) {
            if (i % j == 0) {
                isPrime= false;
            }
        }
        if(isPrime){
            sum = sum +i;
        }
        isPrime = true;
    }
    printf("%d\n\n",sum);
    return 1;
}

//Receiving a number from the user and checking whether it is a perfect number or not.
int ex4(){
    int num;
    int sumDevisors =0;
    printf("Enter a number: ");
    scanf("%d",&num);
    if (num<=0){
        printf("Foolish mortal! You cannot solve Thanos's quest with an input that isn't a number bigger than 0\n\n");
        return 0;
    }
    for(int i = 1 ; i<num ;i++){
        if(num%i == 0){
            sumDevisors = sumDevisors+i;
        }
    }
    if(sumDevisors == num){
        printf("Perfect!\n\n");
        return 1;
    }
    else{
        printf("Not Perfect!\n\n");
        return 0;
    }
}

int main() {
    int quest;
    int sum = 0;
    while (0 == 0) {
        printf("Welcome to Thanos's playground.\nChoose your adventure: \n");
        printf("1. Revealing the Hidden Code\n");
        printf("2. Thanos' numeric mayhem\n");
        printf("3. Thanos' Maze System\n");
        printf("4. The Sorcery of Thanos\n");
        printf("5. Quit the quest\n\n");
        scanf("%d", &quest);
        if (quest == 1) {
            sum += ex1();
        } else if (quest == 2) {
            sum += ex2();
        } else if (quest == 3) {
            sum += ex3();
        } else if (quest == 4) {
            sum += ex4();
        } else if (quest == 5) {
            break;
        } else {
            printf("Thanos is mad! You are playing his game and this is not an option. Choose again, wisely.\n\n");
        }
    }
    printf("Congratulations! You finished the quest and managed to defeat Thanos");
    return 0;
}

