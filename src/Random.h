#pragma once
#include <random>

class Random
{
public:
    inline std::default_random_engine& GetEngine()
    {
        return myRNG;
    }
    void Init();
    static inline Random &GetInstance()
    {
        static Random myInstance;
        return myInstance;
    };
private:
    std::mt19937 myRNG;
};