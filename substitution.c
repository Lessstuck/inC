#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

void encode(string plain, string key);



int main(int argc, string argv[])
{
    // if there is no argument
    if (argc != 2)
    {
        printf("Usage: ./substitution key");
        printf("\n");
        return 1;
    }
    // if there are wrong number of arguments
    // TODO prompts to help get 26 letters exactly
    else if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.");
        printf("\n");
        return 1;
    }
    else
    {
        // get key
        string plainString = get_string("plaintext: ");
        string key = argv[1];
        // encoding
        printf("ciphertext: ");
        // printf("%s", encode(plainString, key));
        encode(plainString, key);
        printf("\n");
        return 0;
    }
}

void encode(string plainString, string key)
{
    int length = strlen(plainString);
    // string encoded[length];
    for (int i = 0; i < length; i++)
    {
        // upper-case letters
        if (plainString[i] >= 65 && plainString[i] <= 90)
        {
            char encodedChar = key[((int) plainString[i] - 65)];
            printf("%c", encodedChar);
        }
        // lower-case letters
        else if (plainString[i] >= 97 && plainString[i] <= 122)
        {
            // adding 32 makes key lower case
            char encodedChar = (int) key[((int) plainString[i] - 65)];
            printf("%c", encodedChar);
        }
        else
        {
            printf("%c", plainString[i]);
        }
    }
}
