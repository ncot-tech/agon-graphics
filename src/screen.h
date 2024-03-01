#ifndef SCREEN_H
#define SCREEN_H

// Forward declaration of Screen struct
struct Screen;

// Define a type for each screen
typedef struct Screen Screen;
#define MAX_SCREENS 10
// Function prototypes for screen-related functions
void define_screen(void (*init)(void), int (*update)(void), void (*draw)(void)); 
void run_screens();
#endif /* SCREEN_H */

