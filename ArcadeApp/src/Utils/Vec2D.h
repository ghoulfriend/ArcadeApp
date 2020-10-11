/**
 * Vec2D.h
 * 
 * Created on 08/22/20
 * Author: Mouse
*/
#include <iostream>

#ifndef UTILS_VEC2D_H_
#define UTILS_VEC2D_H_

class Vec2D
{
private:
    float mX, mY;

public:
    static const Vec2D ZERO;

    Vec2D():Vec2D(0,0){};
    Vec2D(float x, float y):mX(x), mY(y){};

    inline void SetX(float x){mX = x;};
    inline void SetY(float y){mY = y;};
    inline float GetX() const {return mX;};
    inline float GetY() const {return mY;};

    float Mag2() const;
    float Mag() const;

    Vec2D GetUnitVec() const;
    Vec2D& Normalize();

    float Distance(const Vec2D & vec) const;

    float Dot(const Vec2D & vec) const;

    Vec2D ProjectOnto(const Vec2D & vec) const;

    float AngleBetween(const Vec2D & vec) const;

    Vec2D Reflect(const Vec2D & normal) const;
    //Vec2D Reflect2(const Vec2D & normal) const;

    void Rotate(float angle, const Vec2D & aroundPoint);
    Vec2D RotationResult(float angle, const Vec2D & aroundPoint) const;

    Vec2D operator*(const float scalar) const;
    Vec2D operator/(const float scalar) const;
    Vec2D & operator*=(const float scalar);
    Vec2D& operator/=(const float scalar);

    bool operator==(const Vec2D & vec) const;
    bool operator!=(const Vec2D & vec) const;
    Vec2D operator+(const Vec2D & vec) const;
    Vec2D operator-(const Vec2D & vec) const;
    Vec2D& operator+=(const Vec2D & vec);
    Vec2D& operator-=(const Vec2D & vec);
    Vec2D operator-() const;

    //We wont define the friend function inside the Object, bc it is technically separate from the Object
    friend std::ostream& operator<<(std::ostream & consoleOut, const Vec2D & vec);
    friend Vec2D operator*(float scalar, const Vec2D& vec);
    friend Vec2D operator/(float scalar, const Vec2D& vec);

};

#endif /* UTILS_VEC2D_H_ */