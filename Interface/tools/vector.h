#pragma once

class TVector2D
{
public:
    float                                   x, y;
public:

    TVector2D() {
        x = 0.0f;
        y = 0.0f;
    }

    TVector2D(float _x, float _y)
    {
        x = _x;
        y = _y;
    }

    void operator-=(const TVector2D& Other)
    {
        x -= Other.x;
        y -= Other.y;
    }

    TVector2D operator-(const TVector2D& Other)
    {
        TVector2D vecReturn = *this;
        vecReturn.x -= Other.x;
        vecReturn.y -= Other.y;
        return vecReturn;
    }
    TVector2D operator+(const TVector2D& Other)
    {
        TVector2D vecReturn = *this;
        vecReturn.x += Other.x;
        vecReturn.y += Other.y;
        return vecReturn;
    }
    TVector2D operator/(const TVector2D& Other)
    {
        TVector2D vecReturn = *this;
        vecReturn.x /= Other.x;
        vecReturn.y /= Other.y;
        return vecReturn;
    }

    TVector2D operator/(const float& Other)
    {
        TVector2D vecReturn = *this;
        vecReturn.x /= Other;
        vecReturn.y /= Other;
        return vecReturn;
    }


    float  operator[] (size_t idx) const { (idx == 0 || idx == 1); return (&x)[idx]; }
    float& operator[] (size_t idx) { (idx == 0 || idx == 1); return (&x)[idx]; }
};

class TVector3D
{
public:
    float                                   x, y, z;
public:

    TVector3D() {
        x = 0.0f;
        y = 0.0f;
        z = 0.0f;
    }

    TVector3D(float _x, float _y, float _z)
    {
        x = _x;
        y = _y;
        z = _z;
    }

    float  operator[] (size_t idx) const { (idx == 0 || idx == 1); return (&x)[idx]; }
    float& operator[] (size_t idx) { (idx == 0 || idx == 1); return (&x)[idx]; }
};

