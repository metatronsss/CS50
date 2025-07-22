#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>

//American Express uses 15-digit numbers, MasterCard uses 16-digit numbers, and Visa uses 13- and 16-digit numbers.
//American Express numbers start with 34 or 37; MasterCard numbers start with 51, 52, 53, 54, or 55; Visa numbers start with 4
//陣列中 偶數位*2相加，且若有*2大於10的拆成兩個數字，再全部相加為sum_double_even
//奇數位相加後sum_odd 與上述兩倍相加後的奇數相加 sum_up
//if sum_up mod 10 == 0 then true
int main (void){
    long n = get_long("Number: ");
    char str_n[16]="";
    sprintf(str_n, "%ld", n);
    //printf("%s\n", str_n);
    //printf("%c %c\n", str_n[0], str_n[1]);
    //Combine to 2 cs to string
    char combined_str[3] = {str_n[0], str_n[1], '\0'};
    //Convert to digits
    int combined_num = atoi(combined_str);
    //printf("%d\n", combined_num);
    int sum_double_even = 0, sum_odd = 0;
    int sum_up = 0;
    //Length of array
    //printf("%zu\n", strlen(str_n));
    for(int i=strlen(str_n)-2;i>=0;i=i-2)
    {
        //先乘以兩倍
        int tmp_even = (str_n[i]-'0')*2;
        //判斷是否有大於10，沒有就直接加起來
        if((tmp_even)<10){
            sum_double_even += tmp_even;
        }
        //大於10，要把相除的值與餘數相加
        else
        {
            sum_double_even += tmp_even/10+tmp_even%10;
        }
        //sum_double_even檢查點
        //printf("%d %d \n", i, tmp_even);
    }
    //分隔用
    //printf("=====\n");
    for(int j=strlen(str_n)-1;j>=0;j=j-2)
    {
        //sum_odd = sum_odd+str_n[j];
        sum_odd += str_n[j]-'0';
        //sum_odd檢查點
        //printf("%d %c \n", j, str_n[j]);
    }
    sum_up = sum_double_even+sum_odd;
    //sum_up檢查點
    //printf("%d %d %d\n", sum_double_even, sum_odd,sum_up);
    if(sum_up % 10 ==0){
        if(strlen(str_n)==15&&(combined_num==34 || combined_num==37))
        {
            printf("AMEX\n");
        }
        else if(strlen(str_n)==16&&(combined_num>50&&combined_num<56))
        {
            printf("MASTERCARD\n");
        }
        else if((strlen(str_n)==13||strlen(str_n)==16)&&(combined_num>=40&&combined_num<50))
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
            printf("INVALID\n");
    }

}
