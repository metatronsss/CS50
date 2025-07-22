import cs50

quarters, dimes, nickles, pennies = 0.25, 0.1, 0.05, 0.01
amount_of_quarters, amount_of_dimes, amount_of_nickles, amount_of_pennies = 0, 0, 0, 0
while True:
    n = cs50.get_float("Change owed: ")
    if n > 0:
        break
while n > 0:
    n = round(n, 4)
    if n >= 0.25:
        amount_of_quarters = int(n / quarters)
        n = n % quarters
    elif 0.1 <= n and n < 0.25:
        amount_of_dimes = int(n / dimes)
        n = n % dimes
    elif 0.05 <= n and n < 0.1:
        amount_of_nickles = int(n / nickles)
        n = n % nickles
    else:
        amount_of_pennies = int(n / pennies)
        n = n % pennies
Change = amount_of_quarters + amount_of_dimes + amount_of_nickles + amount_of_pennies
print(f"{Change}")
