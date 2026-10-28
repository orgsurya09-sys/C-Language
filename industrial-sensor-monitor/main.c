#include <stdio.h>

int main(void)
{
    double temperature;
    double voltage;
    double pressure;
    int all_normal = 1;

    printf("Industrial Sensor Monitor\n\n");

    printf("Temperature (C): ");
    if (scanf("%lf", &temperature) != 1) {
        printf("Error: invalid temperature.\n");
        return 1;
    }

    printf("Voltage (V): ");
    if (scanf("%lf", &voltage) != 1) {
        printf("Error: invalid voltage.\n");
        return 1;
    }

    printf("Pressure (bar): ");
    if (scanf("%lf", &pressure) != 1) {
        printf("Error: invalid pressure.\n");
        return 1;
    }

    printf("\n");

    printf("Temperature: %.1f C\n", temperature);
    if (temperature < 0.0 || temperature > 80.0) {
        printf("Status: WARNING\n");
        all_normal = 0;
    } else {
        printf("Status: NORMAL\n");
    }

    printf("\nVoltage: %.1f V\n", voltage);
    if (voltage < 200.0 || voltage > 240.0) {
        printf("Status: WARNING\n");
        all_normal = 0;
    } else {
        printf("Status: NORMAL\n");
    }

    printf("\nPressure: %.1f bar\n", pressure);
    if (pressure < 2.0 || pressure > 8.0) {
        printf("Status: WARNING\n");
        all_normal = 0;
    } else {
        printf("Status: NORMAL\n");
    }

    printf("\n------------------------------\n");
    if (all_normal) {
        printf("ALL SENSORS NORMAL\n");
    } else {
        printf("WARNING\n");
    }

    return 0;
}
