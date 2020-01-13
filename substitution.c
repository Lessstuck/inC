#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

// implements substitution encryption
string alphabet[] =
{ "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z" };

//
int main(int argc, string argv[])
{
    // if there is no argument
    if (argc != 2)
    {
        printf("Usage: ./substitution key");
        printf("\n");
        return 1;
    }
    // if there are too few arguments
    else if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.");
        printf("\n");
        return 1;
    }
    else
    {
        printf("plaintext: ");

        printf("\n");
        printf("ciphertext: ");
        // TODO redo with ciphertext
        for (int i = 0; i < 26; i++)
        {
            printf("%c", argv[1][i]);
        }
        printf("\n");
        return 0;
    }
}
