import pygame
import random
import sys

# Initialize Pygame
pygame.init()

# Set screen dimensions
SCREEN_WIDTH = 800
SCREEN_HEIGHT = 600

# Set colors
BLACK = (0, 0, 0)

# Set number of stars
NUM_STARS = 100

# Define Star class
class Star:
    def __init__(self):
        self.x = random.randint(0, SCREEN_WIDTH)
        self.y = random.randint(0, SCREEN_HEIGHT)
        self.speed = random.randint(1, 3)

    def update(self):
        self.y += self.speed
        if self.y > SCREEN_HEIGHT:
            self.y = 0
            self.x = random.randint(0, SCREEN_WIDTH)

# Create screen
screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
pygame.display.set_caption("Starfield Screensaver")

# Create clock
clock = pygame.time.Clock()

# Create stars
stars = [Star() for _ in range(NUM_STARS)]

# Main loop
while True:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
            sys.exit()

    screen.fill(BLACK)

    # Update and draw stars
    for star in stars:
        star.update()
        pygame.draw.circle(screen, (255, 255, 255), (star.x, star.y), 1)

    pygame.display.flip()
    clock.tick(60)

