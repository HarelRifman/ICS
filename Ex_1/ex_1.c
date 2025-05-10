#include <stdio.h>
int main() {
    char num1,num1_1,num1_2,num1_3;
    char num2,num2_1,num2_2,num2_3;
    char result,result1,result2,result3;

    // Exercise 1: A program that asks the user for two binary strings of exactly four digits.
    // The program will execute xor operation between the strings and print the result to the user.
    printf("Exercise 1:\n");
    printf("Please enter 2 binary strings with 4 digits:\n");
    printf("Binary 1: ");
    scanf(" %c%c%c%c", &num1, &num1_1, &num1_2, &num1_3);
    printf("Binary 2: \n");
    scanf(" %c%c%c%c", &num2, &num2_1, &num2_2, &num2_3);

    printf("%c%c%c%c\n", num1, num1_1, num1_2, num1_3);
    printf("^\n");
    printf("%c%c%c%c\n", num2, num2_1, num2_2, num2_3);
    printf("--------\n");

    result = num1 ^ num2;
    result1 = num1_1 ^ num2_1;
    result2 = num1_2 ^ num2_2;
    result3 = num1_3 ^ num2_3;

    printf("%d%d%d%d\n\n", result, result1, result2, result3);


    //Ex2- adds two hex numbers and prints the first 4 bits of the result
    unsigned int firstHex, secondHex, sum;
    int sumBits,sumBits1,sumBits2,sumBits3;
    printf("Exercise 2:\n");
    printf("Enter 2 hexadecimal numbers: \n");
    printf("Hex 1: ");
    scanf("%X", &firstHex);
    printf("Hex 2: \n");
    scanf("%X", &secondHex);
    sum = firstHex + secondHex;
    printf("%X + %X = %X\n",firstHex,secondHex,sum);
    sumBits = sum & 1;
    sum >>= 1;
    sumBits1 = sum & 1;
    sum >>= 1;
    sumBits2 = sum & 1;
    sum >>= 1;
    sumBits3 = sum & 1;
    sum >>= 1;

    printf("The last 4 binary digits of the sum are %d%d%d%d\n\n", sumBits3,sumBits2,sumBits1,sumBits);


    //Ex3- A program that requests a base between 2 and 9 and a 5-digit number written in the selected base. The program will return the
    // decimal representation of the number
    printf("Exercise 3:\n");
    int base, integer,dec;


    printf("Choose a base between 2 to 9: ");
    scanf("%d", &base);

    printf("Enter a 5 digit number using that base: ");
    scanf("%d", &integer);

    dec = integer%10 +
          (base) * ((integer % 100) / 10) +
          (base*base) * ((integer % 1000) / 100) +
          (base*base*base) * ((integer % 10000) / 1000) +
          (base*base*base*base) * (integer / 10000);

    printf("The decimal value of %d in base %d is %d\n\n", integer, base, dec);
    //Ex-4 A program that asks for a number of people, then asks for the index of one of the bits, the program will return the value of the requested bit in the binary representation of
    //The number entered.
    printf("Exercise 4:\n");

    int originalNumber, bitOrder;
    printf("Enter a number: ");
    scanf("%d", &originalNumber);

    printf("I want to know the value of bit number: \n");
    scanf("%d", &bitOrder);

    // Right-shift the originalNumber by the bitOrder
    int bitValue = (originalNumber >> (bitOrder -1)) & 1;

    printf("The value of the %d bit in %d is %d\n", bitOrder, originalNumber, bitValue);

    printf("Congrats! You've found the philosopher's stone!");
    return 0;
}