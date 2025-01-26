// Write a function to replace vowels with numbers
// Get practice with strings
// Get practice with command line
// Get practice with switch

#include <cs50.h>
#include <stdio.h>
#include <string.h>

string replace(string input);

int main(int argc, string argv[])
{
    if(argc != 2)
    {
        printf("This program only accepts 1 command line argument\n");
        return 1;
    }

    printf("%s\n", replace(argv[1]));
}

string replace (string input)
{
    string output = input;
    for (int i = 0; i < strlen(input); i++)
    {
        if (output[i] == 'a')
            output[i] = '6';
        else if (output[i] == 'e')
            output[i] = '3';
        else if (output[i] == 'i')
            output[i] = '1';
        else if (output[i] == 'o')
            output[i] = '0';
        else
            output[i] = input[i];

    }
    return output;
}