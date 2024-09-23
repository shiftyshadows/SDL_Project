#include "project_headers.h"

/**
 * init_SDL - Initializes SDL and creates a window.
 *
 * @window: Pointer to a pointer of type SDL_Window.
 * @renderer: Pointer to a pointer of type SDL_Renderer.
 *
 * Return: 0 on success, 1 on failure.
 */
int init_SDL(SDL_Window **window, SDL_Renderer **renderer)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("Failed to initialize SDL: %s\n", SDL_GetError());
		return (1);
	}

	*window = SDL_CreateWindow("SDL2 Window",
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	if (*window == NULL)
	{
		printf("Failed to create window: %s\n", SDL_GetError());
		return (1);
	}

	*renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
	if (*renderer == NULL)
	{
		printf("Failed to create renderer: %s\n", SDL_GetError());
	}

	return (0);
}

/**
 * handle_events - Polls SDL events and delegates input handling to helpers.
 *
 * @running: Pointer to the running status to indicate when to exit (int*).
 * @state: Pointer to the GameState struct containing player and world data.
 *
 * Return: void.
 */
void handle_events(int *running, GameState *state)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			*running = 0; }
		else if (event.type == SDL_KEYDOWN)
		{
			handle_keyboard_input(&event, running, state); }
		else if (event.type == SDL_MOUSEMOTION)
		{
			handle_mouse_input(state); }
	}
}

/**
 * clean_up - Cleans up SDL resources.
 *
 * @window: Pointer tp SDL_Window to be destroyed.
 * @renderer: pointer to SDL_Renderer that will be destroyed.
 *
 * Return: void
 */
void clean_up(SDL_Window *window, SDL_Renderer *renderer)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
