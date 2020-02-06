#ifndef Vector4f_H
#define Vector4f_H

#include <cmath>

// Vector4f performs vector operations with 4-dimensions
// The purpose of this class is primarily for 3D graphics
// applications.
struct Vector4f{
    // Note: x,y,z,w are a convention
    // x,y,z,w could be position, but also any 4-component value.
    float x,y,z,w;

    // Default conostrutcor
    // 'why default?' https://stackoverflow.com/questions/20828907/the-new-keyword-default-in-c11
    Vector4f() = default;

    // The "Real" constructor we want to use.
    // This initializes the values x,y,z
    Vector4f(float a, float b, float c, float d){
      this->x = a;
      this->y = b;
      this->z = c;
      this->w = d;
    }

    // Index operator, allowing us to access the individual
    // x,y,z,w components of our vector.
    float& operator[](int i){
        // TODO: Discuss with your partner why this works.
        //       There is no code to change here.
      return ((&x)[i]);
    }

    // Index operator, allowing us to access the individual
    // x,y,z,w components of our vector.
    const float& operator[](int i) const{
        // TODO: Discuss with your partner why this works.
        //       There is no code to change here.
        return ((&x)[i]);
    }

    // Multiplication Operator
    // Multiply vector by a uniform-scalar.
    Vector4f& operator *=(float s){
        this->x *= s;
        this->y *= s;
        this->z *= s;
        this->w *= s;
        return (*this);
    }

    // Division Operator
    Vector4f& operator /=(float s){
        this->x /= s;
        this->y /= s;
        this->z /= s;
        this->w /= s;
        return (*this);
    }

    // Addition operator
    Vector4f& operator +=(const Vector4f& v){
        this->x += v[0];
        this->y += v[1];
        this->z += v[2];
        this->w += v[3];
        return (*this);
    }

    // Subtraction operator
    Vector4f& operator -=(const Vector4f& v){
        this->x -= v[0];
        this->y -= v[1];
        this->z -= v[2];
        this->w -= v[3];
        return (*this);
    }

};

// Compute the dot product of a Vector4f
inline float Dot(const Vector4f& a, const Vector4f& b){
    return a[0] * b[0] + a[1] * b[1] + a[2] * b[2] + a[3] * b[3];
  }

// Multiplication of a vector by a scalar values
inline Vector4f operator *(const Vector4f& v, float s){
  Vector4f vec = Vector4f(v[0] * s, v[1] * s, v[2] * s, v[3] * s);
  return vec;
}

// Division of a vector by a scalar value.
inline Vector4f operator /(const Vector4f& v, float s){
  Vector4f vec = Vector4f(v[0] / s, v[1] / s, v[2] / s, v[3] / s);
  return vec;
}

// Negation of a vector
// Use Case: Sometimes it is handy to apply a force in an opposite direction
inline Vector4f operator -(const Vector4f& v){
  Vector4f vec = Vector4f(-v[0], -v[1], -v[2], -v[3]);
  return vec;
}

// Return the magnitude of a vector
inline float Magnitude(const Vector4f& v){
  return sqrt(pow(v[0], 2) + pow(v[1], 2) + pow(v[2], 2) + pow(v[3], 2));
}

// Add two vectors together
inline Vector4f operator +(const Vector4f& a, const Vector4f& b){
  Vector4f vec = Vector4f(a[0] + b[0], a[1] + b[1], a[2] + b[2], a[3] + b[3]);
  return vec;
}

// Subtract two vectors
inline Vector4f operator -(const Vector4f& a, const Vector4f& b){
  Vector4f vec = Vector4f(a[0] - b[0], a[1] - b[1], a[2] - b[2], a[3] - b[3]);
  return vec;
}

// Set a vectors magnitude to 1
// Note: This is NOT generating a normal vector
inline Vector4f Normalize(const Vector4f& v){
  // TODO:
  Vector4f vec;
  vec = v / Magnitude(v);
  return vec;
}

// Vector Projection
// Note: This is the vector projection of 'a' onto 'b'
inline Vector4f Project(const Vector4f& a, const Vector4f& b){
  // TODO:
  Vector4f vec = Normalize(b) * (Dot(a, b) / Magnitude(a)) ;
  return vec;
}


// a x b (read: 'a crossed b')
// Produces a new vector perpendicular to a and b.
// (So long as a and b are not parallel which returns zero vector)
// Note: For a Vector4f, we can only compute a cross porduct to 
//       to vectors in 3-dimensions. Simply ignore w, and set to (0,0,0,1)
//       for this vector.
inline Vector4f CrossProduct(const Vector4f& a, const Vector4f& b){
  // TODO:
  Vector4f vec;
  vec[0] = a[1]*b[2] - a[2]*b[1];
  vec[1] = a[2]*b[0] - a[0]*b[2];
  vec[2] = a[0]*b[1] - a[1]*b[0];
  vec[3] = 1;
  return vec;
}


#endif
