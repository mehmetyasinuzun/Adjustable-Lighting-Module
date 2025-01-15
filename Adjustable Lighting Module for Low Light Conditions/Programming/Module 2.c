#include <stdio.h>
#include <stdlib.h> // For file operations
#include <string.h> // For string manipulation

// Function to calculate output voltage based on input voltage and gain
double calculateOutputVoltage(double inputVoltage, double R1, double R2) {
    return -(R2 / R1) * inputVoltage;
}

int main() {
    // Input voltage from the 7905 regulator
    const double inputVoltage = -5.0; 
    // Fixed resistance (R1) and variable resistance (R2)
    const double R1 = 5000.0; // Fixed resistance in ohms
    double R2; // Variable resistance in ohms

    FILE *file;

    // Print descriptions
    printf("Adjustable Lighting Module Simulation\n");
    printf("---------------------------------------------\n");
    printf("Input Voltage (Vin): -5 V\n");
    printf("Fixed Resistance (R1): 5000 ohms\n\n");

    // Print formula for calculation
    printf("Formula: Vout = -(R2 / R1) * Vin\n\n");

    // Print table header
    printf("%-20s %-20s %-20s %-20s\n", "Vout (Output Voltage)", "Gain (K)", "R2 (ohms)", "R1 (ohms)");
    printf("%-20s %-20s %-20s %-20s\n", "--------------------", "--------------------", "--------------------", "--------------------");

    // Open file to save results temporarily
    file = fopen("module_2_result.txt", "w");
    if (file == NULL) {
        printf("Error: Unable to create file for temporary storage.\n");
        return 1;
    }

    fprintf(file, "Adjustable Lighting Module Simulation\n");
    fprintf(file, "---------------------------------------------\n");
    fprintf(file, "Input Voltage (Vin): -5 V\n");
    fprintf(file, "Fixed Resistance (R1): 5000 ohms\n\n");
    fprintf(file, "Formula: Vout = -(R2 / R1) * Vin\n\n");
    fprintf(file, "%-20s %-20s %-20s %-20s\n", "Vout (Output Voltage)", "Gain (K)", "R2 (ohms)", "R1 (ohms)");
    fprintf(file, "%-20s %-20s %-20s %-20s\n", "--------------------", "--------------------", "--------------------", "--------------------");

    // Iterate over R2 values and calculate Vout
    for (R2 = 0; R2 <= 10000; R2 += 1000) { // Increment R2 in steps of 1 kOhm
        double gain = R2 / R1; // Calculate gain
        double outputVoltage = calculateOutputVoltage(inputVoltage, R1, R2); // Calculate Vout

        // Limit output voltage to range (0-10V)
        if (outputVoltage > 10.0) outputVoltage = 10.0;
        if (outputVoltage < 0.0) outputVoltage = 0.0;

        // Print results
        printf("%-20.2f %-20.2f %-20.0f %-20.0f\n", outputVoltage, gain, R2, R1);
        fprintf(file, "%-20.2f %-20.2f %-20.0f %-20.0f\n", outputVoltage, gain, R2, R1);
    }

    fclose(file);

    // Ask user if they want to save the results
    char saveResults;
    printf("\nDo you want to save the results to a file? (y/n): ");
    scanf(" %c", &saveResults);

    if (saveResults == 'n' || saveResults == 'N') {
        remove("module_2_result.txt");
        printf("Results discarded.\n");
    } else {
        printf("Results saved to 'module_2_result.txt'.\n");
    }

    return 0;
}

