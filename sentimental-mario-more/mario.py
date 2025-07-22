import sys
import cs50

while True:
    n = cs50.get_int("Height: ")
    if n > 0 and n <= 8:
        # if n == 1:
        # print("", end="")
        break

# Space+# equal to n
for i in range(n):
    for j in range(n-i-1):
        print(" ", end="")
    for k in range(i+1):
        print("#", end="")
    print("  ", end="")
    for m in range(i+1):
        print("#", end="")
    print("")
