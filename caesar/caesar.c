#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// not a decimal digit, should print the message
// Usage: ./caesar key and return from main a value of 1.
int pure(string k);
string rotate(char *p, int K);
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
    int a = pure(argv[1]);
    if (argc == 2 && argv[1] != NULL)
    {
        // checkpoint for which case
        // printf("Test\n");
        if (a == false)
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
        else
        {
            int key = atoi(argv[1]);
            // plaintext: (with two spaces but without a newline)
            // ciphertext: (with one space but without a newline)
            string plain = get_string("plaintext:  ");
            rotate(plain, key);
            return 0;
        }
    }
    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
}
int pure(string k)
{
    // 只有數字就正確
    int length = strlen(k);
    int check = 0;
    for (int i = 0; i <= length - 1; i++)
    {
        if (k[i] >= 48 && k[i] <= 57)
        {
            check += 0;
        }
        else
        {
            check += 1;
        }
        // checkpoint for each char
        // printf("此項為%i check是%i\n", k[i], check);
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
// plaintext p; rotate k, % 26 if k >2 6 ; cipher c
// only rotate position of alphabat, no change upper or lower and non-alphabat
string rotate(char *p, int K)
{
    int length_text = strlen(p);
    int r_tmp = K % 26, c_tmp = 0;
    char cipher[length_text + 1];
    cipher[length_text] = '\0';
    for (int j = 0; j < length_text; j++)
    {
        // Z to A (and from z to a); not a letter, same char unchanged.
        // c[i] = (p[i]+k)%26
        // 怎麼繞一圈回來 一樣維持在A-Z a-z 是關鍵
        if (p[j] >= 65 && p[j] <= 90)
        {
            c_tmp = p[j] + r_tmp;
            // A-Z 循環
            if (c_tmp > 90 && c_tmp < 115)
            {
                c_tmp -= 26;
            }
        }
        else if (p[j] >= 97 && p[j] <= 122)
        {
            c_tmp = p[j] + r_tmp;
            // a-z 循環
            if (c_tmp > 122)
            {
                c_tmp -= 26;
            }
        }
        else
        {
            c_tmp = p[j];
        }
        // 把換好的丟給c[j]
        cipher[j] = c_tmp;
    }
    printf("ciphertext: %s\n", cipher);
    return 0;
}
