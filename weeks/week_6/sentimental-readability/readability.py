from cs50 import get_string
import math


# functions prototypes :

# Count letters
def nb_letters(text):
    total = 0
    for char in text:
        if char.isalpha():
            total += 1
    return total

# count words


def nb_words(text):
    total = len(text.split())
    return total


# count sentences
def nb_sentences(text):
    total = 0
    for i in range(len(text)):
        if (text[i] == '.' or text[i] == '!' or text[i] == '?') and (i == len(text) - 1 or text[i + 1] == ' '):
            total += 1
    return total


def main():

    # prompt
    prompt = get_string("Prompt: ")

    # call functions
    letters = nb_letters(prompt)
    words = nb_words(prompt)
    sentences = nb_sentences(prompt)

    # calculate index 1/2
    L = (letters / words) * 100
    S = (sentences / words) * 100

    # calculate index 2/2
    index = round((0.0588 * L) - (0.296 * S) - 15.8)

    # print index depending on score
    if index < 1:
        print("Before Grade 1")
    elif index < 16:
        print(f"Grade {index}")
    else:
        print("Grade 16+")


main()