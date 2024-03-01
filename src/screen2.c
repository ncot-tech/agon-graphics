#include "screen2.h"
#include <stdio.h>

// Define functions for Screen 1
void screen2_init(void) {
    printf("Initializing Screen 2...\n");
}

int screen2_update(void) {
    printf("Updating Screen 2...\n");
    // Example: Switch to next screen if a condition is met
    if (0) {
        return 0; // ID of the next screen
    }
    return -1; // Continue with the current screen
}

void screen2_draw(void) {
    printf("Drawing Screen 2...\n");
}

