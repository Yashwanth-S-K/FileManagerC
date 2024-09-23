#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_ITERATIONS 100

// Function to execute fileManager with a specific command
void run_fileManager(const char *input_command) {
    char command[100];

    // Format the command to run fileManager and pass the input
#ifdef _WIN32
    sprintf(command, "echo %s | fileManager.exe", input_command);  // For Windows
#else
    sprintf(command, "echo %s | ./fileManager", input_command);    // For Linux
#endif

    // Run the fileManager executable with the command
    system(command);
}

// Function to measure the execution time of fileManager operations
double measure_execution_time(const char *command) {
    clock_t start, end;

    start = clock();
    run_fileManager(command);
    end = clock();

    return ((double)(end - start)) / CLOCKS_PER_SEC;
}

int main() {
    double execution_times[NUM_ITERATIONS];  // Array to store execution times
    char folder_name[50], file_name[50];
    clock_t start, end;

    // Iterating over multiple executions of fileManager with different tasks
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        // Generate unique folder and file names for each iteration
        sprintf(folder_name, "test_folder_%d", i);
        sprintf(file_name, "test_folder_%d/test_file_%d.txt", i, i);

        execution_times[i] = 0;

        // Create folder via fileManager
        printf("Creating folder: %s\n", folder_name);
        execution_times[i] += measure_execution_time("1\n");  // Assuming '1' corresponds to 'Create folder' in fileManager

        // Add a small delay or task simulation (optional)
#ifdef _WIN32
        Sleep(1);  // Sleep for 1 second (Windows)
#else
        sleep(1);  // Sleep for 1 second (Linux)
#endif

        // Delete folder via fileManager
        printf("Deleting folder: %s\n", folder_name);
        execution_times[i] += measure_execution_time("3\n");  // Assuming '3' corresponds to 'Delete folder' in fileManager

        // Print the execution time for each iteration
        printf("Iteration %d execution time: %.6f seconds\n", i + 1, execution_times[i]);
    }

    // Calculating average execution time over all iterations
    double total_time = 0;
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        total_time += execution_times[i];
    }

    printf("\nAverage execution time for %d iterations: %.6f seconds\n", NUM_ITERATIONS, total_time / NUM_ITERATIONS);

    // Loop to print all execution times stored in the array
    printf("\nExecution times for each iteration:\n");
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        printf("Execution time for iteration %d: %.6f seconds\n", i + 1, execution_times[i]);
    }

    return 0;
}
