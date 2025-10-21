#include <stdio.h>
int main(void) {
    double sales[4][5]= {0.0};
    double productSales[5]= {0.0};
    puts("Enter the salesperson(0-3), product(0-4), and total sales:");
    puts("Enter -1 for salespersson to end input.");
    unsigned int salesPerson = 0;
    scanf("%u", &salesPerson);
    while (salesPerson != -1) {
        unsigned int product = 0;
        double totalSales = 0.0;
        scanf("%u %lf", &product, &totalSales);
        sales[salesPerson][product] += totalSales;
        productSales[product] += totalSales;
        scanf("%u", &salesPerson);
    }
    puts("     0    1    2    3    4");
    for (unsigned int i = 0; i < 4; i++) {
        printf("%u: ", i);
        double totalSalesPerson = 0.0;
        for (unsigned int j = 0; j < 5; j++) {
            printf("%.2lf ", sales[i][j]);
            totalSalesPerson += sales[i][j];
        }
        printf("  %.2lf\n", totalSalesPerson);
    }    
    for (unsigned int i = 0; i < 5; i++) {
        printf("%.2lf   ", productSales[i]);
    }
return 0;
}   