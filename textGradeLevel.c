#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

int count_letters(string s);
int count_words(string s);
int count_sentences(string s);
float coleman_liau(int letter_count, int word_count, int sentence_count);

int main(void)
{
    string s = get_string("Text: ");
    // printf("%s\n", s);
    int letter_count = count_letters(s);
    // printf("%d letter(s)\n", letter_count);
    int word_count = count_words(s);
    // printf("%d words(s)\n", word_count);
    int sentence_count = count_sentences(s);
    // printf("%d sentence(s)\n", sentence_count);
    int index = coleman_liau(letter_count, word_count, sentence_count);
    // print messages for different index
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %d\n", index);
    }
    return (0);
}

// counts letters in string
int count_letters(string s)
{
    int i = 0;
    int letters = 0;
    do
    {
        // count upper-case letters
        if (s[i] >= 65 && s[i] <= 90)
        {
            letters++;
        }
        // count lower-case letters
        else if (s[i] >= 97 && s[i] <= 122)
        {
            letters++;
        }
        i++;
    }
    while (s[i] != '\0');
    return letters;
}

// counts words in string, i.e substrings separated by spaces
int count_words(string s)
{
    int i = 0;
    int spaces = 0;
    do
    {
        if (s[i] == 32)
        {
            spaces++;
        }
        i++;
    }
    while (s[i] != '\0');
    // there is always one more word than spaces
    return (spaces + 1);
}

// counts periods, question marks, and exclamation marks
int count_sentences(string s)
{
    int i = 0;
    int sentence_endings = 0;
    do
    {
        // counting periods, exclamation marks, and question marks
        if (s[i] == 46 || s[i] == 33 || s[i] == 63)
        {
            sentence_endings++;
        }
        i++;
    }
    while (s[i] != '\0');
    return sentence_endings;
}

float coleman_liau(int letter_count, int word_count, int sentence_count)
{
    float L = (letter_count / (word_count / 100.));
    float S = (sentence_count / (word_count / 100.));
    int index = round((L * 0.0588) - (S * 0.296) - 15.8);
    return (index);
}