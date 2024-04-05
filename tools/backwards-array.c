#include <stdio.h>

int main() {
    int rows = 3; // Number of rows
    int cols = 4; // Number of columns

    // 1D array representing a 2D array
    int array1D[] = {1, 2, 3, 4,
                     5, 6, 7, 8,
                     9, 10, 11, 12};

    // Access each row in the opposite order
    for (int i = rows - 1; i >= 0; i--) {
        // Calculate the starting index of the current row
        int row_start_index = i * cols;

        // Access elements of the current row
        for (int j = 0; j < cols; j++) {
            // Calculate the index of the current element
            int index = row_start_index + j;
            
            // Access the current element
            printf("%d ", array1D[index]);
        }
        printf("\n");
    }

    return 0;
}
