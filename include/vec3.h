#pragma once

#include <iostream>
#include <cmath>

class vec3
{
public:
    float e[3];  // Storage in float for space efficiency
    
    // Constructor
    vec3();
    vec3(float e0, float e1, float e2);

    // Accessors
    float x() const;
    float y() const;
    float z() const;

    // Negation (Returns a new vec3)
    vec3 operator-() const;

    // Index operator (for reading)
    float operator[](int i) const;

    // Index operator (for writing)
    float& operator[](int i);

    // += Operator (Addition)
    vec3& operator+=(const vec3& v);

    // *= Operator (Scalar multiplication)
    vec3& operator*=(float t);

    // /= Operator (Scalar division)
    vec3& operator/=(float t);

    // Length calculations
    float length_squared() const;
    float length() const;
};

// Alias for geometric clarity
using point3 = vec3;

// Vector operations
std::ostream& operator<<(std::ostream& out, const vec3& v);
vec3 operator+(const vec3& u, const vec3& v);
vec3 operator-(const vec3& u, const vec3& v);
vec3 operator*(const vec3& u, const vec3& v);
vec3 operator*(const vec3& v, float t);
vec3 operator*(float t, const vec3& v);
vec3 operator/(const vec3& v, float t);
float dot(const vec3& u, const vec3& v);
vec3 cross(const vec3& u, const vec3& v);
vec3 unit_vector(const vec3& v);

/////////////////////////////////////////////////////////FLOAT///////////////////////////////////////////////////////////////////////

// // float
// class vec3
// {
//     public:
//         float e[3];
//         vec3() : e{0,0,0} {}
//         vec3(float e0, float e1, float e2) : e{e0, e1, e2} {}

//         float x() const { return e[0]; }
//         float y() const { return e[1]; }
//         float z() const { return e[2]; }

//         vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
//         float operator[](int i) const { return e[i]; }
//         float& operator[](int i) { return e[i]; }

//         vec3& operator+=(const vec3& v)
//         {
//             e[0] += v.e[0];
//             e[1] += v.e[1];
//             e[2] += v.e[2];
//             return *this;
//         }

//         vec3& operator*=(float t)
//         {
//             e[0] *= t;
//             e[1] *= t;
//             e[2] *= t;
//             return *this;
//         }

//         vec3& operator/=(float t)
//         {
//             return *this *= 1/t;
//         }

//         float length_squared() const 
//         {
//             return ( e[0]*e[0] + e[1]*e[1] + e[2]*e[2] );
//         }

//         float length() const 
//         {
//             return std::sqrt(length_squared());
//         }
// };

// //Alias useful for geometric clarity
// using point3 = vec3;

// // vec3 utilities

// // Read out vec3 elements
// inline std::ostream& operator<<(std::ostream& out, const vec3& v)
// {
//     return out << v.e[0] << ' ' << v.e[1] <<' ' << v.e[2];
// }

// // Add two vec3
// inline vec3 operator+(const vec3& u, const vec3& v) 
// {
//     return vec3(u.e[0]+v.e[0], u.e[1]+v.e[1], u.e[2]+v.e[2]);
// }
// // Subtract two vec3
// inline vec3 operator-(const vec3& u, const vec3& v)
// {
//     return vec3(u.e[0]-v.e[0], u.e[1]-v.e[1], u.e[2]-v.e[2]);
// }

// // (NOT DOT)Product, Multiply two vec3 u,v
// inline vec3 operator*(const vec3& u, const vec3& v)
// {
//     return vec3(u.e[0]*v.e[0], u.e[1]*v.e[1], u.e[2]*v.e[2]);
// }
// // // (NOT DOT)Product, vec3 v and (float)Scalar t, vec3*t
// inline vec3 operator*(const vec3& v, float t)
// {
//     return vec3(v.e[0]*t, v.e[1]*t, v.e[2]*t);
// }
// // // (NOT DOT)Product, (float)Scalar t and vec3 v, t*v
// inline vec3 operator*(float t, const vec3& v)
// {
//     return t*v;
// }

// // Quotient, (float)Scalar t and vec3 v, (1/t)*v 
// inline vec3 operator/(const vec3& v, float t)
// {
//     return (1/t)*v;
// }

// // //Dot-Product of vec3 u,v
// inline float dot(const vec3& u, const vec3& v)
// {
//     return (
//         (u.e[0] * v.e[0]) + 
//         (u.e[1] * v.e[1]) + 
//         (u.e[2] * v.e[2])
//     );
// }
// //Cross-Product of vec3 u,v
// inline vec3 cross(const vec3& u, const vec3& v)
// {
//     return vec3(
//         u.e[1] * v.e[2] - u.e[2]*v.e[1],
//         u.e[2] * v.e[0] - u.e[0]*v.e[2],
//         u.e[0] * v.e[1] - u.e[1]*v.e[0]
//     );
// }
// // Normalize vec3 v, v/v.length
// inline vec3 unit_vector(const vec3& v) 
// {
//     return v / v.length();
// }
/////////////////////////////////////////////////////////DOUBLE///////////////////////////////////////////////////////////////////////
// DOUBLE
// class vec3
// {
//     public:
//         double e[3];
//         vec3() : e{0,0,0} {}
//         vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}

//         double x() const { return e[0]; }
//         double y() const { return e[1]; }
//         double z() const { return e[2]; }

//         vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
//         double operator[](int i) const { return e[i]; }
//         double& operator[](int i) { return e[i]; }

//         vec3& operator+=(const vec3& v)
//         {
//             e[0] += v.e[0];
//             e[1] += v.e[1];
//             e[2] += v.e[2];
//             return *this;
//         }

//         vec3& operator*=(double t)
//         {
//             e[0] *= t;
//             e[1] *= t;
//             e[2] *= t;
//             return *this;
//         }

//         vec3& operator/=(double t)
//         {
//             return *this *= 1/t;
//         }

//         double length_squared() const 
//         {
//             return ( e[0]*e[0] + e[1]*e[1] + e[2]*e[2] );
//         }

//         double length() const 
//         {
//             return std::sqrt(length_squared());
//         }
// };

// //Alias useful for geometric clarity
// using point3 = vec3;

// // vec3 utilities

// // Read out vec3 elements
// inline std::ostream& operator<<(std::ostream& out, const vec3& v)
// {
//     return out << v.e[0] << ' ' << v.e[1] <<' ' << v.e[2];
// }

// // Add two vec3
// inline vec3 operator+(const vec3& u, const vec3& v) 
// {
//     return vec3(u.e[0]+v.e[0], u.e[1]+v.e[1], u.e[2]+v.e[2]);
// }
// // Subtract two vec3
// inline vec3 operator-(const vec3& u, const vec3& v)
// {
//     return vec3(u.e[0]-v.e[0], u.e[1]-v.e[1], u.e[2]-v.e[2]);
// }

// // (NOT DOT)Product, Multiply two vec3 u,v
// inline vec3 operator*(const vec3& u, const vec3& v)
// {
//     return vec3(u.e[0]*v.e[0], u.e[1]*v.e[1], u.e[2]*v.e[2]);
// }
// // // (NOT DOT)Product, vec3 v and (double)Scalar t, vec3*t
// inline vec3 operator*(const vec3& v, double t)
// {
//     return vec3(v.e[0]*t, v.e[1]*t, v.e[2]*t);
// }
// // // (NOT DOT)Product, (double)Scalar t and vec3 v, t*v
// inline vec3 operator*(double t, const vec3& v)
// {
//     return t*v;
// }

// // Quotient, (double)Scalar t and vec3 v, (1/t)*v 
// inline vec3 operator/(const vec3& v, double t)
// {
//     return (1/t)*v;
// }

// // //Dot-Product of vec3 u,v
// inline double dot(const vec3& u, const vec3& v)
// {
//     return (
//         (u.e[0] * v.e[0]) + 
//         (u.e[1] * v.e[1]) + 
//         (u.e[2] * v.e[2])
//     );
// }
// //Cross-Product of vec3 u,v
// inline vec3 cross(const vec3& u, const vec3& v)
// {
//     return vec3(
//         u.e[1] * v.e[2] - u.e[2]*v.e[1],
//         u.e[2] * v.e[0] - u.e[0]*v.e[2],
//         u.e[0] * v.e[1] - u.e[1]*v.e[0]
//     );
// }
// // Normalize vec3 v, v/v.length
// inline vec3 unit_vector(const vec3& v) 
// {
//     return v / v.length();
// }