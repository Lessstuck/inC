#include <stdio.h>
#include <cs50.h>
#include <math.h>

// visa (16) 4003600000000014
// 
// visa (13) 
// 
// 4
// amex (15) 378282246310005
// 34 37
// MC (16) 5105105105105100
// 51 52 53 54 55


long cc;

//return one digit from long number
int getDigit(long number, int place)
{
        long tensPlaceHigher = pow(10, (place + 1));
        long tensPlace = pow(10, (place));
        long digit = ((number % tensPlaceHigher) - (number % (tensPlace))) / tensPlace;
        return digit;
}

// Luhn's Algorithm
int luhn(long la)
{
    int  leftSum = 0;
    int  rightSum = 0;
    bool isLeft = 0;
    int  valid;

    for (int i = 0; i < 16; i++)
    {
        long digit = getDigit(la, i);
        if (isLeft == 0)
        {
            if (digit > 9)
            {
                // add digits if there are two
                digit = ((digit  - (digit % 10)) * .1) + (digit % 10);
            }

            rightSum = rightSum + digit;
        }
        else
        {
            digit *= 2;
            if (digit > 9)
            {
                // add digits if there are two
                 digit = ((digit  - (digit % 10)) * .1) + (digit % 10);
            }
            leftSum = leftSum + (digit);
        }
        isLeft = !isLeft;
    }
    printf("rightSum: %d\n", rightSum);
    printf("leftSum: %d\n", leftSum);
    if (((leftSum + rightSum) % 10) == 0)
    {
        valid = 1;
    }
    else
    {
        valid = 0;
    }
    return (valid);
}



int main(void)
{
    // get card number
    do
    {
        cc = get_long("Number: ");  
    }
    while (cc < 0 || cc > 9999999999999999);

    printf("%d\n", luhn(cc));
}











