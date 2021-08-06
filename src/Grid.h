#pragma once
#include "Vector2.h"

template <typename T>
class Grid
{
public:
	Grid();
	void Init(Vector2i aSize, int aGridCellSize, Vector2f aPosition);
	~Grid();
	void Clear(const T& aValueToClearTo);
	T* GetCellAtPosition(float aX, float aY) const;
	T* GetCellAtPosition(const Vector2f& aPosition) const;
	T* GetCellAtIndex(int aIndex) const;
	T* GetCellAtGridPos(int aX, int aY) const;
	T* GetCellAtGridPos(const Vector2i& aPosition) const;
	inline int GetCellSize() const {return myCellSize;};
	inline Vector2f GetPosition() const {return myPosition;};
	inline void SetPosition(const Vector2f aPosition){myPosition = aPosition;};
	inline Vector2i GetSize() const {return mySize;};
	inline Vector2i IndexToGridPos(int aIndex)
	{
		int x = aIndex % mySize.x;
		int y = aIndex / mySize.x;
		return {x, y};
	};
	inline Vector2f GetCellPosition(int aCellIndex)
	{
		Vector2i gridPos = IndexToGridPos(aCellIndex);
		Vector2f result = {(float)(gridPos.x * myCellSize), (float)(gridPos.y * myCellSize)};
		result += myPosition;
		return result;
	}
private:
	T* myData = nullptr;
	Vector2i mySize;
	int myCellSize = 0;
	Vector2f myPosition;
};

template <typename T>
Grid<T>::Grid()
{
}

template <typename T>
void Grid<T>::Init(Vector2i aSize, int aGridCellSize, Vector2f aPosition)
{
	myData = new T[aSize.x * aSize.y];
	mySize = aSize;
	myCellSize = aGridCellSize;
	myPosition = aPosition;
}


template <typename T>
Grid<T>::~Grid()
{
	delete[] myData;
	myData = nullptr;
}
template <typename T>
void Grid<T>::Clear(const T& aValueToClearTo)
{
	for (size_t i = 0; i < mySize.x * mySize.y; i++)
	{
		myData[i] = aValueToClearTo;
	}
	
}

template <typename T>
T* Grid<T>::GetCellAtPosition(float aX, float aY) const
{
	int x = (aX - myPosition.x) / myCellSize;
	int y = (aY - myPosition.y) / myCellSize;
	if(x > mySize.x - 1 || y > mySize.y - 1 || aX < myPosition.x || aY < myPosition.y)
	{
		return nullptr;
	}
	int index = y * mySize.x + x;
	return &myData[index];
}
template <typename T>
T* Grid<T>::GetCellAtPosition(const Vector2f& aPosition) const
{
	return GetCellAtPosition(aPosition.x, aPosition.y);
}
template <typename T>
T* Grid<T>::GetCellAtIndex(int aIndex) const
{
	if(aIndex < 0 || aIndex > (mySize.x * mySize.y) - 1)
	{
		return nullptr;
	}
	return &myData[aIndex];
}
template <typename T>
T* Grid<T>::GetCellAtGridPos(int aX, int aY) const
{
	if(aX > mySize.x - 1 || aY > mySize.y - 1 || aX < 0 || aY < 0)
	{
		return nullptr;
	}
	int index = aY * mySize.x + aX;
	return &myData[index];
}
template <typename T>
T* Grid<T>::GetCellAtGridPos(const Vector2i& aPosition) const
{
	return GetCellAtGridPos(aPosition.x, aPosition.y);
}