#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Prompt user value
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    // printvalue


    int i = 0;
    int j = 0;
    int k = height;
    int l = height;

    while (i < height) // espace pyramid
    {
        j = j + 1;
        while (j < height) // print .
        {
            printf(" ");
            j++;
        }

        while (j <= k)
        {
            printf("#");
            j++;
        }
        printf("  ");
        while (k + 1 >= j)
        {
            printf("#");
            j++;
        }
        printf("\n");
        height--;
        j = 0;

    }
}