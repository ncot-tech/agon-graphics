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
        self.size = self.speed * 2

    def update(self):
        self.y += self.speed
        if self.y > SCREEN_HEIGHT:
            self.y = 0
            self.x = random.randint(0, SCREEN_WIDTH)

    def draw(self, screen):
        brightness = 255 - (self.speed * 50)  # Calculate brightness based on speed
        color = (brightness, brightness, brightness)
        pygame.draw.circle(screen, color, (self.x, self.y), self.size)

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
        star.draw(screen)

    pygame.display.flip()
    clock.tick(60)

