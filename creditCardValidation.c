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
// return 1 if number is valid
    return (((leftSum + rightSum) % 10) == 0);
}



int main(void)
{
    // get card number
    do
    {
        cc = get_long("Number: ");
    }
    while (cc < 0 || cc > 9999999999999999);

    // getting digits for final card check, starting at 1 instead of 0, like problem text
    int d16 = getDigit(cc, 15);
    int d15 = getDigit(cc, 14);
    int d14 = getDigit(cc, 13);
    int d13 = getDigit(cc, 12);

    if (luhn(cc) != 1)
    {
        printf("INVALID\n");
    }
    else if (d16 == 0 && (d15 == 3) && ((d14 == 4) || (d14 == 7)))
    {
        printf("AMEX\n");
    }
    else if ((d16 == 5) && ((d15 == 1) || (d15 == 2) || (d15 == 3) || (d15 == 4) || (d15 == 5)))
    {
        printf("MASTERCARD\n");
    }
    else if (d16 == 4)
    {
        printf("VISA\n");
    }
    else if ((d16 == 0) && (d15 == 0) && (d14 == 0) && (d13 == 4))
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }

}
