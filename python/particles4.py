import pygame
import random
import math

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
    def __init__(self, x, y, color, velocity, spawn_probability):
        self.x = x
        self.y = y
        self.color = color
        self.radius = 5
        self.lifetime = random.randint(50, 200)  # Set random initial lifetime
        self.vel_x, self.vel_y = velocity
        self.spawn_probability = spawn_probability

    def update(self):
        self.x += self.vel_x
        self.y += self.vel_y
        self.lifetime -= 1  # Decrease lifetime
        if self.lifetime < 0:
            self.lifetime = 0  # Ensure lifetime doesn't go negative

    def draw(self):
        alpha = int((self.lifetime / 200) * 255)  # Adjust alpha based on remaining lifetime
        pygame.draw.circle(screen, (self.color[0], self.color[1], self.color[2], alpha), (int(self.x), int(self.y)), self.radius)

    def spawn_particles(self):
        if random.random() < self.spawn_probability:
            num_particles = random.randint(2, 5)  # Random number of particles to spawn
            for _ in range(num_particles):
                particle_color = (random.randint(0, 255), random.randint(0, 255), random.randint(0, 255))
                particle_velocity = (random.uniform(-1, 1), random.uniform(-1, 1))
                new_particle = Particle(self.x, self.y, particle_color, particle_velocity, self.spawn_probability)
                particles.append(new_particle)

# Function to calculate velocity components for particles forming a ring around a center point
def calculate_ring_velocities(center_x, center_y, num_particles, radius, speed):
    velocities = []
    angle_increment = (2 * math.pi) / num_particles
    for i in range(num_particles):
        angle = i * angle_increment
        vel_x = speed * math.cos(angle)
        vel_y = speed * math.sin(angle)
        velocities.append((vel_x, vel_y))
    return velocities

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
            # Spawn ring of particles around mouse cursor
            num_particles = 20
            radius = 50
            speed = 1
            ring_velocities = calculate_ring_velocities(event.pos[0], event.pos[1], num_particles, radius, speed)
            for i in range(num_particles):
                particle_color = (random.randint(0, 255), random.randint(0, 255), random.randint(0, 255))
                spawn_probability = 0.2  # Probability of spawning particles when this particle dies
                particle = Particle(event.pos[0], event.pos[1], particle_color, ring_velocities[i], spawn_probability)
                particles.append(particle)

    # Update and draw particles
    for particle in particles:
        particle.update()
        particle.draw()
        if particle.lifetime == 0:
            particle.spawn_particles()

    # Remove particles with zero lifetime
    particles = [particle for particle in particles if particle.lifetime > 0]

    pygame.display.flip()

    # Limit frame rate
    pygame.time.Clock().tick(60)

# Quit Pygame
pygame.quit()

