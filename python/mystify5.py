import pygame
import random

# Initialize Pygame
pygame.init()

# Screen dimensions
SCREEN_WIDTH = 800
SCREEN_HEIGHT = 600

# Colors
BLACK = (0, 0, 0)
WHITE = (255, 255, 255)

# Line class to represent each line
class Line:
    def __init__(self):
        self.segments = []
        self.color = (random.randint(0, 255), random.randint(0, 255), random.randint(0, 255))
        self.speed = random.randint(1, 5)

        # Generate initial positions and directions for segments
        for _ in range(10):
            start_pos = [random.randint(0, SCREEN_WIDTH), random.randint(0, SCREEN_HEIGHT)]
            direction = [random.choice([-1, 1]), random.choice([-1, 1])]
            self.segments.append((start_pos, direction))

    def move(self):
        # Move each segment of the line
        for i, (pos, direction) in enumerate(self.segments):
            self.segments[i] = ([pos[0] + self.speed * direction[0], pos[1] + self.speed * direction[1]], direction)

            # Check if the segment hits the screen edges
            if pos[0] <= 0 or pos[0] >= SCREEN_WIDTH:
                self.segments[i] = (pos, [-direction[0], direction[1]])
            if pos[1] <= 0 or pos[1] >= SCREEN_HEIGHT:
                self.segments[i] = (pos, [direction[0], -direction[1]])

# Initialize screen
screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
pygame.display.set_caption("Mystify Screensaver")

# Clock for controlling the frame rate
clock = pygame.time.Clock()

# List to hold lines
lines = [Line() for _ in range(10)]  # Create 10 lines

# Main loop
running = True
while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    # Clear the screen
    screen.fill(BLACK)

    # Move and draw lines
    for line in lines:
        line.move()
        for segment in line.segments:
            pygame.draw.line(screen, line.color, segment[0], (segment[0][0] + segment[1][0], segment[0][1] + segment[1][1]), 1)

    # Update the display
    pygame.display.flip()

    # Cap the frame rate
    clock.tick(30)  # Limit to 30 frames per second

# Quit Pygame
pygame.quit()

