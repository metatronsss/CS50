import cs50


def main():
    text = cs50.get_string("Text: ")
    # 預計拿來放單字
    each_word = ""
    # 含空白以及標點符號的字母數
    # 空白前或後的text[i]們組成一組即為一個單字，先不考慮縮寫
    length = len(text)
    # print(f"{length}")
    length_letters = 0
    j, k = 0, 0

    # Lucky 7
    ascii_values = [7] * len(text)
    for i in range(length):
        # 移除空白以及標點符號的字母數 A-Z a-z
        ascii_values[i] = ord(text[i])
        if (ascii_values[i] >= 65 and ascii_values[i] <= 90) or (ascii_values[i] >= 97 and ascii_values[i] <= 122):
            length_letters += 1
            # 字母們組在一起變成一個單字
        elif (ascii_values[i] == 32):
            # 遇到空白準備把之後的字母加到第二組單字
            j += 1
        # Before period, question mark or exclamation mark is A sentence
        elif ascii_values[i] == 33 or ascii_values[i] == 46 or ascii_values[i] == 63:
            # 遇到空白準備把之後的字母加到第二組單字
            k += 1
    # 最後一個字接著是標點符號但後面沒有空白了 也要算一個單字
    j += 1

    # print(f"{length_letters}, {j}, {k}")
    read_grade = readability_tests(length_letters, j, k)
    print(f"{read_grade}")

# rounded to the nearest integer. higher “Grade 16+”; less than 1 “BeforeGrade 1”.
# index = 0.0588 * L - 0.296 * S - 15.8.
# L是每一百個單字有幾個字母, S是100個單字有多少個句子.字母數/單字數*單字數/100
# 24個單字有96個字母，那100個字 就會有96*(100/24) 400
# 24個單字1句，那100個單字就會有1*(100/24) 4.16666666


def readability_tests(letters, words, sentences):
    L = letters * (100.0 / words)
    S = sentences * (100.0 / words)

    # rounded to the nearest integer.
    index = round(0.0588 * L - 0.296 * S - 15.8)
    grade = ["Before Grade 1", "Grade 1",  "Grade 2",  "Grade 3",  "Grade 4",
             "Grade 5",        "Grade 6",  "Grade 7",  "Grade 8",  "Grade 9",
             "Grade 10",       "Grade 11", "Grade 12", "Grade 13", "Grade 14",
             "Grade 15",       "Grade 16", "Grade 16+"]
    # check point for all elements of formula
    # print(f"letters: {letters} words: {words} sentences {sentences} L: {L} S: {S} index: {index}")

    if index < 1:
        return grade[0]
    elif index > 16:
        return grade[17]
    else:
        return grade[index]


if __name__ == "__main__":
    main()
