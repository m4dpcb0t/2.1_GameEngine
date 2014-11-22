#ifndef VECTOR2D_H
#define VECTOR2D_H

#include "math.h"
class Vector2D
{
    public:
        inline Vector2D() {}
        inline Vector2D(float x, float y) : m_x(x), m_y(y) {}
        //Create overloaded adding operators
        inline Vector2D operator+(const Vector2D& v2) const
        {
            return Vector2D(m_x + v2.m_x, m_y + v2.m_y);
        }

        // can access the "private" and "protected" members of the class
        inline friend Vector2D& operator+=(Vector2D& v1, const Vector2D& v2)
        {
            v1.m_x += v2.m_x;
            v1.m_y += v2.m_y;

            return v1;
        }

        //Create overloaded subtraction operators
        inline Vector2D operator-(const Vector2D& v2) const
        {
            return Vector2D(m_x - v2.m_x, m_y - v2.m_y);
        }

        inline friend Vector2D& operator-=(Vector2D& v1, const Vector2D& v2)
        {
            v1.m_x -= v2.m_x;
            v1.m_y -= v2.m_y;

            return v1;
        }

        //Scalar multiplication
        inline Vector2D operator*(float scalar)
        {
            return Vector2D(m_x * scalar, m_y * scalar);
        }

        inline Vector2D operator*=(float scalar)
        {
            m_x*=scalar;
            m_y*=scalar;

            //return the object
            return *this;
        }

        //Scalar Division
        inline Vector2D operator/(float scalar)
        {
            return Vector2D(m_x/scalar, m_y/scalar);
        }

        inline Vector2D operator/=(float scalar)
        {
            m_x /= scalar;
            m_y /= scalar;

            return *this;
        }

        //Find the lenght of vector
        inline float length() { return sqrt(m_x * m_x + m_y * m_y);}

        //Normalizing a vector makes length equal to 1
        inline void normalize()
        {
            float l= length();

            //If length of vector is greater than 0
            //
            if(l > 0)
                (*this) *= 1/1;
        }
        //Zero Vector
        inline void zeroVector()
        {
            m_x = 0;
            m_y = 0;
        }

        inline float getX() { return m_x; }
        inline float getY() { return m_y; }

        inline void setX(float x) { m_x = x; }
        inline void setY(float y) { m_y = y; }



    private:
        float m_x;
        float m_y;
};

#endif // VECTOR2D_H
