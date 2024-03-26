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

# Main loop
clock = pygame.time.Clock()
running = True
x_offset = 0

while running:
    screen.fill(BLACK)

    # Handle events
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    # Calculate vertical offset using sine wave
    y_offset = amplitude * math.sin(frequency * x_offset)

    # Draw the line of rectangles
    for i in range(num_rectangles):
        x = i * (rectangle_width + 10) + x_offset
        y = height // 2 + y_offset

        # Draw rectangle
        pygame.draw.rect(screen, WHITE, (x, y, rectangle_width, rectangle_height))

    # Update x_offset for horizontal movement
    x_offset += speed

    # Update display
    pygame.display.flip()
    clock.tick(60)

pygame.quit()

