#include <stdio.h>
#include <math.h>

int main() {
    
//EXERCISE 1
    printf("Exercise 1:\nPlease enter 2 binary strings with 4 digits:\nBinary 1: ");
    int dig1,dig2,dig3,dig4,DIG1,DIG2,DIG3,DIG4;

    //Scan every bit into a different variable
    scanf("%1d%1d%1d%1d", &dig4,&dig3,&dig2,&dig1);
    printf("Binary 2: ");
    scanf("%1d%1d%1d%1d", &DIG4,&DIG3,&DIG2,&DIG1);

    //Print the calculate
    printf("\n%d%d%d%d\n^\n%d%d%d%d\n--------\n", dig4,dig3,dig2,dig1,DIG4,DIG3,DIG2,DIG1);

    //print the xor result of every bit from the first num with his matching bit from the second num
    printf("%d%d%d%d\n", dig4^DIG4, dig3^DIG3, dig2^DIG2, dig1^DIG1);



//EXRECISE 2
    printf("\nExercise 2:\nEnter 2 hexadecimal numbers:\nHex 1: ");

    //Scan 2 hexadecimal numbers
    int hex1,hex2;
    scanf("%X", &hex1);
    printf("Hex 2: ");
    scanf("%X", &hex2);

    //Calculate and print their sum
    int hexSum = hex1+hex2;
    printf("\n%X + %X = %X\n", hex1, hex2, hexSum);

    //Print the last 4 bits of the sum
    printf("The last 4 binary digits of the sum are %d%d%d%d\n", (hexSum>>3)&0x1, (hexSum>>2)&0x1, (hexSum>>1)&0x1, hexSum&0x1);
 


//EXERCISE 3
    printf("\nExercise 3:\nChoose a base between 2 to 9: ");

    //Scan a base and a number in that base
    int base, numInBase,numInDec;
    scanf("%d", &base);
    printf("Enter a 5 digit number using that base: ");
    scanf("%d",&numInBase);

    //Represent the number in base decimal (10)
    int temp=numInBase;
    numInDec=(temp%10)*pow(base,0);

    temp/=10;
    numInDec+=(temp%10)*pow(base,1);
    
    temp/=10;
    numInDec+=(temp%10)*pow(base,2);

    temp/=10;
    numInDec+=(temp%10)*pow(base,3);

    temp/=10;
    numInDec+=(temp%10)*pow(base,4);

    //Print the decimal value
    printf("The decimal value of %d in base %d is %d\n",numInBase,base,numInDec);



//EXERCISE 4
    printf("\nExercise 4:\nEnter a number: ");
    
    //Scan a number and a bit between 1-32
    int num, dig;
    scanf("%d", &num);
    printf("I want to know the value of bit number: ");
    scanf("%d", &dig);

    //Print that bit in the number
    printf("\nThe value of the %d bit in %d is %d\n",dig,num,(num>>(dig-1))&0x1);



//FINISH 
    printf("Congrats! You've found the philosopher's stone!");

    return 0;
}