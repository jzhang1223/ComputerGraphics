// Includes for the assignment
#include "Vector4f.h"
#include "Matrix4f.h"
#include <iostream>

// Tests for comparing our library
// You may compare your operations against the glm library
// which is a well tested library.
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/projection.hpp>

// Sample unit test comparing against GLM.
bool unitTest0(){
	glm::mat4 glmIdentityMatrix = glm::mat4(1.0f);
	Matrix4f myIdentity( 1.0f,0,0,0,
        			     0,1.0f,0,0,
		        	     0,0,1.0f,0,
			             0,0,0,1.0f);

    if(
        glmIdentityMatrix[0][0]==myIdentity[0][0] &&
        glmIdentityMatrix[0][1]==myIdentity[0][1] &&
        glmIdentityMatrix[0][2]==myIdentity[0][2] &&
        glmIdentityMatrix[0][3]==myIdentity[0][3] &&
        glmIdentityMatrix[1][0]==myIdentity[1][0] &&
        glmIdentityMatrix[1][1]==myIdentity[1][1] &&
        glmIdentityMatrix[1][2]==myIdentity[1][2] &&
        glmIdentityMatrix[1][3]==myIdentity[1][3] &&
        glmIdentityMatrix[2][0]==myIdentity[2][0] &&
        glmIdentityMatrix[2][1]==myIdentity[2][1] &&
        glmIdentityMatrix[2][2]==myIdentity[2][2] &&
        glmIdentityMatrix[2][3]==myIdentity[2][3] &&
        glmIdentityMatrix[3][0]==myIdentity[3][0] &&
        glmIdentityMatrix[3][1]==myIdentity[3][1] &&
        glmIdentityMatrix[3][2]==myIdentity[3][2] &&
        glmIdentityMatrix[3][3]==myIdentity[3][3]){
            return true;
    }
	
    return false;	
}

bool unitTest1(){
	glm::mat4 glmIdentityMatrix = glm::mat4(1.0f);
	Matrix4f myIdentity( 1.0f,0,0,0,
        			     0,1.0f,0,0,
		        	     0,0,1.0f,0,
			             0,0,0,1.0f);

    if(
        glmIdentityMatrix[0][0]==myIdentity(0,0) &&
        glmIdentityMatrix[0][1]==myIdentity(0,1) &&
        glmIdentityMatrix[0][2]==myIdentity(0,2) &&
        glmIdentityMatrix[0][3]==myIdentity(0,3) &&
        glmIdentityMatrix[1][0]==myIdentity(1,0) &&
        glmIdentityMatrix[1][1]==myIdentity(1,1) &&
        glmIdentityMatrix[1][2]==myIdentity(1,2) &&
        glmIdentityMatrix[1][3]==myIdentity(1,3) &&
        glmIdentityMatrix[2][0]==myIdentity(2,0) &&
        glmIdentityMatrix[2][1]==myIdentity(2,1) &&
        glmIdentityMatrix[2][2]==myIdentity(2,2) &&
        glmIdentityMatrix[2][3]==myIdentity(2,3) &&
        glmIdentityMatrix[3][0]==myIdentity(3,0) &&
        glmIdentityMatrix[3][1]==myIdentity(3,1) &&
        glmIdentityMatrix[3][2]==myIdentity(3,2) &&
        glmIdentityMatrix[3][3]==myIdentity(3,3)){
            return true;
    }
	
    return false;	
}

// Sample unit test comparing against GLM.
bool unitTest2(){
	glm::mat4 glmIdentityMatrix = glm::mat4(1.0f);
	Vector4f a(1.0f ,0.0f,  0.0f,   0.0f);
	Vector4f b(0.0f ,1.0f,  0.0f,   0.0f);
	Vector4f c(0.0f ,0.0f,  1.0f,   0.0f);
	Vector4f d(0.0f ,0.0f,  0.0f,   1.0f);
	Matrix4f myIdentity(a,b,c,d);

    if(
        glmIdentityMatrix[0][0]==myIdentity[0][0] &&
        glmIdentityMatrix[0][1]==myIdentity[0][1] &&
        glmIdentityMatrix[0][2]==myIdentity[0][2] &&
        glmIdentityMatrix[0][3]==myIdentity[0][3] &&
        glmIdentityMatrix[1][0]==myIdentity[1][0] &&
        glmIdentityMatrix[1][1]==myIdentity[1][1] &&
        glmIdentityMatrix[1][2]==myIdentity[1][2] &&
        glmIdentityMatrix[1][3]==myIdentity[1][3] &&
        glmIdentityMatrix[2][0]==myIdentity[2][0] &&
        glmIdentityMatrix[2][1]==myIdentity[2][1] &&
        glmIdentityMatrix[2][2]==myIdentity[2][2] &&
        glmIdentityMatrix[2][3]==myIdentity[2][3] &&
        glmIdentityMatrix[3][0]==myIdentity[3][0] &&
        glmIdentityMatrix[3][1]==myIdentity[3][1] &&
        glmIdentityMatrix[3][2]==myIdentity[3][2] &&
        glmIdentityMatrix[3][3]==myIdentity[3][3]){
            return true;
    }
	
    return false;	
}

// Sample unit test comparing against GLM.
// Testing operator
bool unitTest4(){
	glm::mat4 glmTest = glm::mat4(1.0f);
    glmTest[1][3] = 72.0f;
    glmTest[2][3] = 2.1f;

	Matrix4f myMatrix(0,0,0,0,
                      0,0,0,0,
                      0,0,0,0,
                      0,0,0,0);

    myMatrix[1][3] = 72.0f;
    myMatrix[2][3] = 2.1f;

    if( glmTest[1][3]==myMatrix[1][3] &&
        glmTest[2][3]==myMatrix[2][3] ){
            return true;
    }
	
    return false;	
}

// Sample unit test testing your library
bool unitTest5(){
  Vector4f a(1,1,1,1);
  Vector4f b(0,0,0,0);
  Vector4f c = a + b;

  if(c.x == 1 && c.y == 1 && c.z ==1 && c.w==1){
    return true;
  }
    return false;
}

// Test Vector4f -> Dot
bool test_v_dot_0() {
    Vector4f v1 = Vector4f(1, 3, 4, 2);
    Vector4f v2 = Vector4f(4, 3, 1, 2);

    glm::vec4 e = glm::vec4(1.0f, 3.0f, 4.0f, 2.0f);
    glm::vec4 f = glm::vec4(4.0f, 3.0f, 1.0f, 2.0f);

    float result1 = Dot(v1, v2);
    float result2 = glm::dot(e, f);
    
    if (result1 == result2) {
        return true;
    } else {
        return false;
    }
    return true;
}

// Test multiply vector by a scalar
bool test_v_scalarmult_0() {
    Vector4f v1 = Vector4f(1.0f, 3.0f, 4.0f, 2.0f);
    glm::vec4 e = glm::vec4(1.0f, 3.0f, 4.0f, 2.0f);

    float scaleFactor = 2;

    Vector4f result1 = v1 * scaleFactor;
    glm::vec4 result2 = e * scaleFactor;

    for (int i = 0; i < 4; i++) {
        if (result1[i] != result2[i]) {
            return false;
        }
    }
    return true;
}

// Test divide vector by a scalar
bool test_v_scalardiv_0() {
    Vector4f v1 = Vector4f(1.0f, 3.0f, 4.0f, 2.0f);
    glm::vec4 e = glm::vec4(1.0f, 3.0f, 4.0f, 2.0f);

    float scaleFactor = 2;

    Vector4f result1 = v1 / scaleFactor;
    glm::vec4 result2 = e / scaleFactor;

    for (int i = 0; i < 4; i++) {
        if (result1[i] != result2[i]) {
            return false;
        }
    }
    return true;
}

// Test negating vector
bool test_v_negate_0() {
    Vector4f v1 = Vector4f(1.0f, 3.0f, 4.0f, 2.0f);
    glm::vec4 e = glm::vec4(1.0f, 3.0f, 4.0f, 2.0f);

    Vector4f result1 = -v1;
    glm::vec4 result2 = -e;

    for (int i = 0; i < 4; i++) {
        if (result1[i] != result2[i]) {
            return false;
        }
    }
    return true;
}

// Test magnitude of a vector
bool test_v_magnitude_0() {
    Vector4f v1 = Vector4f(1.0f, 3.0f, 4.0f, 2.0f);
    glm::vec4 e = glm::vec4(1.0f, 3.0f, 4.0f, 2.0f);

    float result1 = Magnitude(v1);
    float result2 = glm::length(e);

    if (result1 == result2) {
        return true;
    } else {
        return false;
    }
    return true;
}

// Test sum of 2 vectors
bool test_v_sum_0() {
    Vector4f v1 = Vector4f(1.0f, 3.0f, 4.0f, 2.0f);
    Vector4f v2 = Vector4f(4.0f, 3.0f, 1.0f, 2.0f);

    glm::vec4 e = glm::vec4(1.0f, 3.0f, 4.0f, 2.0f);
    glm::vec4 f = glm::vec4(4.0f, 3.0f, 1.0f, 2.0f);

    Vector4f result1 = v1 + v2;
    glm::vec4 result2 = e + f;
    
    for (int i = 0; i < 4; i++) {
        if (result1[i] != result2[i]) {
            return false;
        }
    }
    return true;
}

// Test subtraction of 2 vectors
bool test_v_minus_0() {
    Vector4f v1 = Vector4f(1.0f, 3.0f, 4.0f, 2.0f);
    Vector4f v2 = Vector4f(4.0f, 3.0f, 1.0f, 2.0f);

    glm::vec4 e = glm::vec4(1.0f, 3.0f, 4.0f, 2.0f);
    glm::vec4 f = glm::vec4(4.0f, 3.0f, 1.0f, 2.0f);

    Vector4f result1 = v1 - v2;
    glm::vec4 result2 = e - f;
    
    for (int i = 0; i < 4; i++) {
        if (result1[i] != result2[i]) {
            return false;
        }
    }
    return true;
}

// Test normalization of a vector
bool test_v_normalize_0() {
    Vector4f v1 = Vector4f(1.0f, 3.0f, 4.0f, 2.0f);
    glm::vec4 e = glm::vec4(1.0f, 3.0f, 4.0f, 2.0f);

    Vector4f result1 = Normalize(v1);
    glm::vec4 result2 = glm::normalize(e);

    for (int i = 0; i < 4; i++) {
        if (std::abs(result1[i] - result2[i]) > 0.0001f) {
            return false;
        }
    }
    return true;
}

// Test projection of a vector
bool test_v_projection_0() {
    Vector4f v1 = Vector4f(1.0f, 3.0f, 4.0f, 2.0f);
    Vector4f v2 = Vector4f(4.0f, 3.0f, 1.0f, 2.0f);

    // Vector Multiplication
    glm::vec4 e = glm::vec4(1.0f, 3.0f, 4.0f, 2.0f);
    glm::vec4 f = glm::vec4(4.0f, 3.0f, 1.0f, 2.0f);

    Vector4f result1 = Project(v1, v2);
    glm::vec4 result2 = glm::proj(e, f);

    for (int i = 0; i < 4; i++) {
        if (std::abs(result1[i] - result2[i]) > 0.0001f) {
            return false;
        }
    }
    return true;
}

// Test cross product of a vector
bool test_v_crossproduct_0() {
    Vector4f v1 = Vector4f(1.0f, 3.0f, 4.0f, 1.0f);
    Vector4f v2 = Vector4f(4.0f, 3.0f, 1.0f, 1.0f);

    // Vector Multiplication
    glm::vec3 e = glm::vec3(1.0f, 3.0f, 4.0f);
    glm::vec3 f = glm::vec3(4.0f, 3.0f, 1.0f);

    Vector4f result1 = CrossProduct(v1, v2);
    glm::vec3 result2 = glm::cross(e, f);

    for (int i = 0; i < 3; i++) {
        if (std::abs(result1[i] - result2[i]) > 0.0001f) {
            return false;
        }
    }
    return true;
}

// Test Vector4f constructor
bool test_v_constructor_0() {
    Vector4f v1 = Vector4f(1.0f, 3.0f, 4.0f, 1.0f);
    glm::vec4 e = glm::vec4(1.0f, 3.0f, 4.0f, 1.0f);

    for (int i = 0; i < 4; i++) {
        if (std::abs(v1[i] - e[i]) > 0.0001f) {
            return false;
        }
    }
    return true;
}

// Test vector *= scalar
bool test_v_multequals_0() {
    Vector4f v1 = Vector4f(1.0f, 3.0f, 4.0f, 1.0f);
    glm::vec4 e = glm::vec4(1.0f, 3.0f, 4.0f, 1.0f);

    float scaleFactor = 2;

    v1 *= scaleFactor;
    e *= scaleFactor;

    for (int i = 0; i < 4; i++) {
        if (std::abs(v1[i] - e[i]) > 0.0001f) {
            return false;
        }
    }
    return true;
}

// Test vector /= scalar
bool test_v_divequals_0() {
    Vector4f v1 = Vector4f(1.0f, 3.0f, 4.0f, 1.0f);
    glm::vec4 e = glm::vec4(1.0f, 3.0f, 4.0f, 1.0f);

    float scaleFactor = 2;

    v1 /= scaleFactor;
    e /= scaleFactor;

    for (int i = 0; i < 4; i++) {
        if (std::abs(v1[i] - e[i]) > 0.0001f) {
            return false;
        }
    }
    return true;
}

// Test vector += vector
bool test_v_plusequals_0() {
    Vector4f v1 = Vector4f(1.0f, 3.0f, 4.0f, 2.0f);
    Vector4f v2 = Vector4f(4.0f, 3.0f, 1.0f, 2.0f);

    glm::vec4 e = glm::vec4(1.0f, 3.0f, 4.0f, 2.0f);
    glm::vec4 f = glm::vec4(4.0f, 3.0f, 1.0f, 2.0f);

    v1 += v2;
    e += f;

    for (int i = 0; i < 4; i++) {
        if (std::abs(v1[i] - e[i]) > 0.0001f) {
            return false;
        }
    }
    return true;
}

// Test vector -= vector
bool test_v_minusequals_0() {
    Vector4f v1 = Vector4f(1.0f, 3.0f, 4.0f, 2.0f);
    Vector4f v2 = Vector4f(4.0f, 3.0f, 1.0f, 2.0f);

    glm::vec4 e = glm::vec4(1.0f, 3.0f, 4.0f, 2.0f);
    glm::vec4 f = glm::vec4(4.0f, 3.0f, 1.0f, 2.0f);

    v1 -= v2;
    e -= f;

    for (int i = 0; i < 4; i++) {
        if (std::abs(v1[i] - e[i]) > 0.0001f) {
            return false;
        }
    }
    return true;
}

bool test_m_identity_values() {
    Matrix4f m1;
    m1.identity();

    for(int i = 0; i < 4; ++i) {
        for(int j = 0; j < 4; ++j) {
            if(j == i && m1[i][j] != 1) {
                return false;
            }
            if(j != i && m1[i][j] != 0) {
                return false;
            }
        }
    }
    return true;
}

bool test_m_rotateX() {

    float angle = 5.f;
    Matrix4f m1(5,2,8,3,
                7,3,10,3,
                9,3,2,4,
                10,8,3,8);


    m1.MakeRotationX(angle);


    glm::vec4 gv1(5.0f, 2.0f, 8.0f, 3.0f);
    glm::vec4 gv2(7.0f, 3.0f, 10.0f, 3.0f);
    glm::vec4 gv3(9.0f, 3.0f, 2.0f, 4.0f);
    glm::vec4 gv4(10.0f, 8.0f, 3.0f, 8.0f);
    glm::mat4 gm1(gv1, gv2, gv3, gv4);

    gm1 = glm::rotate(angle, glm::vec3(1,0,0));



    for(int i = 0; i < 4; ++i) {
        for(int j = 0; j < 4; ++j) {
            if(abs(m1[i][j] - gm1[i][j]) > .0001f) {
                return false;
            }
        }
    }
    return true;
}

bool test_m_rotateY() {

    float angle = 7.f;
    Matrix4f m1(5,2,8,3,
                7,3,10,3,
                9,3,2,4,
                10,8,3,8);


    m1.MakeRotationY(angle);



    glm::vec4 gv1(5.0f, 2.0f, 8.0f, 3.0f);
    glm::vec4 gv2(7.0f, 3.0f, 10.0f, 3.0f);
    glm::vec4 gv3(9.0f, 3.0f, 2.0f, 4.0f);
    glm::vec4 gv4(10.0f, 8.0f, 3.0f, 8.0f);
    glm::mat4 gm1(gv1, gv2, gv3, gv4);

    gm1 = glm::rotate(angle, glm::vec3(0,1,0));



    for(int i = 0; i < 4; ++i) {
        for(int j = 0; j < 4; ++j) {
            if(abs(m1[i][j] - gm1[i][j]) > .0001f) {
                return false;
            }
        }
    }
    return true;
}

bool test_m_rotateZ() {

    float angle = 9.f;
    Matrix4f m1(5,2,8,3,
                7,3,10,3,
                9,3,2,4,
                10,8,3,8);


    m1.MakeRotationZ(angle);


    glm::vec4 gv1(5.0f, 2.0f, 8.0f, 3.0f);
    glm::vec4 gv2(7.0f, 3.0f, 10.0f, 3.0f);
    glm::vec4 gv3(9.0f, 3.0f, 2.0f, 4.0f);
    glm::vec4 gv4(10.0f, 8.0f, 3.0f, 8.0f);
    glm::mat4 gm1(gv1, gv2, gv3, gv4);

    gm1 = glm::rotate(angle, glm::vec3(0,0,1));



    for(int i = 0; i < 4; ++i) {
        for(int j = 0; j < 4; ++j) {
            if(abs(m1[i][j] - gm1[i][j]) > .0001f) {
                return false;
            }
        }
    }
    return true;
}

bool test_m_scale() {

    float scaleX = 1.5f;
    float scaleY = 0.5f;
    float scaleZ = 2.0f;

    Matrix4f m1(5,2,8,3,
                7,3,10,3,
                9,3,2,4,
                10,8,3,8);
    m1.MakeScale(scaleX, scaleY, scaleZ);

    glm::vec4 gv1(5.0f, 2.0f, 8.0f, 3.0f);
    glm::vec4 gv2(7.0f, 3.0f, 10.0f, 3.0f);
    glm::vec4 gv3(9.0f, 3.0f, 2.0f, 4.0f);
    glm::vec4 gv4(10.0f, 8.0f, 3.0f, 8.0f);
    glm::mat4 gm1(gv1, gv2, gv3, gv4);

    gm1 = glm::scale(glm::vec3(scaleX, scaleY, scaleZ));

    for(int i = 0; i < 4; ++i) {
        for(int j = 0; j < 4; ++j) {
            if(abs(m1[i][j] - gm1[i][j]) > .0001f) {
                return false;
            }
        }
    }
    return true;
}



bool test_m_multiply_values(){
        Matrix4f m1(5,2,8,3,
                      7,3,10,3,
                      9,3,2,4,
                      10,8,3,8);
        Matrix4f m2(3,12,9,3,
                      10,1,10,12,
                      12,4,12,4,
                      18,9,2,10);
        Matrix4f m3 = m1 * m2;

        return (m3[0][0] == 210 && m3[1][0] == 93 && m3[2][0] == 171 && m3[3][0] == 105 && 
                m3[0][1] == 267 && m3[1][1] == 149 && m3[2][1] == 146 && m3[3][1] == 169 && 
                m3[0][2] == 236 && m3[1][2] == 104 && m3[2][2] == 172 && m3[3][2] == 128 && 
                m3[0][3] == 271 && m3[1][3] == 149 && m3[2][3] == 268 && m3[3][3] == 169);
}

bool test_m_multiply_glm(){


    Matrix4f m1(5,2,8,3,
                7,3,10,3,
                9,3,2,4,
                10,8,3,8);
    Matrix4f m2(3,12,9,3,
                10,1,10,12,
                12,4,12,4,
                18,9,2,10);
    Matrix4f m3 = m1 * m2;

    glm::vec4 gv1(5.0f, 2.0f, 8.0f, 3.0f);
    glm::vec4 gv2(7.0f, 3.0f, 10.0f, 3.0f);
    glm::vec4 gv3(9.0f, 3.0f, 2.0f, 4.0f);
    glm::vec4 gv4(10.0f, 8.0f, 3.0f, 8.0f);


    glm::mat4 gm1 = glm::mat4(gv1, gv2, gv3, gv4);

    glm::vec4 gv11(3.0f, 12.0f, 9.0f, 3.0f);
    glm::vec4 gv22(10.0f, 1.0f, 10.0f, 12.0f);
    glm::vec4 gv33(12.0f, 4.0f, 12.0f, 4.0f);
    glm::vec4 gv44(18.0f, 9.0f, 2.0f, 10.0f);

    glm::mat4 gm2 = glm::mat4(gv11, gv22, gv33, gv44);

    glm::mat4 gm3 = gm1 * gm2;

    return (gm3[0][0]==m3(0,0) &&
            gm3[0][1]==m3(0,1) &&
            gm3[0][2]==m3(0,2) &&
            gm3[0][3]==m3(0,3) &&
            gm3[1][0]==m3(1,0) &&
            gm3[1][1]==m3(1,1) &&
            gm3[1][2]==m3(1,2) &&
            gm3[1][3]==m3(1,3) &&
            gm3[2][0]==m3(2,0) &&
            gm3[2][1]==m3(2,1) &&
            gm3[2][2]==m3(2,2) &&
            gm3[2][3]==m3(2,3) &&
            gm3[3][0]==m3(3,0) &&
            gm3[3][1]==m3(3,1) &&
            gm3[3][2]==m3(3,2) &&
            gm3[3][3]==m3(3,3));
}

bool test_m_multiply_vector() {
    Matrix4f m1(5,2,8,3,
                7,3,10,3,
                9,3,2,4,
                10,8,3,8);
    Vector4f v1(3,8,6,2);

    Vector4f result = m1 * v1;

    Vector4f answer(145,64,122,73);


    return (answer[0] == result[0] &&
            answer[1] == result[1] &&
            answer[2] == result[2] &&
            answer[3] == result[3]);
}

bool test_m_multiply_vector_glm() {
    Matrix4f m1(5,2,8,3,
                7,3,10,3,
                9,3,2,4,
                10,8,3,8);
    Vector4f v1(3,8,6,2);


    Vector4f result = m1 * v1;

    glm::vec4 gv1(5.0f, 2.0f, 8.0f, 3.0f);
    glm::vec4 gv2(7.0f, 3.0f, 10.0f, 3.0f);
    glm::vec4 gv3(9.0f, 3.0f, 2.0f, 4.0f);
    glm::vec4 gv4(10.0f, 8.0f, 3.0f, 8.0f);
    glm::mat4 gm1 = glm::mat4(gv1, gv2, gv3, gv4);



    glm::vec4 gv11(3,8,6,2);

    glm::vec4 answer = gm1 * gv11;



    return (answer[0] == result[0] &&
            answer[1] == result[1] &&
            answer[2] == result[2] &&
            answer[3] == result[3]);
}

int main(){
    // Keep track of the tests passed
    unsigned int testsPassed = 0;

    // Run 'unit tests'
    std::cout << "Passed 0: " << unitTest0() << " \n";
    std::cout << "Passed 1: " << unitTest1() << " \n";
    std::cout << "Passed 2: " << unitTest2() << " \n";
    std::cout << "Passed 4: " << unitTest4() << " \n";
    std::cout << "Passed 5: " << unitTest5() << " \n";

    std::cout << "Passed 6 (Vector Dot Product): -------------------" << test_v_dot_0() << " \n";
    std::cout << "Passed 7 (Vector * Scalar): ---------------" << test_v_scalarmult_0() << " \n";
    std::cout << "Passed 8 (Vector / Scalar): ----------------" << test_v_scalardiv_0() << " \n";
    std::cout << "Passed 9 (-Vector): ---------------------------" << test_v_negate_0() << " \n";
    std::cout << "Passed 10 (Magnitude of Vector): -----------" << test_v_magnitude_0() << " \n";
    std::cout << "Passed 11 (Sum of vectors): ----------------------" << test_v_sum_0() << " \n";
    std::cout << "Passed 12 (Subtraction of vectors): ------------" << test_v_minus_0() << " \n";
    std::cout << "Passed 13 (Normalize a vector): ------------" << test_v_normalize_0() << " \n";
    std::cout << "Passed 14 (Projection onto a vector): -----" << test_v_projection_0() << " \n";
    std::cout << "Passed 15 (Cross product of 2 vectors): ---" << test_v_crossproduct_0() << " \n";
    std::cout << "Passed 16 (Vector4f constructor: ---------" << test_v_constructor_0() << " \n";
    std::cout << "Passed 17 (Vector *= scalar): -------------" << test_v_multequals_0() << " \n";
    std::cout << "Passed 18 (Vector /= scalar): --------------" << test_v_divequals_0() << " \n";
    std::cout << "Passed 19 (Vector += scalar): -------------" << test_v_plusequals_0() << " \n";
    std::cout << "Passed 20 (Vector -= scalar): ------------" << test_v_minusequals_0() << " \n";

    std::cout << "Passed test_m_multiply_values: ----------" << test_m_multiply_values() << "\n";
    std::cout << "Passed test_m_multiply_glm: ----------------" << test_m_multiply_glm() << "\n";
    std::cout << "Passed test_m_multiply_vector: ----------" << test_m_multiply_vector() << "\n";
    std::cout << "Passed test_m_multiply_vector_glm: -----" << test_m_multiply_vector_glm() << "\n";
    std::cout << "Passed test_m_identity_values: ----------" << test_m_identity_values() << "\n";
    std::cout << "Passed test_m_rotateX: -----------------" << test_m_rotateX() << "\n";
    std::cout << "Passed test_m_rotateY: -----------------" << test_m_rotateY() << "\n";
    std::cout << "Passed test_m_rotateZ: -----------------" << test_m_rotateZ() << "\n";
    std::cout << "Passed test_m_scale: -----------------" << test_m_scale() << "\n";




    return 0;
}
