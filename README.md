# SDL Raycasting Game Engine

This project is a simple 2D raycasting-based game engine implemented using SDL2 in C. It simulates a 3D environment from a 2D map, similar to early first-person shooter games like *Wolfenstein 3D*. The player can move around a grid-based world and view the surroundings in a pseudo-3D perspective by casting rays from the player's point of view.

## Features

- **2D grid world with walls**: The world is represented as an 8x8 grid, where `1` indicates a wall and `0` indicates empty space.
- **Raycasting-based 3D rendering**: The game uses raycasting to calculate the distance between the player and walls, rendering the scene from a first-person perspective.
- **Movement and rotation**: The player can move forward, backward, and rotate left or right using keyboard inputs.
- **Adjustable camera angle**: The initial camera angle can be set in the code, allowing for a customizable starting direction.
- **Sky, wall, and ground rendering**: The engine renders the sky, walls, and ground in different colors for a realistic environment.

## Setup

### Prerequisites

To build and run this project, you'll need:
- **SDL2**: Simple DirectMedia Layer (SDL2) installed on your machine. You can install it with your system's package manager or from [here](https://www.libsdl.org/download-2.0.php).

### Installation

1. **Clone the repository**:
   ```bash
   git clone https://github.com/shiftyshadows/SDL_Project.git
   cd sdl-raycasting-engine

2. **Compile the project:**:
   gcc -Wall -Werror -Wextra -pedantic -std=gnu89  *.c -o raycasting_game -l SDL2 -l m

3. **Run the game:**:
   ./raycasting_game

