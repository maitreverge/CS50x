#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int start_size;
    int end_size;
    //Prompt start size
    do
    {
        start_size = get_int("What's the start size ? ");
    }
    while (start_size < 9);
    //prompt user end size
    do
    {
        end_size = get_int("What's the end size ? ");
    }
    while (end_size < start_size);
    //calculate function
    int n = 0;

    int current_size = start_size;

    while (current_size < end_size)
    {
        current_size = (current_size + (current_size / 3)) - (current_size / 4);
        n++;
    }
    if (end_size == start_size)
    {
        n = 0;
    }
    //Main print function
    printf("Years: %i", n);
}
