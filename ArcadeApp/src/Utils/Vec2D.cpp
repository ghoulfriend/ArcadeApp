#include "Vec2D.h"
#include "Utils.h"
#include <iostream>
#include <cassert>
#include <cmath>

using namespace std;

const Vec2D Vec2D::ZERO;

float Vec2D::Mag2() const
{
    return Dot(*this);
}
float Vec2D::Mag() const
{
    return sqrt(Mag2());
}
Vec2D Vec2D::GetUnitVec() const
{
    float mag = Mag();
    if (mag > EPSILON)
    {
        return *this / mag;
    }
    else
    {
        return Vec2D::ZERO;
    }
}
Vec2D& Vec2D::Normalize()
{
   float mag = Mag();
   if (mag > EPSILON)
   {
       return *this /= mag;
   } 
   else
   {
       return *this;
   }
}
//CAN BE WRITTEN EITHER WAY
//float Vec2D::Distance(const Vec2D & vec) const
//{
//    return sqrt(pow(vec.mX - mX,2) + pow(vec.mY - mY,2));
//}
float Vec2D::Distance(const Vec2D & vec) const
{
    return (vec - *this).Mag();
}
/** Dot Product
 * 
 *  a = [2,4]
 *  b = [3,9]
 * 
 *  a dot b = (2*3) + (4*9) 
*/
float Vec2D::Dot(const Vec2D & vec) const
{
    return mX * vec.mX + mY * vec.mY;
}
Vec2D Vec2D::ProjectOnto(const Vec2D & vec) const
{
    Vec2D unitVec = vec.GetUnitVec();
    float dot = Dot(unitVec);
    return dot * unitVec;
}
float Vec2D::AngleBetween(const Vec2D & vec) const
{
   return acosf(GetUnitVec().Dot(vec.GetUnitVec()));
}
/**
 * EITHER OF THESE WORK
*/
//Vec2D Vec2D::Reflect2(const Vec2D & normal) const
//{
//    return (ProjectOnto(normal) * -2) + *this;
//}
Vec2D Vec2D::Reflect(const Vec2D & normal) const
{
    return *this - 2 * ProjectOnto(normal);
}
void Vec2D::Rotate(float angle, const Vec2D & aroundPoint)
{
    float cosine = cosf(angle);
    float sine = sinf(angle);

    Vec2D thisVec(mX, mY);

    thisVec -= aroundPoint;

    float xRot = thisVec.mX * cosine - thisVec.mY * sine;
    float yRot = thisVec.mX * sine + thisVec.mY * cosine;

    Vec2D rot = Vec2D(xRot, yRot);
    *this = rot + aroundPoint;
}
Vec2D Vec2D::RotationResult(float angle, const Vec2D & aroundPoint) const
{
	//angle = angle * (3.14159 / 180);

	float cosine = cosf(angle);
    float sine = sinf(angle);

    Vec2D thisVec(mX, mY);

    thisVec -= aroundPoint;

    float xRot = thisVec.mX * cosine - thisVec.mY * sine;
    float yRot = thisVec.mX * sine + thisVec.mY * cosine;

    Vec2D rot = Vec2D(xRot, yRot);
    return rot + aroundPoint;
}

Vec2D Vec2D::operator*(const float scalar) const
{
    return Vec2D(mX * scalar, mY * scalar); 
}
Vec2D Vec2D::operator/(const float scalar) const
{
    assert(fabs(scalar) > EPSILON);
    return Vec2D(mX / scalar, mY / scalar);
}
Vec2D Vec2D::operator+(const Vec2D & vec) const
{
    return Vec2D(mX + vec.mX, mY + vec.mY);
};
Vec2D Vec2D::operator-(const Vec2D & vec) const
{
    return Vec2D(mX - vec.mX, mY - vec.mY);
};
Vec2D& Vec2D::operator+=(const Vec2D & vec)
{
    *this = *this + vec;
    return *this;
}
Vec2D& Vec2D::operator-=(const Vec2D & vec)
{
    *this = *this - vec;
    return *this;
}
Vec2D & Vec2D::operator*=(const float scalar)
{
    *this = *this * scalar;
    return *this;
}
Vec2D& Vec2D::operator/=(const float scalar)
{
    assert(fabs(scalar) > EPSILON);
    *this = *this / scalar;
    return *this;
}
bool Vec2D::operator==(const Vec2D & vec) const
{
    return IsEqual(mX,vec.mX) && IsEqual(mY,vec.mY);
}
bool Vec2D::operator!=(const Vec2D & vec) const
{
    return !(*this == vec);
}
Vec2D Vec2D::operator-() const
{
    return Vec2D(-mX,-mY);
}
//notice that we do not have to prefix with Vec2D::
ostream& operator<<(std::ostream & consoleOut, const Vec2D & vec)
{
    consoleOut << "X: " << vec.mX << ", Y: " << vec.mY << endl;        
    return consoleOut;
};
Vec2D operator*(float scalar, const Vec2D& vec)
{
    return vec * scalar;
}
Vec2D operator/(float scalar, const Vec2D& vec)
{
    return vec / scalar;
}
