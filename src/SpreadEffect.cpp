#include "SpreadEffect.h"
#include "StreamQuad.h"
#include <functional>
#include "WindowHandler.h"
#include "Random.h"

void SpreadEffect::Init(Vector2i aSize, int aPixelSize, float aSpreadTime)
{
    myScaledSize = aSize / aPixelSize;
    myImagePixelSize = aSize;
    myPixelSize = aPixelSize;
    myPixelCount = myScaledSize.x * myScaledSize.y;
    myColored = new bool[myPixelCount];
    memset(myColored, 0, myPixelCount);
    myDrawIndex = 0;

    mySpreadTimer = aSpreadTime;
	mySpreadDelay = mySpreadTimer / GetTotalPixelsToDraw();
    myCurrentSpreadTime = mySpreadDelay;
}
bool SpreadEffect::FinishedDrawing() 
{
    return myDrawnPixels >= myPixelCount;
};
void SpreadEffect::Update(float aDeltaTime, StreamQuad& aQuad)
{
    if(FinishedDrawing())
    {
        return;
    }
	myCurrentSpreadTime -= aDeltaTime;
	if(myCurrentSpreadTime <= 0.f)
	{
		float diff = aDeltaTime;
		while(diff > 0.f)
		{
			ColorNextPixel(aQuad);
			diff -= mySpreadDelay;
		}
		myCurrentSpreadTime = mySpreadDelay;
	}
}
void SpreadEffect::SetFillPercentage(float aPercentage)
{
    myDrawIndex = myFillIndex;
    myFillPercentage = aPercentage;
    myFillIndex = myPixelCount * aPercentage;
}
void SpreadEffect::StartFloodFill(Vector2i aPosition)
{
    int startPixel = ((aPosition.y / myPixelSize) * myScaledSize.x) + aPosition.x / myPixelSize;


    std::stack<int> myPixelStack;
    myPixelStack.push(startPixel);
    while (myPixelStack.size() > 0)
    {
        int pixel = myPixelStack.top();
        myPixelStack.pop();
        Vector2i position = {pixel % myScaledSize.x, pixel / myScaledSize.x};
        if (position.x < myScaledSize.x && position.x >= 0 &&
            position.y < myScaledSize.y && position.y >= 0) //make sure we stay within bounds
        {
            if (!myColored[pixel])
            {
                myColored[pixel] = true;
                myPixelsToDraw.push_back(pixel);
                std::vector<std::function<void()>> functionsToRun;
                functionsToRun.push_back(
                    [&]()
                    {
                        myPixelStack.push(VecToIndex({position.x - 1, position.y}));
                    });
                functionsToRun.push_back(
                    [&]()
                    {
                        myPixelStack.push(VecToIndex({position.x + 1, position.y}));
                    });
                functionsToRun.push_back(
                    [&]()
                    {
                        myPixelStack.push(VecToIndex({position.x, position.y - 1}));
                    });
                functionsToRun.push_back(
                    [&]()
                    {
                        myPixelStack.push(VecToIndex({position.x, position.y + 1}));
                    });
                    std::shuffle(functionsToRun.begin(), functionsToRun.end(), Random::GetInstance().GetEngine());
                    functionsToRun[0]();
                    functionsToRun[1]();
                    functionsToRun[2]();
                    functionsToRun[3]();
            }
        }
    }
}

void SpreadEffect::StartCircle(Vector2i aPosition)
{
    int startPixel = ((aPosition.y / myPixelSize) * myScaledSize.x) + aPosition.x / myPixelSize;

    for (size_t i = 2; i < myScaledSize.x / 2; i++)
    {
        int radius = i;
        //DrawCircle(aPosition.x, aPosition.y, i);
        for (int y = -radius; y <= radius; y++)
            for (int x = -radius; x <= radius; x++)
            {
                if (x * x + y * y <= radius * radius)
                {
                    auto element = VecToIndex({aPosition.x + x, aPosition.y + y});
                    //if (std::find(myPixelsToDraw.begin(), myPixelsToDraw.end(), element) == myPixelsToDraw.end())
                    {
                        myPixelsToDraw.push_back(element);
                    }
                }
            }
    }
}

void SpreadEffect::StartRandom()
{
    myPixelsToDraw.clear();
    myReversePixelsToDraw.clear();
    myPixelsToDraw.reserve(myPixelCount);
    for (size_t i = 0; i < myPixelCount; i++)
    {
        myPixelsToDraw.push_back(i);
    }
    std::shuffle(myPixelsToDraw.begin(), myPixelsToDraw.end(), Random::GetInstance().GetEngine());
}

void SpreadEffect::ColorNextPixel(StreamQuad &aQuad)
{
    aQuad.LockTexture();
    Uint32 *pixels = (Uint32 *)aQuad.GetPixels();
    auto format = WindowHandler::GetInstance()->GetPixelFormat();
    Uint32 color = SDL_MapRGB(format, myColor.r * 255, myColor.g * 255, myColor.b * 255);
    Uint32 coverColor = SDL_MapRGB(format, 255, 0, 0);
    int effectPixel = GetNextPixelToColor();
    //effectPixel *= myPixelSize;
    if (effectPixel >= 0)
    {
        for (size_t y = 0; y < myPixelSize; y++)
        {
            for (size_t x = 0; x < myPixelSize; x++)
            {
                if((float)myDrawIndex / myPixelCount > myFillPercentage)
                {
                    pixels[effectPixel + VecToPixelIndex({x, y})] = coverColor; 
                    continue;
                }
                pixels[effectPixel + VecToPixelIndex({x, y})] = color; 
            }
        }
    }
    myDrawnPixels++;
    aQuad.UnlockTexture();
}
int SpreadEffect::GetNextPixelToColor()
{
    if(myDrawnPixels >= myPixelCount)
    {
        return -1;
    }
    int id = myPixelsToDraw[myDrawIndex];
    int x = id % myScaledSize.x;
    int y = id / myScaledSize.y;
    x *= myPixelSize;
    y *= myPixelSize;
    id = VecToPixelIndex({x, y});
    if(myDrawReverse)
    {
        myDrawIndex--;
        return id;
    }
    myDrawIndex++;
    return id;
}
int SpreadEffect::VecToIndex(Vector2i aPosition)
{
    return (aPosition.y * myScaledSize.x) + aPosition.x;
}
int SpreadEffect::VecToPixelIndex(Vector2i aPosition)
{
    return (aPosition.y * myImagePixelSize.x) + aPosition.x;
}
void SpreadEffect::Reset(bool aReverse)
{
    if(aReverse)
    {
        myDrawReverse = true;
        myDrawnPixels = 0;
        myDrawIndex = myPixelCount - 1;
        return;
    }
    myDrawReverse = false;
    myDrawnPixels = 0;
    myDrawIndex = 0;

}
void SpreadEffect::DrawCircle(int32_t centreX, int32_t centreY, int32_t radius)
{
    const int32_t diameter = (radius * 2);

    int32_t x = (radius - 1);
    int32_t y = 0;
    int32_t tx = 1;
    int32_t ty = 1;
    int32_t error = (tx - diameter);

    while (x >= y)
    {
        //  Each of the following renders an octant of the circle
        myPixelsToDraw.push_back(VecToIndex({centreX + x, centreY - y}));
        myPixelsToDraw.push_back(VecToIndex({centreX + x, centreY + y}));
        myPixelsToDraw.push_back(VecToIndex({centreX - x, centreY - y}));
        myPixelsToDraw.push_back(VecToIndex({centreX - x, centreY + y}));
        myPixelsToDraw.push_back(VecToIndex({centreX + y, centreY - x}));
        myPixelsToDraw.push_back(VecToIndex({centreX + y, centreY + x}));
        myPixelsToDraw.push_back(VecToIndex({centreX - y, centreY - x}));
        myPixelsToDraw.push_back(VecToIndex({centreX - y, centreY + x}));

        if (error <= 0)
        {
            ++y;
            error += ty;
            ty += 2;
        }

        if (error > 0)
        {
            --x;
            tx += 2;
            error += (tx - diameter);
        }
    }
}
void SpreadEffect::SetColor(Color aColor)
{
    myColor = aColor;
}
bool SpreadEffect::ShouldFillReverse()
{
    return myDrawIndex / myPixelCount > myFillPercentage;
}