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
WHITE = (255, 255, 255)

# Set number of stars
NUM_STARS = 300

# Define Star class
class Star:
    def __init__(self):
        self.x = random.randint(-SCREEN_WIDTH, SCREEN_WIDTH)
        self.y = random.randint(-SCREEN_HEIGHT, SCREEN_HEIGHT)
        self.z = random.randint(1, SCREEN_WIDTH)  # Distance from the viewer
        self.size = 2  # Base size of the star

    def update(self):
        # Move stars towards the viewer
        self.z -= 1
        if self.z <= 0:
            self.z = SCREEN_WIDTH

    def draw(self, screen):
        # Calculate the size of the star based on its distance from the viewer
        size = self.size * (1 / (self.z / SCREEN_WIDTH))

        # Convert 3D coordinates to 2D (perspective projection)
        x = SCREEN_WIDTH // 2 + (self.x * SCREEN_WIDTH // (2 * self.z))
        y = SCREEN_HEIGHT // 2 + (self.y * SCREEN_HEIGHT // (2 * self.z))

        # Draw the star
        pygame.draw.circle(screen, WHITE, (int(x), int(y)), int(size))

# Create screen
screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
pygame.display.set_caption("Fake 3D Starfield")

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

