import cs50


def main():
    # prompt user for a number between 1 and 8 using get int
    while True:
        height = cs50.get_int("Entrer une hauteur : ")
        if height >= 1 and height <= 8:
            break

    # looping process
    for i in range(1, height + 1):
        print(" " * (height - i) + "#" * i + "  " + "#" * i)


main()