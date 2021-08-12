#pragma once
#include <stack>
#include <vector>
#include <algorithm>
#include <random>
#include "Vector2.h"
#include "robin_hood.h"
#include "Primitives.h"

class StreamQuad;

class SpreadEffect
{
public:
    void Init(Vector2i aSize, int aPixelSize, float aSpreadTime);
    void Update(float aDeltaTime, StreamQuad& aQuad);
    void SetColor(Color aColor);
    void StartFloodFill(Vector2i aPosition);
    void StartCircle(Vector2i aPosition);
    void StartRandom();
    void SetFillPercentage(float aPercentage);
    void Reset(bool aReverse);
    int GetNextPixelToColor();
    void ColorNextPixel(StreamQuad& aQuad);
    inline int GetTotalPixelsToDraw() {return myPixelCount;};
    bool FinishedDrawing();
    void SetDrawReverse(bool aReverse);
private:
    void DrawCircle(int32_t centreX, int32_t centreY, int32_t radius);
    int VecToIndex(Vector2i aPosition);
    int VecToPixelIndex(Vector2i aPosition);
    bool ShouldFillReverse();
    int myPixelSize;
    int myPixelCount;
    Vector2i myScaledSize;
    Vector2i myImagePixelSize;
    std::vector<int> myPixelsToDraw;
    std::vector<int> myReversePixelsToDraw;
    int myDrawIndex;
    bool* myColored;
	float mySpreadTimer = 1.f;
	float myCurrentSpreadTime;
	float mySpreadDelay;
    Color myColor;
    float myFillPercentage = 0.f;
    int myFillIndex = 0;
    bool myDrawReverse = false;
    //int myDrawnPixels = 0;
};