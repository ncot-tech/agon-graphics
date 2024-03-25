import pygame
import random

# Initialize Pygame
pygame.init()

# Set screen dimensions
SCREEN_WIDTH = 800
SCREEN_HEIGHT = 600
screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
pygame.display.set_caption("Particle Simulation")

# Define colors
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)

# Define Particle class
class Particle:
    def __init__(self, x, y, color):
        self.x = x
        self.y = y
        self.color = color
        self.radius = 5
        self.lifetime = random.randint(50, 200)  # Set random initial lifetime

    def update(self):
        self.lifetime -= 1  # Decrease lifetime
        if self.lifetime < 0:
            self.lifetime = 0  # Ensure lifetime doesn't go negative

    def draw(self):
        alpha = int((self.lifetime / 200) * 255)  # Adjust alpha based on remaining lifetime
        pygame.draw.circle(screen, (self.color[0], self.color[1], self.color[2], alpha), (self.x, self.y), self.radius)

# Create list to store particles
particles = []

# Main loop
running = True
while running:
    screen.fill(BLACK)

    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
        elif event.type == pygame.MOUSEBUTTONDOWN:
            # Spawn new particle at mouse position with random color
            particle_color = (random.randint(0, 255), random.randint(0, 255), random.randint(0, 255))
            particle = Particle(event.pos[0], event.pos[1], particle_color)
            particles.append(particle)

    # Update and draw particles
    for particle in particles:
        particle.update()
        particle.draw()

    # Remove particles with zero lifetime
    particles = [particle for particle in particles if particle.lifetime > 0]

    pygame.display.flip()

    # Limit frame rate
    pygame.time.Clock().tick(60)

# Quit Pygame
pygame.quit()

