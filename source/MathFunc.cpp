#include "MathFunc.h"

float Lerp(float a, float b, float f) { return (a * (1.0f - f)) + (b * f); }
Vector2<float> VectorLerp(Vector2<float> start, Vector2<float> end, float percent) { return ((end - start) * percent + start); }
float GetAngleFromVector(Vector2<float> dir) 
{ 
	float a = ((std::atan2(dir.x, dir.y) * 57.2958f) - 90) * -1;
	if(a < 0) { a += 360; }
	return a; 
}
Vector2<float> GetVectorFromAngle(float angle)
{
	angle *= 0.0174533;
	Vector2<float> r {std::cos(angle), std::sin(angle)};
	return r;
}
float RoundFloatToPlace(float fl, int place)
{
	int decimalPlace = (int)pow(10, place);
	return roundf(fl * decimalPlace) / decimalPlace;
}
float RandomFloat(int num)
{
	if (num == 0) { return 0; }
	return (float)(rand() % (num * 2) - num) + ((float)(rand() % 101) / 100);
}
Vector2<int> GetTilePosition(Vector2<int> pos, int tileSize)
{
	Vector2<int> r;
	if (pos.x >= 0) { r.x = pos.x - (pos.x % tileSize); }
	else { 
        int m = pos.x % tileSize;
        if(m != 0){ r.x = pos.x - m - tileSize; }
        else{ r.x = pos.x; }
    }
	if (pos.y >= 0) { r.y = pos.y - (pos.y % tileSize); }
	else { 
        int m = pos.y % tileSize;
        if(m != 0){ r.y = pos.y - m - tileSize; }
        else{ r.y = pos.y; }
    }
	return r;
}