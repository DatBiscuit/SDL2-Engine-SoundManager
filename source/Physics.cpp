#include "Physics.h"

bool AABB(SDL_Rect *a, SDL_Rect *b)
{
	return a->x < b->x + b->w && a->x + a->w > b->x && a->y < b->y + b->h && a->y + a->h > b->y;
}

int AABBSide(SDL_Rect *a, SDL_Rect *b)
{
	if (a->x < b->x + b->w && a->x + a->w > b->x) { return 1; }
	else if (a->y < b->y + b->h && a->y + a->h > b->y) { return 2; }
	else { return 0; }
}