#pragma once
#include "robin_hood.h"

namespace DoubleKey
{
template <typename T>
struct Key
{
	T aFirst;
	T aSecond;
};

template <typename key_t, typename value_t>
class Map
{
public:
	void Insert(Key<key_t> aKey, value_t aValue);
	void Insert(key_t firstKey, key_t aSecondKey, aValue);
private:
	robin_hood::unordered_map<Key<key_t>, value_t> myData;
};
}