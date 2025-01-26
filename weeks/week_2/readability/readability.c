#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

// FUNCTION PROTOTYPES
int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

// MAIN
int main(void)
{
    string prompt = get_string("Text: ");

    int letters = count_letters(prompt);
    int words = count_words(prompt);
    int sentences = count_sentences(prompt);

    //test printf
    //printf("%i letters\n", letters);
    //printf("%i words\n", words);
    // printf("%i sentences\n", sentences);

    float L = ((float)letters / words) * 100;
    float S = ((float)sentences / words) * 100;

    int index = round((0.0588 * L) - (0.296 * S) - 15.8);

    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index < 16 && index >= 1)
    {
        printf("Grade %i\n", index);
    }
    else
    {
        printf("Grade 16+\n");
    }

}

int count_letters(string text)
{
    int total = 0;

    for (int i = 0; i < strlen(text); i++)
    {
        if (isalpha(text[i]))
        {
            total++;
        }
    }
    return total;
}
// count words
int count_words(string text)
{
    int total = 1;

    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] == ' ')
        {
            total++;
        }
    }
    return total;
}
// count sentences
int count_sentences(string text)
{
    int total = 1;

    for (int i = 0; i < strlen(text); i++)
    {
        if ((text[i] == '.' || text[i] == '!' || text[i] == '?') && (text[i + 1] == ' '))
        {
            total++;
        }
    }
    return total;
}


