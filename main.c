#include "project_headers.h"

/**
 * init_game_state - Initializes the player's position, direction,
 *                   and world map.
 *
 * @state: Pointer to the GameState struct to initialize.
 *
 * Return: void.
 */
void init_game_state(GameState *state)
{/* Initialize the world map with walls (1) and empty spaces (0) */
	int worldMap[8][8] = {
		{1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 1, 0, 1, 0, 0, 1},
		{1, 0, 1, 0, 1, 0, 0, 1},
		{1, 0, 1, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 1, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1}
	};
	int i, j;

	/* Initialize player's position in the middle of the map */
	state->posX = 3.5;
	state->posY = 3.5;
	/* Set initial direction of the player (facing left) */
	state->dirX = -1.0;
	state->dirY = 0.0;
	/* Set the camera plane (to give a field of view) */
	state->planeX = 0.0;
	state->planeY = 0.66;  /* 66 degrees FOV */
	/* Copy world map into the state struct */
	for (i = 0; i < 8; i++)
		for (j = 0; j < 8; j++)
			state->worldMap[i][j] = worldMap[i][j];
}

/**
 * main - Entry point of the program.
 *
 * Return: 0 on success, 1 on failure.
 */
int main(void)
{/* Declaration of Variables */
	int running = 1;
	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;
	GameState state;  /* Initialize the game state struct */

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("Failed to initialize SDL: %s\n", SDL_GetError());
		return (1);
	}
	window = SDL_CreateWindow("Raycasting",
				SDL_WINDOWPOS_CENTERED,
				SDL_WINDOWPOS_CENTERED,
				SCREEN_WIDTH, SCREEN_HEIGHT,
				SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		printf("Failed to create window: %s\n", SDL_GetError());
		SDL_Quit();
		return (1);
	}
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL)
	{
		printf("Failed to create renderer: %s\n", SDL_GetError());
		SDL_DestroyWindow(window);
		SDL_Quit();
		return (1); }
	init_game_state(&state);
	while (running)
	{/* Handle events like movement and rotation */
		handle_events(&running);
		cast_rays(renderer, &state);
		SDL_RenderPresent(renderer);
		SDL_Delay(16);
	}
	clean_up(window, renderer);
	return (0);
}
