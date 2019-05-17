#pragma once
#include "Vectors.h"

float Lerp(float a, float b, float f);
Vector2<float> VectorLerp(Vector2<float> start, Vector2<float> end, float percent);
float GetAngleFromVector(Vector2<float> dir);
Vector2<float> GetVectorFromAngle(float angle);
float RoundFloatToPlace(float fl, int place);
float RandomFloat(int num);
Vector2<int> GetTilePosition(Vector2<int> pos, int tileSize);

template <typename N>
int Sign(N num)
{
    if (num > 0) { return 1; }
    if (num < 0) { return -1; }
    return 0;
}

template <typename V>
float DotProduct(Vector2<V> a, Vector2<V> b) { return (a.x * b.x) + (a.y * b.y); }