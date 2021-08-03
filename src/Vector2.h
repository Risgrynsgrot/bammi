#pragma once
#pragma once
#include <cmath>

template <class T>
class Vector2
{
public:
	T x;
	T y;
	//Creates a null-vector
	Vector2<T>();
	//Creates a vector (aX, aY)
	Vector2<T>(const T &aX, const T &aY);
	//Copy constructor (compiler generated)
	Vector2<T>(const Vector2<T> &aVector) = default;
	//Assignment operator (compiler generated)
	Vector2<T> &operator=(const Vector2<T> &aVector) = default;
	//Destructor (compiler generated)
	~Vector2<T>() = default;
	//Returns the squared length of the vector
	T LengthSqr() const;
	//Returns the length of the vector
	T Length() const;
	//Returns a normalized copy of this
	Vector2<T> GetNormalized() const;
	//Normalizes the vector
	void Normalize();
	//Returns the dot product of this and aVector
	T Dot(const Vector2<T> &aVector) const;
};

template <class T>
Vector2<T>::Vector2()
{
	x = 0;
	y = 0;
}

template <class T>
Vector2<T>::Vector2(const T &aX, const T &aY)
{
	x = aX;
	y = aY;
}

template <class T>
T Vector2<T>::LengthSqr() const
{
	return (x * x + y * y);
}

template <class T>
T Vector2<T>::Length() const
{
	return sqrt(LengthSqr());
}

template <class T>
Vector2<T> Vector2<T>::GetNormalized() const
{
	if (LengthSqr() == 0)
	{
		return {0, 0};
	}
	return (*this) / Length();
}

template <class T>
void Vector2<T>::Normalize()
{
	(*this) = GetNormalized();
}

template <class T>
T Vector2<T>::Dot(const Vector2<T> &aVector) const
{
	return (x * aVector.x + y * aVector.y);
}

//Returns the vector sum of aVector0 and aVector1
template <class T>
Vector2<T> operator+(const Vector2<T> &aVector0, const Vector2<T> &aVector1)
{
	return Vector2<T>(aVector0.x + aVector1.x, aVector0.y + aVector1.y);
}

//Returns the vector difference of aVector0 and aVector1
template <class T>
Vector2<T> operator-(const Vector2<T> &aVector0, const Vector2<T> &aVector1)
{
	return Vector2<T>(aVector0.x - aVector1.x, aVector0.y - aVector1.y);
}

//Returns the vector aVector multiplied by the scalar aScalar
template <class T>
Vector2<T> operator*(const Vector2<T> &aVector, const T &aScalar)
{
	return Vector2<T>(aVector.x * aScalar, aVector.y * aScalar);
}

//Returns the vector aVector multiplied by the scalar aScalar
template <class T>
Vector2<T> operator*(const T &aScalar, const Vector2<T> &aVector)
{
	return Vector2<T>(aVector.x * aScalar, aVector.y * aScalar);
}

//Returns the vector aVector divided by the scalar aScalar (equivalent to aVector multiplied by 1 / aScalar)
template <class T>
Vector2<T> operator/(const Vector2<T> &aVector, const T &aScalar)
{
	return Vector2<T>(aVector.x / aScalar, aVector.y / aScalar);
}

//Equivalent to setting aVector0 to (aVector0 + aVector1)
template <class T>
void operator+=(Vector2<T> &aVector0, const Vector2<T> &aVector1)
{
	aVector0.x += aVector1.x;
	aVector0.y += aVector1.y;
}

//Equivalent to setting aVector0 to (aVector0 - aVector1)
template <class T>
void operator-=(Vector2<T> &aVector0, const Vector2<T> &aVector1)
{
	aVector0.x -= aVector1.x;
	aVector0.y -= aVector1.y;
}

//Equivalent to setting aVector to (aVector * aScalar)
template <class T>
void operator*=(Vector2<T> &aVector, const T &aScalar)
{
	aVector.x *= aScalar;
	aVector.y *= aScalar;
}

//Equivalent to setting aVector to (aVector / aScalar)
template <class T>
void operator/=(Vector2<T> &aVector, const T &aScalar)
{
	aVector.x /= aScalar;
	aVector.y /= aScalar;
}

typedef Vector2<float> Vector2f;
typedef Vector2<int> Vector2i;