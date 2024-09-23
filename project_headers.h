#ifndef PROJECT_HEADERS_H
#define PROJECT_HEADERS_H

#include <SDL2/SDL.h>
#include <stdio.h>
#include <math.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

/**
 * struct GameState - Stores the player's state and the game world map.
 *
 * @posX: double representing the player's X position in the game world.
 * @posY: double representing the player's Y position in the game world.
 * @dirX: double representing the X direction of the player's view.
 * @dirY: double representing the Y direction of the player's view.
 * @planeX: double representing the X component of the camera plane
 *          (used for field of view).
 * @planeY: double representing the Y component of the camera plane
 *          (used for field of view).
 * @worldMap: 2D array of integers representing the game world map where
 *            1 indicates a wall and 0 indicates empty space.
 */
typedef struct GameState
{
	double posX;
	double posY;
	double dirX;
	double dirY;
	double planeX;
	double planeY;
	int worldMap[8][8];
} GameState;
/* Function prototypes  */

void init_game_state(GameState *state);
int init_SDL(SDL_Window **window, SDL_Renderer **renderer);
void handle_events(int *running);
void clean_up(SDL_Window *window, SDL_Renderer *renderer);
void set_camera_angle(GameState *state, double angle);
void draw_sky(SDL_Renderer *renderer, int x, int drawStart);
void draw_ground(SDL_Renderer *renderer, int x, int drawEnd, int h);
void draw_wall(SDL_Renderer *renderer, int x, int drawStart, int drawEnd,
	int side);
void calculate_step_sideDist(GameState *state, double rayDirX, double rayDirY,
	int mapX, int mapY, int *stepX, int *stepY, double *sideDistX,
	double *sideDistY, double deltaDistX, double deltaDistY);
void perform_DDA(GameState *state, int *mapX, int *mapY, double *sideDistX,
	double *sideDistY, double deltaDistX, double deltaDistY,
	int stepX, int stepY, int *hit, int *side);
double calculate_wall_distance(int side, int mapX, int mapY, GameState *state,
	int stepX, int stepY, double rayDirX, double rayDirY);
void cast_rays(SDL_Renderer *renderer, GameState *state);

#endif /* SDL_UTILS_H */
