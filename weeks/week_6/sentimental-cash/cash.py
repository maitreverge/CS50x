import cs50


def main():
    # prompt user to a positive value
    while True:
        change = cs50.get_float("Change owed: ")
        if change > 0:
            break

    # calculate coins
    quarters = int(change // 0.25)
    dimes = int((change - (quarters * 0.25)) // 0.1)
    nickels = int((change - (quarters * 0.25) - (dimes * 0.1)) // 0.05)
    pennies = int((change - (quarters * 0.25) - (dimes * 0.1) - (nickels * 0.05)) // 0.01)

    print(quarters + dimes + nickels + pennies)


main()