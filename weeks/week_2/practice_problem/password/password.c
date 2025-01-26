// Check that a password has at least one lowercase letter, uppercase letter, number and symbol
// Practice iterating through a string
// Practice using the ctype library

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

bool valid(string password);

int main(void)
{
    string password = get_string("Enter your password: ");
    if (valid(password))
    {
        printf("Your password is valid!\n");
    }
    else
    {
        printf("Your password needs at least one uppercase letter, lowercase letter, number and symbol\n");
    }
}

// TODO: Complete the Boolean function below
bool valid(string password)
{
    bool check_upper = false;
    bool check_lower = false;
    bool check_number = false;
    bool check_symbol = false;

    for (int i = 0; i < strlen(password); i++)
    {
        if (isupper(password[i]))
            check_upper = true;
        if (islower(password[i]))
            check_lower = true;
        if (isdigit(password[i]))
            check_number = true;
        if (ispunct(password[i]))
            check_symbol = true;
    }
    if ((check_upper == true) && (check_lower == true) && (check_number == true) && (check_symbol == true))
        return 1;
    else
        return 0;
}
