#include <stdio.h>

#define MAX_PASSENGERS 10

// Station structure
typedef struct {
    char name[20];
    int price;
} Station;

int main(void) {
    // Define available stations and their base adult fares
    Station stations[4] = {
        {"Tokyo", 150},
        {"Shinjuku", 210},
        {"Shibuya", 210},
        {"Akihabara", 150}
    };
    
    int choice;
    int num_adults = 0, num_children = 0;
    int payment_method;
    int suica_balance = 2000; // Starting IC card balance
    int cash_inserted = 0;
    int total_fare = 0;
    
    printf("=======================================\n");
    printf("    WELCOME TO JR TICKET MACHINE       \n");
    printf("=======================================\n");
    
    // 1. Station Selection
    printf("\n[Select Destination Station]\n");
    for (int i = 0; i < 4; i++) {
        printf("%d. %-10s (Adult: %d JPY / Child: %d JPY)\n", 
               i + 1, stations[i].name, stations[i].price, stations[i].price / 2);
    }
    
    printf("Enter station number (1-4): ");
    if (scanf("%d", &choice) != 1 || choice < 1 || choice > 4) {
        printf("Invalid choice. Operation cancelled.\n");
        return 1;
    }
    int selected_idx = choice - 1;
    
    // 2. Passenger Count Selection
    printf("\n[Select Number of Passengers]\n");
    printf("Enter number of Adults: ");
    if (scanf("%d", &num_adults) != 1 || num_adults < 0 || num_adults > MAX_PASSENGERS) {
        printf("Invalid number of adults. Operation cancelled.\n");
        return 1;
    }
    
    printf("Enter number of Children: ");
    if (scanf("%d", &num_children) != 1 || num_children < 0 || num_children > MAX_PASSENGERS) {
        printf("Invalid number of children. Operation cancelled.\n");
        return 1;
    }
    
    if (num_adults == 0 && num_children == 0) {
        printf("No passengers selected. Operation cancelled.\n");
        return 1;
    }
    
    // Calculate Fares (Children are 50% off)
    total_fare = (num_adults * stations[selected_idx].price) + 
                 (num_children * (stations[selected_idx].price / 2));
                 
    printf("\n--- Ticket Breakdown ---\n");
    printf("Destination: %s\n", stations[selected_idx].name);
    if (num_adults > 0) printf("Adults: %d x %d JPY\n", num_adults, stations[selected_idx].price);
    if (num_children > 0) printf("Children: %d x %d JPY\n", num_children, stations[selected_idx].price / 2);
    printf("Total Amount Due: %d JPY\n", total_fare);
    printf("------------------------\n");
    
    // 3. Payment Method Selection
    printf("\n[Select Payment Method]\n");
    printf("1. Cash\n");
    printf("2. IC Card (Suica/Pasmo) [Current Balance: %d JPY]\n", suica_balance);
    printf("Select payment option (1-2): ");
    if (scanf("%d", &payment_method) != 1 || (payment_method != 1 && payment_method != 2)) {
        printf("Invalid payment method. Operation cancelled.\n");
        return 1;
    }
    
    // 4. Processing Payment
    if (payment_method == 1) {
        // Cash Logic
        printf("\nInsert Cash (JPY): ");
        if (scanf("%d", &cash_inserted) != 1 || cash_inserted < 0) {
            printf("Invalid amount. Operation cancelled.\n");
            return 1;
        }
        
        if (cash_inserted < total_fare) {
            printf("Insufficient cash inserted. Refunding %d JPY.\n", cash_inserted);
            return 1;
        }
        
        int change = cash_inserted - total_fare;
        printf("\nPayment successful!\n");
        if (change > 0) {
            printf("Your change: %d JPY\n", change);
        }
    } else {
        // IC Card Logic
        if (suica_balance < total_fare) {
            printf("\nIC Card Error: Insufficient funds. Balance is only %d JPY.\n", suica_balance);
            return 1;
        }
        
        suica_balance -= total_fare;
        printf("\nPayment successful! (IC Card tapped)\n");
        printf("Remaining IC Card Balance: %d JPY\n", suica_balance);
    }
    
    // 5. Ticket Dispensing Simulation
    printf("\n=======================================\n");
    printf("         PRINTING TICKETS...           \n");
    for (int i = 0; i < num_adults; i++) {
        printf(" [ JR TICKET | %-8s | ADULT | %d JPY ]\n", stations[selected_idx].name, stations[selected_idx].price);
    }
    for (int i = 0; i < num_children; i++) {
        printf(" [ JR TICKET | %-8s | CHILD | %d JPY ]\n", stations[selected_idx].name, stations[selected_idx].price / 2);
    }
    printf("=======================================\n");
    printf(" Thank you for riding JR! Have a nice trip.\n");
    
    return 0;
}