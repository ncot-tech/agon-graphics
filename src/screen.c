#include "screen.h"
#include <stdio.h>
#include <stdlib.h>

// Define a type for each screen
struct Screen {
    void (*init)(void);
    int (*update)(void);
    void (*draw)(void);
    // Add any other screen-specific functions or data here
};

// Define an array of screens
Screen *screens[MAX_SCREENS];
int num_screens = 0;

// Function to define screen
void define_screen(void (*init)(void), int (*update)(void), void (*draw)(void)) {
    // Check if there's still space in the array
    if (num_screens < MAX_SCREENS) {
        // Create the Screen struct
        Screen *new_screen = (Screen *)malloc(sizeof(Screen));
        if (new_screen != NULL) {
            new_screen->init = init;
            new_screen->update = update;
            new_screen->draw = draw;

            // Add the new screen to the array
            screens[num_screens++] = new_screen;
        }
    }
}

// Function to execute the next screen based on the current screen's update function
void run_screens() {
    static int current_screen_index = 0;
    
    // Get the current screen
    Screen *current_screen = screens[current_screen_index];
    if (current_screen == NULL || current_screen->update == NULL) {
        return; // Invalid current screen
    }

    // Call the update function to determine the next screen
    int next_screen_id = current_screen->update();
    if (next_screen_id != -1 && next_screen_id < num_screens && next_screen_id != current_screen_index) {
        // Only update the screen index if it's different from the current one
        current_screen_index = next_screen_id;
        current_screen = screens[current_screen_index];
        
        // Call the init function if needed
        if (current_screen->init != NULL) {
            current_screen->init();
        }
    }    
}
