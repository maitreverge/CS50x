#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int convert(string input);

int main(void)
{
    string input = get_string("Enter a positive integer: ");

    for (int i = 0, n = strlen(input); i < n; i++)
    {
        if (!isdigit(input[i]))
        {
            printf("Invalid Input!\n");
            return 1;
        }
    }

    // Convert string to int
    printf("%i\n", convert(input));
}

int convert(string input)
{
    int result = 0;
    for (int i = 0; input[i] != '\0'; i++)
    {
        result = result * 10 + (input[i] - 48);
    }
    return result;

    //int result = 1;
   // int i = strlen(input);

    //result = result + input[i]

}