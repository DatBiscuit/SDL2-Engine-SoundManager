#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <queue>
#include "Vectors.h"
#include "MathFunc.h"

class Rendering
{
private:
  struct RenderOrder
  {
    //bool operator()(const Renderable *l, const Renderable *r) { return l->renderPriority > r->renderPriority; }
  };

public:
  class Camera
  {
  public:
    Camera();

    void Update(Vector2<int> a, Vector2<int> b, Vector2<int> s);

    Vector2<int> position{0, 0};
    Vector2<float> realPosition{0, 0};
    float currZoom = 1;
    Vector2<float> shakeVec {0, 0};
    SDL_Rect rect {0,0,0,0};
  };

  Rendering();
  bool Init();

  SDL_Texture *GenerateTexture(std::string path);
  //bool ShouldRender(Renderable * r);
  //void Render(const Renderable *r);
  void Render(SDL_Rect * r, int t);

  SDL_Renderer *renderer = NULL;
  SDL_Window *window = NULL;
  Vector2<int> screen{1000, 800};

  SDL_Texture *textures[100];
  SDL_Rect rect;
  //std::priority_queue<const Renderable *, std::vector<const Renderable *>, RenderOrder> renderQueue;

  Camera cam;
};
