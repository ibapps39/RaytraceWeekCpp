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

    static vec3 rand_reflect();
    static vec3 rand_reflect(float min, float max);
    
    static vec3 random(float min, float max);
    static vec3 random();

    bool near_zero();
    
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
vec3 rand_unit_vec();
vec3 random_on_hemisphere(const vec3& normal);
vec3 reflect(const vec3& v, const vec3& n);
vec3 refract(const vec3& uv, const vec3& n, float etai_over_etat);
vec3 random_in_unit_disk();

