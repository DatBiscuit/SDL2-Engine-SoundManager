#include "Rendering.h"

Rendering::Rendering() { }

bool Rendering::Init()
{
    window = SDL_CreateWindow("Exterminaut", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen.x, screen.y, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (window == NULL)
    {
        std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); 
    if (renderer == NULL)
    {
        printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        return false;
    }
    //SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "best");
    SDL_RenderSetLogicalSize(renderer, screen.x, screen.y);

    int count = 1;
    std::string textureNames[] =
        {
            "square_white"
        };

    for(int i = 0; i < count; ++i)
    {
        textures[i] = GenerateTexture(textureNames[i]);
    }

    SDL_RenderSetScale(renderer, cam.currZoom, cam.currZoom);

    return true;
}

SDL_Texture *Rendering::GenerateTexture(std::string path)
{
    SDL_Surface *loadedSurface = IMG_Load(("../images/" + path + ".png").c_str());
    if (loadedSurface == NULL)
    {
        std::cout << "Unable to load image: " << path.c_str() << std::endl;
        std::cout << "SDL_image Error: " << IMG_GetError() << std::endl;
        return NULL;
    }
    SDL_Texture *newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    if (newTexture == NULL)
    {
        std::cout << "Unable to create texture: " << path.c_str() << std::endl;
        std::cout << "SDL Error: " << SDL_GetError() << std::endl;
        return NULL;
    }
    SDL_FreeSurface(loadedSurface);
    loadedSurface = NULL;
    return newTexture;
}

/*bool Rendering::ShouldRender(Renderable * r) 
{ 
    rect = r->rect;
    rect.x -= (int)r->renderOffset.x;
    rect.y -= (int)r->renderOffset.y;
    return AABB(&rect, &cam.rect); 
}*/

/*void Rendering::Render(const Renderable *r)
{
    if(r->spriteRect.w == -1) { rect = r->rect; }
    else 
    { 
        rect = r->spriteRect; 
        rect.x += r->rect.x; 
        rect.y += r->rect.y; 
    }
    rect.x -= (int)r->renderOffset.x;
    rect.y -= (int)r->renderOffset.y;
    rect.x -= cam.position.x;
    rect.y -= cam.position.y;
    SDL_RenderCopyEx(renderer, textures[r->texture], NULL, &rect, r->angle, r->rotationPoint, r->flip);
}*/

void Rendering::Render(SDL_Rect * r, int t)
{
    if(r == NULL) { SDL_RenderCopy(renderer, textures[t], NULL, NULL); }
    else
    {
        rect = *r;
        rect.x -= cam.position.x;
        rect.y -= cam.position.y;
        SDL_RenderCopy(renderer, textures[t], NULL, &rect);
    }
}

Rendering::Camera::Camera() {}
void Rendering::Camera::Update(Vector2<int> a, Vector2<int> b, Vector2<int> s) 
{
    Vector2<float> targetOffset = {(float)a.x, (float)a.y};
    Vector2<float> v = {(float)(b.x - a.x), (float)(b.y - a.y)};
    v /= 3;
    targetOffset = targetOffset + v;
    targetOffset.x -= s.x / (2 * currZoom);
    targetOffset.y -= s.y / (2 * currZoom);
    realPosition = VectorLerp(realPosition, targetOffset, .05f);
    position.x = (int)(realPosition.x + shakeVec.x);
    position.y = (int)(realPosition.y + shakeVec.y);
    if (shakeVec.Magnitude() < .001f) { shakeVec = {0, 0}; }
    else { shakeVec *= -.75f; }

    rect = {position.x, position.y, s.x, s.y};
}