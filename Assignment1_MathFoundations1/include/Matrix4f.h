// High level design note
// Our matrix should match the behavior of the glm library.
#ifndef MATRIX4F_H
#define MATRIX4F_H

#include <cmath>

// We need to Vector4f header in order to multiply a matrix
// by a vector.
#include "Vector4f.h"

// Matrix 4f represents 4x4 matrices in Math
struct Matrix4f{
private:
    float n[4][4];  // Store each value of the matrix

public:
    Matrix4f() = default;

    // TODO: Row or column major order you decide!
    // Matrix constructor with 9 scalar values.
    Matrix4f( float n00, float n01, float n02, float n03,
              float n10, float n11, float n12, float n13,
              float n20, float n21, float n22, float n23,
              float n30, float n31, float n32, float n33){

        n[0][0] = n00; n[0][1] = n10; n[0][2] = n20; n[0][3] = n30;
        n[1][0] = n01; n[1][1] = n11; n[1][2] = n21; n[1][3] = n31;
        n[2][0] = n02; n[2][1] = n12; n[2][2] = n22; n[2][3] = n32;
        n[3][0] = n03; n[3][1] = n13; n[3][2] = n23; n[3][3] = n33;
    }

    // Matrix constructor from four vectors.
    // Note: 'd' will almost always be 0,0,0,1
    Matrix4f(const Vector4f& a, const Vector4f& b, const Vector4f& c, const Vector4f& d){
      n[0][0] = a.x; n[0][1] = b.x; n[0][2] = c.x; n[0][3] = d.x;
      n[1][0] = a.y; n[1][1] = b.y; n[1][2] = c.y; n[1][3] = d.y;
      n[2][0] = a.z; n[2][1] = b.z; n[2][2] = c.z; n[2][3] = d.z;
      n[3][0] = a.w; n[3][1] = b.w; n[3][2] = c.w; n[3][3] = d.w;
    }

    // Makes the matrix an identity matrix
    void identity(){
        n[0][0] = 1; n[0][1] = 0; n[0][2] = 0; n[0][3] = 0;
        n[1][0] = 0; n[1][1] = 1; n[1][2] = 0; n[1][3] = 0;
        n[2][0] = 0; n[2][1] = 0; n[2][2] = 1; n[2][3] = 0;
        n[3][0] = 0; n[3][1] = 0; n[3][2] = 0; n[3][3] = 1;
    }

    // Index operator with two dimensions
    // Example: M(1,1) returns row 1 and column 1 of matrix M.
    float& operator ()(int i, int j){
      return (n[j][i]);
    }

    // Index operator with two dimensions
    // Example: M(1,1) returns row 1 and column 1 of matrix M.
    const float& operator ()(int i, int j) const{
      return (n[j][i]);
    }

    // Return a single vector from the matrix (row or columnn major? hmm).
    Vector4f& operator [](int j){
      return (*reinterpret_cast<Vector4f *>(n[j]));
    }

    // Return a single vector from the matrix (row or columnn major? hmm).
    const Vector4f& operator [](int j) const{
      return (*reinterpret_cast<const Vector4f *>(n[j]));
    }

    // Make a matrix rotate about various axis
    Matrix4f MakeRotationX(float t){
        // TODO:
        // May need radians conversion

        Matrix4f xRotate(
        1, 0, 0, 0,
        0, cos(t), sin(t), 0,
        0, -sin(t), cos(t), 0,
        0, 0, 0, 1);

        Vector4f Col0 = Vector4f((0, 0), (1, 0), (2, 0), (3, 0));
        Vector4f Col1 = Vector4f((0, 1), (1, 1), (2, 1), (3, 1));
        Vector4f Col2 = Vector4f((0, 2), (1, 2), (2, 2), (3, 2));
        Vector4f Col3 = Vector4f((0, 3), (1, 3), (2, 3), (3, 3));

        Matrix4f result;

        result[0][0] = Dot(xRotate.operator[](0), Col0);
        result[1][0] = Dot(xRotate.operator[](1), Col0);
        result[2][0] = Dot(xRotate.operator[](2), Col0);
        result[3][0] = Dot(xRotate.operator[](3), Col0);

        result[0][1] = Dot(xRotate.operator[](0), Col1);
        result[1][1] = Dot(xRotate.operator[](1), Col1);
        result[2][1] = Dot(xRotate.operator[](2), Col1);
        result[3][1] = Dot(xRotate.operator[](3), Col1);

        result[0][2] = Dot(xRotate.operator[](0), Col2);
        result[1][2] = Dot(xRotate.operator[](1), Col2);
        result[2][2] = Dot(xRotate.operator[](2), Col2);
        result[3][2] = Dot(xRotate.operator[](3), Col2);

        result[0][3] = Dot(xRotate.operator[](0), Col3);
        result[1][3] = Dot(xRotate.operator[](1), Col3);
        result[2][3] = Dot(xRotate.operator[](2), Col3);
        result[3][3] = Dot(xRotate.operator[](3), Col3);


        return result;

        // You will need to modify this.
        // When you test, test against glm_gtx_transform
    }

    Matrix4f MakeRotationY(float t){
        // TODO:
        // May need radians conversion

        Matrix4f yRotate(
        cos(t), 0, -sin(t), 0,
        0, 1, 0, 0,
        sin(t), 0, cos(t), 0,
        0, 0, 0, 1);

        // You will need to modify this.
        // When you test, test against glm_gtx_transform
    }
    Matrix4f MakeRotationZ(float t){
        // TODO:
        // May need radians conversion

        Matrix4f zRotate(
        cos(t), -sin(t), 0, 0,
        sin(t), cos(t), 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1);


        // You will need to modify this.
        // When you test, test against glm_gtx_transform
    }
    Matrix4f MakeScale(float sx,float sy, float sz){
        // TODO:

        // Vector4f a = *this
                // Vector4f a(1.0f,0,0,0);

        // Vector4f b(0.0f,1.0f,0,0);
        // Vector4f c(0,0,1.0f,0);
        // Vector4f d(0,0,0,1.0f);

        // Matrix4f temp(a,b,c,d);
        // Matrix4f result; 

        Matrix4f scale(sx, 0, 0, 0,
                        0, sy, 0, 0,
                        0, 0, sz, 0,
                        0, 0, 0, 1);
        Matrix4f temp(this->n[0][0], this->n[1][0], this->n[2][0], this->n[3][0],
                        this->n[0][1], this->n[1][1], this->n[2][1], this->n[3][1],
                        this->n[0][2], this->n[1][2], this->n[2][2], this->n[3][2],
                        this->n[0][3], this->n[1][3], this->n[2][3], this->n[3][3]);

        // Matrix4f result = scale * temp;

        // return temp;

        return scale;

        // You will need to modify this.
        // When you test, test against glm_gtx_transform
    }


};

// Matrix Multiplication
Matrix4f operator *(const Matrix4f& A, const Matrix4f& B){
  // TODO:
  Matrix4f mat4;

  mat4[0][0] = A[0][0] * B[0][0] + A[0][1] * B[1][0] + A[0][2] * B[2][0] + A[0][3] * B[3][0];
  mat4[0][1] = A[0][0] * B[0][1] + A[0][1] * B[1][1] + A[0][2] * B[2][1] + A[0][3] * B[3][1];
  mat4[0][2] = A[0][0] * B[0][2] + A[0][1] * B[1][2] + A[0][2] * B[2][2] + A[0][3] * B[3][2];
  mat4[0][3] = A[0][0] * B[0][3] + A[0][1] * B[1][3] + A[0][2] * B[2][3] + A[0][3] * B[3][3];
  
  mat4[1][0] = A[1][0] * B[0][0] + A[1][1] * B[1][0] + A[1][2] * B[2][0] + A[1][3] * B[3][0];
  mat4[1][1] = A[1][0] * B[0][1] + A[1][1] * B[1][1] + A[1][2] * B[2][1] + A[1][3] * B[3][1];
  mat4[1][2] = A[1][0] * B[0][2] + A[1][1] * B[1][2] + A[1][2] * B[2][2] + A[1][3] * B[3][2];
  mat4[1][3] = A[1][0] * B[0][3] + A[1][1] * B[1][3] + A[1][2] * B[2][3] + A[1][3] * B[3][3];
  
  mat4[2][0] = A[2][0] * B[0][0] + A[2][1] * B[1][0] + A[2][2] * B[2][0] + A[2][3] * B[3][0];
  mat4[2][1] = A[2][0] * B[0][1] + A[2][1] * B[1][1] + A[2][2] * B[2][1] + A[2][3] * B[3][1];
  mat4[2][2] = A[2][0] * B[0][2] + A[2][1] * B[1][2] + A[2][2] * B[2][2] + A[2][3] * B[3][2];
  mat4[2][3] = A[2][0] * B[0][3] + A[2][1] * B[1][3] + A[2][2] * B[2][3] + A[2][3] * B[3][3];

  mat4[3][0] = A[3][0] * B[0][0] + A[3][1] * B[1][0] + A[3][2] * B[2][0] + A[3][3] * B[3][0];
  mat4[3][1] = A[3][0] * B[0][1] + A[3][1] * B[1][1] + A[3][2] * B[2][1] + A[3][3] * B[3][1];
  mat4[3][2] = A[3][0] * B[0][2] + A[3][1] * B[1][2] + A[3][2] * B[2][2] + A[3][3] * B[3][2];
  mat4[3][3] = A[3][0] * B[0][3] + A[3][1] * B[1][3] + A[3][2] * B[2][3] + A[3][3] * B[3][3];

  return mat4;
}

// Matrix multiply by a vector

Vector4f operator *(const Matrix4f& M, const Vector4f& v){
  // TODO:
  Vector4f vec;
  vec[0] = M[0][0] * v[0] + M[0][1] * v[1] + M[0][2] * v[2] + M[0][3] * v[3];

  vec[1] = M[1][0] * v[0] + M[1][1] * v[1] + M[1][2] * v[2] + M[1][3] * v[3];

  vec[2] = M[2][0] * v[0] + M[2][1] * v[1] + M[2][2] * v[2] + M[2][3] * v[3];

  vec[3] = M[3][0] * v[0] + M[3][1] * v[1] + M[3][2] * v[2] + M[3][3] * v[3];

  return vec;
}


#endif
