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
        self.start_pos = (random.randint(0, SCREEN_WIDTH), random.randint(0, SCREEN_HEIGHT))
        self.end_pos = (random.randint(0, SCREEN_WIDTH), random.randint(0, SCREEN_HEIGHT))
        self.color = (random.randint(0, 255), random.randint(0, 255), random.randint(0, 255))
        self.speed = random.randint(1, 5)
        self.direction = (random.choice([-1, 1]), random.choice([-1, 1]))

    def move(self):
        # Move the line
        self.start_pos = (self.start_pos[0] + self.speed * self.direction[0], self.start_pos[1] + self.speed * self.direction[1])
        self.end_pos = (self.end_pos[0] + self.speed * self.direction[0], self.end_pos[1] + self.speed * self.direction[1])

        # Check if the line hits the screen edges
        if self.start_pos[0] <= 0 or self.start_pos[0] >= SCREEN_WIDTH:
            self.direction = (-self.direction[0], self.direction[1])
        if self.start_pos[1] <= 0 or self.start_pos[1] >= SCREEN_HEIGHT:
            self.direction = (self.direction[0], -self.direction[1])
        if self.end_pos[0] <= 0 or self.end_pos[0] >= SCREEN_WIDTH:
            self.direction = (-self.direction[0], self.direction[1])
        if self.end_pos[1] <= 0 or self.end_pos[1] >= SCREEN_HEIGHT:
            self.direction = (self.direction[0], -self.direction[1])

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
        pygame.draw.line(screen, line.color, line.start_pos, line.end_pos, 1)

    # Update the display
    pygame.display.flip()

    # Cap the frame rate
    clock.tick(30)  # Limit to 30 frames per second

# Quit Pygame
pygame.quit()

