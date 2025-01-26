#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int size = get_int("Size of the array : "); // this is a comment
    int i = 1;

    long array[size]; // this is another comment
    array[0] = 1;
    while (i <= size)
    {
        array[i] = array[i - 1] * 2;
        printf("%li\n", array[i]);
        i++;
    }

}
