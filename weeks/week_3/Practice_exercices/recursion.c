#include <stdio.h>
#include <cs50.h>

int factorial(int number);

int main(void)
{
    int i = get_int("Factorial: ");

    printf("%i\n", factorial(i));
}

int factorial(int number)
{
    if (number == 1)
    {
        return 1;
    }

    return number * factorial(number - 1);
}