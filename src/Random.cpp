#include "Random.h"
#include <chrono>

void Random::Init()
{    
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    myRNG = std::mt19937(seed);
}