#include <stdio.h>

int main(void)
{
    double consumption;
    double rate = 30.0;
    double normal_limit = 300.0;
    double cost;

    printf("Smart Electricity Meter\n\n");

    printf("Enter electricity consumption (kWh): ");
    if (scanf("%lf", &consumption) != 1) {
        printf("Error: invalid input.\n");
        return 1;
    }

    if (consumption < 0.0) {
        printf("Error: consumption cannot be negative.\n");
        return 1;
    }

    cost = consumption * rate;

    printf("\n");
    printf("Electricity Usage: %.1f kWh\n", consumption);
    printf("Electricity Rate: %.0f yen/kWh\n", rate);
    printf("Estimated Cost: %.0f yen\n", cost);

    if (consumption > normal_limit) {
        printf("Usage Status: HIGH CONSUMPTION\n");
    } else {
        printf("Usage Status: NORMAL\n");
    }

    return 0;
}
