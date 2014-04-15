#ifndef VECTOR2D_H_
#define VECTOR2D_H_

#include <sstream>
#include <string>
#include <cmath>

/*
 * A simple Vector in 2 dimensional euclidean space
 */
template<typename T>
class Vector2D
{
public:
	Vector2D(T x = 0, T Y = 0);
	template<typename U>
	Vector2D(const Vector2D<U>& other);

	// Returns comma separated representation ("x, y").
	std::string ToString() const;

	// Euclidean distance to origin
	T Length() const;
	T x_, y_;
};

template<typename T>
Vector2D<T>::Vector2D(T x, T y) :
		x_(x), y_(y)
{
}

template<typename T>
template<typename U>
Vector2D<T>::Vector2D(const Vector2D<U>& other) :
		x_(static_cast<T>(other.x_)), y_(static_cast<T>(other.y_))
{
}

template<typename T>
std::string Vector2D<T>::ToString() const
{
	std::ostringstream str;
	str << x_ << ", " << y_;
	return str.str();
}

template<typename T>
T Vector2D<T>::Length() const
{
	return std::sqrt(x_ * x_ + y_ * y_);
}

template<typename charT, typename traitT, typename T>
std::basic_ostream<charT, traitT>& operator<<(std::basic_ostream<charT, traitT>& strm, const Vector2D<T>& vector)
{
	strm << vector.ToString();
	return strm;
}

template<typename T>
Vector2D<T> operator+(const Vector2D<T>& lhs, const Vector2D<T>& rhs)
{
	return Vector2D<T>(lhs.x_ + rhs.x_, lhs.y_ + rhs.y_);
}

template<typename T>
Vector2D<T> operator-(const Vector2D<T>& lhs, const Vector2D<T>& rhs)
{
	return Vector2D<T>(lhs.x_ - rhs.x_, lhs.y_ - rhs.y_);
}

template<typename T>
Vector2D<T>& operator+=(Vector2D<T>& lhs, const Vector2D<T>& rhs)
{
	lhs.x_ += rhs.x_;
	lhs.y_ += rhs.y_;
	return lhs;
}

template<typename T>
bool operator==(const Vector2D<T>& lhs, const Vector2D<T>& rhs)
{
	return lhs.x_ == rhs.x_ && lhs.y_ == rhs.y_;
}

template<typename T>
bool operator!=(const Vector2D<T>& lhs, const Vector2D<T>& rhs)
{
	return lhs.x_ != rhs.x_ || lhs.y_ != rhs.y_;
}

template<typename T>
Vector2D<T>& operator-=(Vector2D<T>& lhs, const Vector2D<T>& rhs)
{
	lhs.x_ -= rhs.x_;
	lhs.y_ -= rhs.y_;
	return lhs;
}

template<typename T, typename U>
Vector2D<T>& operator*=(Vector2D<T>& lhs, const U& rhs)
{
	lhs.x_ *= rhs;
	lhs.y_ *= rhs;
	return lhs;
}

template<typename T>
Vector2D<T> operator*(const Vector2D<T>& lhs, const Vector2D<T>& rhs)
{
	return Vector2D<T>(lhs.x_ * rhs.x_, lhs.y_ * rhs.y_);
}

template<typename T, typename U>
Vector2D<T> operator*(const Vector2D<T>& lhs, const U& rhs)
{
	return Vector2D<T>(lhs.x_ * rhs, lhs.y_ * rhs);
}

template<typename T>
Vector2D<T> operator*(const Vector2D<T>& lhs, const double& rhs)
{
	return Vector2D<T>(static_cast<T>(static_cast<double>(lhs.x_) * rhs),
			static_cast<T>(static_cast<double>(lhs.y_) * rhs));
}

template<typename T>
Vector2D<T> operator/(const Vector2D<T>& lhs, const Vector2D<T>& rhs)
{
	return Vector2D<T>(lhs.x_ / rhs.x_, lhs.y_ / rhs.y_);
}

template<typename T>
Vector2D<T> operator/(const Vector2D<T>& lhs, T divisor)
{
	return Vector2D<T>(lhs.x_ / divisor, lhs.y_ / divisor);
}

template<typename T>
T ManhattanDistance(const Vector2D<T>& lhs, const Vector2D<T>& rhs)
{
	return std::abs(rhs.x_ - lhs.x_) + std::abs(rhs.y_ - lhs.y_);
}

#endif /* VECTOR2D_H_ */
