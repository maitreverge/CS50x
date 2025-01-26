#include <cs50.h>
#include <stdio.h>
#include <string.h>

const int BITS_IN_BYTE = 8;


void print_bulb(int bit);

int main(void)
{
    int a_bit[8];
    string prompt = get_string("Message: ");

    for (int i = 0; prompt[i] != '\0'; i++)
    {
        int j = BITS_IN_BYTE - 1; // Start from the last bit
        int current_num = prompt[i];
        while (j >= 0) // Iterate over the bits in reverse order
        {
            a_bit[j] = current_num % 2;
            current_num /= 2;
            j--;
        }
        for (int k = 0; k < BITS_IN_BYTE; k++)
        {
            print_bulb(a_bit[k]);
        }
        printf("\n");
    }
}


void print_bulb(int bit)
{
    if (bit == 0)
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (bit == 1)
    {
        // Light emoji
        printf("\U0001F7E1");
    }
}
