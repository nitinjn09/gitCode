#include <stdio.h>

float tax_cal (float);
int main ()
{
    int age = 28, years = 100 - age, time = 12, i;
    float amount = 22269, sum[years], interest[years], tax[years];
    for (i = 0; i < years; i++) {
        sum[i] = 0;
        interest[i] = 0;
        tax[i] = 0;
    }
    
    printf("year    age    interest     base-sum      total-sum    tax\n\n");
    for (i = 1; i <= years; i++, age++) {
        sum[i] = sum[i-1] + interest[i-1] - tax[i-1];
        if (i <= time) {
            sum[i] = sum[i] + amount;
        }
        interest[i] = sum[i] * 0.04;
        tax[i] = tax_cal(interest[i]);
        printf("%d      %d       %d       %d            %d       %d\n",i, age, (int)interest[i], (int)sum[i], (int)(sum[i] + interest[i]), (int)tax[i]);
    }

    return 0;
}


float tax_cal (float amount) 
{
    if (amount <= 250000) {
        return 0;
    } else if (amount <= 500000) {
        return (0.1 * (amount-250000));
    } else if (amount < 1000000) {
        return ((0.1* 250000) + (0.2*(amount-500000)));
    } else {
        return ((0.1*250000) + (0.2*500000) + (0.3 * (amount-1000000)));
    }
}
