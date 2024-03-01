#include "screen1.h"
#include <stdio.h>

// Define functions for Screen 1
void screen1_init(void) {
    printf("Initializing Screen 1...\n");
}

int screen1_update(void) {
    printf("Updating Screen 1...\n");
    // Example: Switch to next screen if a condition is met
    if (1) {
        return 1; // ID of the next screen
    }
    return -1; // Continue with the current screen
}

void screen1_draw(void) {
    printf("Drawing Screen 1...\n");
}

