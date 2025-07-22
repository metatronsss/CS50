import cs50

# American Express uses 15-digit numbers, MasterCard uses 16-digit numbers, and Visa uses 13- and 16-digit numbers.
# American Express numbers start with 34 or 37; MasterCard numbers start with 51, 52, 53, 54, or 55; Visa numbers start with 4
# 陣列中 偶數位*2相加，且若有*2大於10的拆成兩個數字，再全部相加為sum_double_even
# 奇數位相加後sum_odd 與上述兩倍相加後的奇數相加 sum_up
# if sum_up mod 10 == 0 then true
n = input("Number: ")
# c sprintf(str_n, "%ld", n)
str_n = str(n)
combined_str = str_n[0] + str_n[1]
combined_num = int(combined_str)
sum_double_even, sum_odd, sum_up = 0, 0, 0

for i in range(len(str_n)-2, -1, -2):
    # python don't need stmp_even = (str_n[i]-'0')*2
    tmp_even = int(str_n[i]) * 2
    # 判斷是否有大於10，沒有就直接加起來
    if tmp_even < 10:
        sum_double_even += tmp_even
        # 大於10，要把相除的值與餘數相加
    else:
        # round down to the nearest integer
        sum_double_even += tmp_even // 10 + tmp_even % 10

for j in range(len(str_n)-1, -1, -2):
    # python don't need sum_odd += str_n[j] - '0'
    sum_odd += int(str_n[j])
    sum_up = sum_double_even + sum_odd
if sum_up % 10 == 0:
    if len(str_n) == 15 and (combined_num == 34 or combined_num == 37):
        print("AMEX")
    elif len(str_n) == 16 and (combined_num > 50 and combined_num < 56):
        print("MASTERCARD")
    elif (len(str_n) == 13 or len(str_n) == 16) and (combined_num >= 40 and combined_num < 50):
        print("VISA")
    else:
        print("INVALID")
else:
    print("INVALID")
