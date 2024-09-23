#include "project_headers.h"

/**
 * calculate_step_sideDist - Calculates step and initial sideDist.
 * @state: Pointer to the GameState struct containing player and world data.
 * @rayDirX: The X direction of the ray (double).
 * @rayDirY: The Y direction of the ray (double).
 * @mapX: The X coordinate of the current square in the map (int).
 * @mapY: The Y coordinate of the current square in the map (int).
 * @stepX: Pointer to the step direction in the X axis (int*).
 * @stepY: Pointer to the step direction in the Y axis (int*).
 * @sideDistX: Pointer to the distance to the next X side (double*).
 * @sideDistY: Pointer to the distance to the next Y side (double*).
 * @deltaDistX: The distance from one X side to the next (double).
 * @deltaDistY: The distance from one Y side to the next (double).
 *
 * Return: void.
 */
void calculate_step_sideDist(GameState *state, double rayDirX, double rayDirY,
	int mapX, int mapY, int *stepX, int *stepY, double *sideDistX,
	double *sideDistY, double deltaDistX, double deltaDistY)
{
	if (rayDirX < 0)
	{
		*stepX = -1;
		*sideDistX = (state->posX - mapX) * deltaDistX;
	}
	else
	{
		*stepX = 1;
		*sideDistX = (mapX + 1.0 - state->posX) * deltaDistX;
	}
	if (rayDirY < 0)
	{
		*stepY = -1;
		*sideDistY = (state->posY - mapY) * deltaDistY;
	}
	else
	{
		*stepY = 1;
		*sideDistY = (mapY + 1.0 - state->posY) * deltaDistY;
	}
}

/**
 * perform_DDA - Performs Digital Differential Analysis to find the wall.
 * @state: Pointer to the GameState struct containing player and world data.
 * @mapX: Pointer to the map X coordinate (int*).
 * @mapY: Pointer to the map Y coordinate (int*).
 * @sideDistX: Pointer to the distance to the next X side (double*).
 * @sideDistY: Pointer to the distance to the next Y side (double*).
 * @deltaDistX: The distance from one X side to the next (double).
 * @deltaDistY: The distance from one Y side to the next (double).
 * @stepX: The step direction in the X axis (int).
 * @stepY: The step direction in the Y axis (int).
 * @hit: Pointer to the hit status (int*).
 * @side: Pointer to the side where the wall was hit (0 for X, 1 for Y) (int*).
 *
 * Return: void.
 */
void perform_DDA(GameState *state, int *mapX, int *mapY, double *sideDistX,
	double *sideDistY, double deltaDistX, double deltaDistY,
	int stepX, int stepY, int *hit, int *side)
{
	while (*hit == 0)
	{
		if (*sideDistX < *sideDistY)
		{
			*sideDistX += deltaDistX;
			*mapX += stepX;
			*side = 0;
		}
		else
		{
			*sideDistY += deltaDistY;
			*mapY += stepY;
			*side = 1;
		}
		if (state->worldMap[*mapX][*mapY] > 0)
			*hit = 1;
	}
}

/**
 * calculate_wall_distance - Calculates the distance to the wall.
 * @side: The side of the wall hit (0 for X, 1 for Y) (int).
 * @mapX: The X coordinate of the current square in the map (int).
 * @mapY: The Y coordinate of the current square in the map (int).
 * @state: Pointer to the GameState struct containing player and world data.
 * @stepX: The step direction in the X axis (int).
 * @stepY: The step direction in the Y axis (int).
 * @rayDirX: The X direction of the ray (double).
 * @rayDirY: The Y direction of the ray (double).
 *
 * Return: The perpendicular distance from the player to the wall (double).
 */
double calculate_wall_distance(int side, int mapX, int mapY, GameState *state,
	int stepX, int stepY, double rayDirX, double rayDirY)
{
	double perpWallDist;

	if (side == 0)
		perpWallDist = (mapX - state->posX + (1 - stepX) / 2) / rayDirX;
	else
		perpWallDist = (mapY - state->posY + (1 - stepY) / 2) / rayDirY;

	return (perpWallDist);
}

/**
 * cast_rays - Cast rays to simulate a 3D environment and draw walls, sky,
 * and ground.
 * @renderer: SDL_Renderer pointer for drawing (SDL_Renderer*).
 * @state: Pointer to the GameState struct containing player and world data.
 *
 * Return: void.
 */
void cast_rays(SDL_Renderer *renderer, GameState *state)
{
	int w = SCREEN_WIDTH, h = SCREEN_HEIGHT, mapX, mapY, stepX, stepY, side,
		x, lineHeight, drawStart, drawEnd, hit;
	double cameraX, rayDirX, rayDirY, sideDistX, sideDistY, deltaDistX,
		deltaDistY, perpWallDist;

	for (x = 0; x < w; x++)
	{
		cameraX = 2 * x / (double)w - 1;
		rayDirX = state->dirX + state->planeX * cameraX;
		rayDirY = state->dirY + state->planeY * cameraX;
		mapX = (int)state->posX;
		mapY = (int)state->posY;
		deltaDistX = fabs(1 / rayDirX);
		deltaDistY = fabs(1 / rayDirY);
		hit = 0;

		calculate_step_sideDist(state, rayDirX, rayDirY, mapX, mapY,
			&stepX, &stepY, &sideDistX, &sideDistY, deltaDistX,
			deltaDistY);

		perform_DDA(state, &mapX, &mapY, &sideDistX, &sideDistY,
			deltaDistX, deltaDistY, stepX, stepY, &hit, &side);

		perpWallDist = calculate_wall_distance(side, mapX, mapY, state,
			stepX, stepY, rayDirX, rayDirY);

		lineHeight = (int)(h / perpWallDist);
		drawStart = -lineHeight / 2 + h / 2;
		drawEnd = lineHeight / 2 + h / 2;

		if (drawStart < 0)
			drawStart = 0;
		if (drawEnd >= h)
			drawEnd = h - 1;

		draw_sky(renderer, x, drawStart);
		draw_wall(renderer, x, drawStart, drawEnd, side);
		draw_ground(renderer, x, drawEnd, h);
	}
}
