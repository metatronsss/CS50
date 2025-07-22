cd ..
#include <stdio.h>
#include <cs50.h>
// A/B==C 取整數找出硬幣數量 A mod B == D算出剩餘金額，再用下一個等級的硬幣去重複以上動作 Multiple times&Remainder
// C必須無條件捨棄小數位
int main (void)
{
    int quarters = 25, dimes = 10, nickles = 5, pennies = 1;
    int n = get_int("Change owed: ");
    int amount_of_quarters = 0 , amount_of_dimes = 0, amount_of_nickles=0 , amount_of_pennies=0;
    while(n<1)
    {
        n = get_int("Change owed: ");
    }
    while(n>0)
    {
        if(n>=25)
        {
            amount_of_quarters  = n / quarters;
            n = n % quarters;//remainders_of_quqrters
        }
        else if(10<=n&&n<25)
        {
            amount_of_dimes  = n / dimes;
            n = n % dimes;//remainders_of_dimes
            //printf("%d\n", amount_of_dimes);
            //printf("%d\n", n);
        }
        else if(5<=n&&n<10)
        {
            amount_of_nickles  = n / nickles;
            n = n % nickles;//remainders_of_nickles
            //printf("%d\n", amount_of_nickles);
            //printf("%d\n", n);
        }
        else
        {
            amount_of_pennies  = n / pennies;
            n = n % pennies;//remainders_of_pennies
            //printf("%d\n", amount_of_pennies);
            //printf("%d\n", n);
        }
    }
    int Change = amount_of_quarters+amount_of_dimes+amount_of_nickles+amount_of_pennies;//Amount_of_change
    printf("%d\n", Change);
}
