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
        printf("Usage: ./substitution key\n");
        return 1;
    }
    // if there are wrong number of arguments
    // TODO prompts to help get 26 letters exactly
    else if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    else
    {
        // get key
        string key = argv[1];
        for (int i = 0; i < 25; i++)
        {
            int testKey = key[i];
            if (testKey < 65 || (testKey > 90 && testKey < 97) || testKey > 122)
            {
                printf("Key must contain only alphabetical characters.\n");
                return 1;
            }
            else
            {
                for (int j = 0; j < 25; j++)
                {
                    for (int k = 0; k < j; k++)
                    {
                        if (key[j] == key[k])
                        {
                            printf("Key must not contain repeated characters.\n");
                            return 1;
                        }
                    }
                }
            }
            
        }
        // get plain text
        string plainString = get_string("plaintext: ");
        // encoding
        printf("ciphertext: ");
        // prints ciphertext
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
            encodedChar = toupper(encodedChar);
            printf("%c", encodedChar);
        }
        // lower-case letters
        else if (plainString[i] >= 97 && plainString[i] <= 122)
        {
            char encodedChar = (int) key[((int) plainString[i] - 97)];
            encodedChar = tolower(encodedChar);
            printf("%c", encodedChar);
        }
        else
        {
            printf("%c", plainString[i]);
        }
    }
}
