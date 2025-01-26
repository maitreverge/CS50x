#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Prompt user a name
    string name = get_string("What's your name ? ");
    // Print hello + promped name
    printf("hello, %s\n", name);
}