#include "project_headers.h"

/**
 * move_forward_backward - Moves the player forward or backward.
 *
 * @state: Pointer to the GameState struct containing player and world data.
 * @direction: Positive for forward movement, negative for backward.
 *
 * Return: void.
 */
void move_forward_backward(GameState *state, double direction)
{
	if (state->worldMap[(int)(state->posX + state->dirX * direction)]
		[(int)state->posY] == 0)
	{
		state->posX += state->dirX * direction; }
	if (state->worldMap[(int)state->posX]
		[(int)(state->posY + state->dirY * direction)] == 0)
	{
		state->posY += state->dirY * direction; }
}

/**
 * strafe_left_right - Strafes the player left or right.
 *
 * @state: Pointer to the GameState struct containing player and world data.
 * @direction: Positive for right strafe, negative for left strafe.
 *
 * Return: void.
 */
void strafe_left_right(GameState *state, double direction)
{
	if (state->worldMap[(int)(state->posX + state->planeX * direction)]
		[(int)state->posY] == 0)
	{
		state->posX += state->planeX * direction; }
	if (state->worldMap[(int)state->posX]
		[(int)(state->posY + state->planeY * direction)] == 0)
	{
		state->posY += state->planeY * direction; }
}

/**
 * rotate_camera - Rotates the camera based on a given speed.
 *
 * @state: Pointer to the GameState struct containing player and world data.
 * @rotationSpeed: The speed of the rotation (double).
 *
 * Return: void.
 */
void rotate_camera(GameState *state, double rotationSpeed)
{
	double oldDirX = state->dirX;
	double oldPlaneX = state->planeX;

	state->dirX = state->dirX * cos(rotationSpeed) -
		state->dirY * sin(rotationSpeed);
	state->dirY = oldDirX * sin(rotationSpeed) +
		state->dirY * cos(rotationSpeed);
	state->planeX = state->planeX * cos(rotationSpeed) -
		state->planeY * sin(rotationSpeed);
	state->planeY = oldPlaneX * sin(rotationSpeed) +
		state->planeY * cos(rotationSpeed);
}

/**
 * handle_mouse_input - Handles mouse movement for camera rotation.
 *
 * @state: Pointer to the GameState struct containing player and world data.
 *
 * Return: void.
 */
void handle_mouse_input(GameState *state)
{
	int mouseX, mouseY;
	double rotationSpeed;

	SDL_GetRelativeMouseState(&mouseX, &mouseY);
	rotationSpeed = -mouseX * MOUSE_SENSITIVITY;
	rotate_camera(state, rotationSpeed);
}

/**
 * handle_keyboard_input - Handles keyboard input for movement and rotation.
 *
 * @event: The SDL_Event containing the keypress event.
 * @running: Pointer to the running status to indicate when to exit (int*).
 * @state: Pointer to the GameState struct containing player and world data.
 *
 * Return: void.
 */
void handle_keyboard_input(SDL_Event *event, int *running, GameState *state)
{
	switch (event->key.keysym.sym)
	{
		case SDLK_ESCAPE:
			*running = 0;
			break;

		case SDLK_w:  /* Move forward */
			move_forward_backward(state, MOVE_SPEED);
			break;

		case SDLK_s:  /* Move backward */
			move_forward_backward(state, -MOVE_SPEED);
			break;

		case SDLK_a:  /* Strafe left */
			strafe_left_right(state, -MOVE_SPEED);
			break;

		case SDLK_d:  /* Strafe right */
			strafe_left_right(state, MOVE_SPEED);
			break;

		case SDLK_LEFT:  /* Rotate left */
			rotate_camera(state, ROTATE_SPEED);
			break;

		case SDLK_RIGHT:  /* Rotate right */
			rotate_camera(state, -ROTATE_SPEED);
			break;
	}
}
