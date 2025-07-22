#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// not a decimal digit, should print the message
// Usage: ./caesar key and return from main a value of 1.
int alphabat_26_no_repeat(string k);
int change(char *plaintext, char *key, int text_length);
int main(int argc, string argv[])
{
    if (argv[1] == NULL)
    {
        argv[1] = 0;
        printf("Usage: ./caesar key\n");
        return 1;
    }
    // check point for argv
    // printf("%s %s %s %i\n", argv[0], argv[1],argv[2], argc);
    // without any command-line arguments or with more than one command-line argument,
    // print an error message and return 1
    int a = alphabat_26_no_repeat(argv[1]);
    if (argc == 2 && argv[1] != NULL)
    {
        // checkpoint for which case
        // printf("Test\n");
        if (a == false)
        {
            printf("Usage: ./substitution key\n");
            return 1;
        }
        else
        {
            string plain = get_string("plaintext: ");
            int plain_length = strlen(plain);
            change(plain, argv[1], plain_length);
            return 0;
        }
    }
    else
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
}
int alphabat_26_no_repeat(string k)
{
    // 字母26碼就正確
    // 不論大小寫 大寫保持大寫 小寫保持小寫
    int length = strlen(k);
    int tmp = 0;
    char k_tmp2[length];
    k_tmp2[length] = '\0';
    char alphabat_list[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
                              'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    if (length != 26)
    {
        return false;
    }
    int check = 0;
    for (int i = 0; i < length; i++)
    {
        // 通通變大寫，65-90加總就是2015
        if ((k[i] >= 65 && k[i] <= 90) || (k[i] >= 97 && k[i] <= 122))
        {
            check += 0;
            // 字母不可重複 先統一大寫去比較 之後記得要變回來
            k_tmp2[i] = k[i];
            // Bubble sort
            for (int j = 0; j < i; j++)
            {
                // 跟上一個比，小的往左放
                if (toupper(k_tmp2[j]) > toupper(k_tmp2[i]))
                {
                    tmp = k_tmp2[j];
                    k_tmp2[j] = k_tmp2[i];
                    k_tmp2[i] = tmp;
                }
            }
        }
        else
        {
            check += 1;
        }
        // checkpoint for each char
        // printf("此項為%i check是%i\n", k[i], check);
    }
    // check point for key sorting
    // printf("%s\n%s\n", k_tmp2, k);
    for (int i = 0; i < length; i++)
    {
        if (toupper(k_tmp2[i]) == alphabat_list[i])
        {
            check += 0;
        }
        else
        {
            check += 1;
        }
    }
    if (check == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
int change(char *plaintext, char *key, int text_length)
{
    char alphabat_list[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
                              'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    char cipher[text_length + 1];
    cipher[text_length] = '\0';
    for (int i = 0; i < text_length; i++)
    {
        // 文本的字母對應到alphabat_list，換成對應key_list 重點在陣列位置互換
        for (int j = 0; j < 26; j++)
        {
            if (toupper(plaintext[i]) == alphabat_list[j])
            {
                // 原本就是大寫就直接放
                if (toupper(plaintext[i]) == plaintext[i])
                {
                    cipher[i] = toupper(key[j]);
                }
                // 若非就是小寫 要放小的
                else
                {
                    cipher[i] = tolower(key[j]);
                }
            }
            // 非對應字母則不動
            else if (toupper(plaintext[i]) < 65 || toupper(plaintext[i]) > 90)
            {
                cipher[i] = plaintext[i];
            }
        }
    }
    printf("ciphertext: %s\n", cipher);
    return 0;
}
