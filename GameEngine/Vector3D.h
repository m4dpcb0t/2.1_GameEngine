#ifndef VECTOR3D_H_INCLUDED
#define VECTOR3D_H_INCLUDED

#include "math.h"

class Vector3D
{
    public:
        inline Vector3D() {}
        inline Vector3D(float x, float y, float z) : m_x(x), m_y(y), m_z(z) {}
        //Create overloaded adding operators
        inline Vector3D operator+(const Vector3D& v2) const
        {
            return Vector3D(m_x + v2.m_x, m_y + v2.m_y, m_z + v2.m_z);
        }

        // can access the "private" and "protected" members of the class
        inline friend Vector3D& operator+=(Vector3D& v1, const Vector3D& v2)
        {
            v1.m_x += v2.m_x;
            v1.m_y += v2.m_y;
            v1.m_z += v2.m_z;

            return v1;
        }

        //Create overloaded subtraction operators
        inline Vector3D operator-(const Vector3D& v2) const
        {
            return Vector3D(m_x - v2.m_x, m_y - v2.m_y, m_z - v2.m_z);
        }

        inline friend Vector3D& operator-=(Vector3D& v1, const Vector3D& v2)
        {
            v1.m_x -= v2.m_x;
            v1.m_y -= v2.m_y;
            v1.m_z -= v2.m_z;

            return v1;
        }

        //Scalar multiplication
        inline Vector3D operator*(float scalar)
        {
            return Vector3D(m_x * scalar, m_y * scalar, m_z * scalar);
        }

        inline Vector3D operator*=(float scalar)
        {
            m_x*=scalar;
            m_y*=scalar;
            m_z*=scalar;

            //return the object
            return *this;
        }

        //Scalar Division
        inline Vector3D operator/(float scalar)
        {
            return Vector3D(m_x/scalar, m_y/scalar, m_z/scalar);
        }

        inline Vector3D operator/=(float scalar)
        {
            m_x /= scalar;
            m_y /= scalar;
            m_z /= scalar;

            return *this;
        }

        //Find the lenght of vector
        inline float length() { return sqrt(m_x * m_x + m_y * m_y + m_z * m_z);}

        //Normalizing a vector makes length equal to 1
        inline void normalize()
        {
            float l= length();

            //If length of vector is greater than 0
            //Set this Vector object to normalize
            if(l > 0)
                (*this) *= 1/1;
        }

        //Dot Product
        inline float dotProduct(Vector3D& b)
        {
            return m_x * b.m_x + m_y * b.m_y + m_z * b.m_z;
        }

/*
        //Zero Vector
        inline friend void zeroVector()
        {
            m_x = 0;
            m_y = 0;
            m_z = 0;
        }*/

        inline float getX() { return m_x; }
        inline float getY() { return m_y; }
        inline float getZ() { return m_z; }

        inline void setX(float x) { m_x = x; }
        inline void setY(float y) { m_y = y; }
        inline void setZ(float z) { m_z = z; }



    private:
        float m_x;
        float m_y;
        float m_z;
};

#endif // VECTOR3D_H_INCLUDED
