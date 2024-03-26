import pygame
import math

# Initialize Pygame
pygame.init()

# Set up the display
width, height = 800, 600
screen = pygame.display.set_mode((width, height))
pygame.display.set_caption("Moving Line of Rectangles")

# Colors
BLACK = (0, 0, 0)
WHITE = (255, 255, 255)

# Parameters
num_rectangles = 10
rectangle_width = 40
rectangle_height = 20
amplitude = 100  # Amplitude of the sine wave
frequency = 0.02  # Frequency of the sine wave
speed = 2  # Horizontal movement speed
vertical_speed = 1  # Vertical movement speed

# Main loop
clock = pygame.time.Clock()
running = True
x_offsets = [i * (rectangle_width + 10) for i in range(num_rectangles)]

while running:
    screen.fill(BLACK)

    # Handle events
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    # Update x_offsets for horizontal movement
    for i in range(num_rectangles):
        x_offsets[i] += speed

    # Draw the line of rectangles
    for i in range(num_rectangles):
        x = x_offsets[i]
        y = height // 2 + amplitude * math.sin(frequency * x)

        # Draw rectangle
        pygame.draw.rect(screen, WHITE, (x, y, rectangle_width, rectangle_height))

    # Update display
    pygame.display.flip()
    clock.tick(60)

pygame.quit()

