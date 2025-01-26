#include <stdio.h>
#include <cs50.h>

typedef struct
{
    string name;
    int vote;
}
candidate;

candidate get_candidate(string prompt);

int main(void)
{
    candidate president = get_candidate("Enter a candidate: ");
    printf("%s\n", president.name);
    printf("%i\n", president.vote);
}

candidate get_candidate(string prompt)
{
    printf("%s\n", prompt);

    candidate c;
    c.name = get_string("Enter a name: ");
    c.vote = get_int("Enter a number of vote: ");
    return c;
}