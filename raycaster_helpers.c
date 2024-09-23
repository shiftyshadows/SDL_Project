#include "project_headers.h"

/**
 * set_camera_angle - Sets the camera direction based on a given angle.
 *
 * @angle: The angle (in degrees) to set the camera direction.
 * @state: Pointer to the GameState struct containing player and world data.
 *
 * Return: void.
 */
void set_camera_angle(GameState *state, double angle)
{/* Convert degrees to radians */
	double radians = angle * (M_PI / 180.0);

	/* Update the player's direction vector based on the angle */
	state->dirX = cos(radians);
	state->dirY = sin(radians);
	/* Update the camera plane to maintain a ~66 degree field of view */
	state->planeX = -0.66 * state->dirY;
	state->planeY = 0.66 * state->dirX;
}

/**
 * draw_sky - Draws the sky (top half of the screen) for a column.
 *
 * @renderer: SDL_Renderer pointer for drawing.
 * @x: Column index to draw.
 * @drawStart: The starting Y position of the wall.
 *
 * Return: void.
 */
void draw_sky(SDL_Renderer *renderer, int x, int drawStart)
{
	SDL_SetRenderDrawColor(renderer, 135, 206, 235, 255);  /* Sky blue */
	SDL_RenderDrawLine(renderer, x, 0, x, drawStart);
}

/**
 * draw_ground - Draws the ground (bottom half of the screen) for a column.
 *
 * @renderer: SDL_Renderer pointer for drawing.
 * @x: Column index to draw.
 * @drawEnd: The ending Y position of the wall.
 * @h: Screen height.
 *
 * Return: void.
 */
void draw_ground(SDL_Renderer *renderer, int x, int drawEnd, int h)
{
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);  /* Green for ground */
	SDL_RenderDrawLine(renderer, x, drawEnd, x, h);
}

/**
 * draw_wall - Draws a wall for a column.
 *
 * @renderer: SDL_Renderer pointer for drawing.
 * @x: Column index to draw.
 * @drawStart: The starting Y position of the wall.
 * @drawEnd: The ending Y position of the wall.
 * @side: Indicates whether the wall hit was on the X or Y axis.
 *
 * Return: void.
 */
void draw_wall(SDL_Renderer *renderer, int x, int drawStart, int drawEnd,
		int side)
{
	if (side == 1)
		SDL_SetRenderDrawColor(renderer, 105, 105, 105, 255);  /* Darker grey */
	else
		SDL_SetRenderDrawColor(renderer, 169, 169, 169, 255);  /* Grey */

	SDL_RenderDrawLine(renderer, x, drawStart, x, drawEnd);
}
