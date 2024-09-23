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
- **SDL2**: Simple DirectMedia Layer (SDL2) installed on your machine. You can install it with your system's package manager or from [here](https://github.com/libsdl-org/SDL/releases/tag/release-2.30.7).

### Installation

1. **Clone the repository**:

-   bash
-   git clone https://github.com/shiftyshadows/SDL_Project.git
-   cd SDL_Project

2. **Compile the project:**:

-   gcc -Wall -Werror -Wextra -pedantic -std=gnu89  *.c -o raycasting_game -l SDL2 -l m

3. **Run the game:**:

-   ./raycasting_game

## Controls

- **W**: Move forward
- **S**: Move backward
- **A**: Rotate left
- **D**: Rotate right
- **ESC**: Quit the game

## Code Overview
### Main Components

- **GameState struct**: This structure holds all player state and world data. It includes the player's position, direction, and the game world map.

### Key Functions

- **cast_rays**: Casts rays from the player's position to determine the distance to walls and renders the 3D scene.
- **handle_events**: Handles player movement (forward, backward) and rotation (left, right) using keyboard inputs.
- **draw_sky, draw_wall, draw_ground**: Functions that handle the rendering of sky, walls, and ground based on the player's perspective.
- **set_camera_angle**: Sets the player's initial viewing direction based on a given angle in degrees.

### Movement and Rotation Logic

- **Movement**: The player can move forward or backward in the direction they are currently facing. Collisions with walls are prevented using the worldMap data.
- **Rotation**: The player can rotate left or right, which adjusts their direction (dirX and dirY) as well as the camera plane (planeX and planeY) for proper field of view.

### Customizing the Camera Angle

- You can set the player's initial viewing direction by calling set_camera_angle with the desired angle (in degrees). For example, to set the player facing 90 degrees (upward):
  set_camera_angle(&state, 90.0);

### License
- This project is licensed under the MIT [License](https://opensource.org/license/mit) - see the LICENSE file for details.
