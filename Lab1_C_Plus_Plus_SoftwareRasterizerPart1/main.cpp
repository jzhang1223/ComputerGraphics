/** @file main.cpp
 *  @brief Entry point into our program.
 *  
 *  Welcome to the Great Looking Software Render 
 *  code base (Yes, I needed something with a gl prefix).
 *
 *  This is where you will implement your graphics API.
 *
 *  Compile on the terminal with: 
 *
 *  clang++ -std=c++11 main.cpp -o main
 *
 *  @author Mike Shah
 *  @bug No known bugs.
 */

// Load our libraries
#include <iostream>

// Some define values
#define WINDOW_HEIGHT 320
#define WINDOW_WIDTH 320

// C++ Standard Libraries
#include <iostream>

// User libraries
#include "GL.h"
#include "Color.h"
#include "TGA.h"
#include "Maths.h"

// Create a canvas to draw on.
TGA canvas(WINDOW_WIDTH,WINDOW_HEIGHT);


// Implementation of Bresenham's Line Algorithm
// The input to this algorithm is two points and a color
// This algorithm will then modify a canvas (i.e. image)
// filling in the appropriate colors.
void drawLine(Vec2 v0, Vec2 v1, TGA& image, ColorRGB c){
    bool steep = false;
    if(std::abs(v0.x-v1.x)<std::abs(v0.y-v1.y)){
        // If the line is steep we want to transpose the image.
        std::swap(v0.x,v0.y);
        std::swap(v1.x,v1.y);
        steep = true;
    }
    if(v0.x>v1.x){  // make it left-to-right
        std::swap(v0.x, v1.x);
        std::swap(v0.y, v1.y);
    }
    for(int x = v0.x; x <= v1.x; ++x){
        float t = (x-v0.x)/(float)(v1.x-v0.x);
        int y = v0.y*(1.0f-t) + v1.y*t;
        if(steep){
            canvas.setPixelColor(y,x,c);
        }else{
            canvas.setPixelColor(x,y,c);
        }
    }
}

// Calculate the determinant of 2x2 vectors.
int determinant(Vec2 u, Vec2 v) {
    return u.x * v.y - u.y * v.x;
}

// Determine if the point v is in the triangle.
bool inTriangle(Vec2 v0, Vec2 v1, Vec2 v) {

    float a = (float)determinant(v, v1) / determinant(v0, v1);
    float b = (float)determinant(v0, v) / determinant(v0, v1);

    return a >= 0 && b >= 0 && a + b <= 1;
}

// Draw a triangle
void triangle(Vec2 v0, Vec2 v1, Vec2 v2,TGA& image, ColorRGB c){
    ColorRGB outline;
    outline.r = 240; 
    outline.g = 230;
    outline.b = 140;

    int maxX = std::max(v0.x, std::max(v1.x, v2.x));
    int maxY = std::max(v0.y, std::max(v1.y, v2.y));
    int minX = std::min(v0.x, std::min(v1.x, v2.x));
    int minY = std::min(v0.y, std::min(v1.y, v2.y));

    Vec2 vn0 = Vec2(v1.x - v0.x, v1.y - v0.y);
    Vec2 vn1 = Vec2(v2.x - v0.x, v2.y - v0.y);

    // Loop over the square min and max bounds of x and y
    for(int i = minX; i <= maxX; i++) {
        for(int j = minY; j <= maxY; j++) {
            Vec2 vn = Vec2(i - v0.x, j - v0.y);
            if (inTriangle(vn0, vn1, vn)) {
                canvas.setPixelColor(i,j,c);
            }
        }
    }

    // Draw the outline of the triangle (for testing)
    drawLine(v0,v1,image,outline);
    drawLine(v1,v2,image,outline);
    drawLine(v2,v0,image,outline);
}

// Main
int main(){

    // A sample of color(s) to play with
    ColorRGB red;
    red.r = 255; red.g = 0; red.b = 0;
    ColorRGB green;
    green.r = 0; green.g = 255; green.b = 0;
    ColorRGB blue;
    blue.r = 0; blue.g = 0; blue.b = 255;
        
    // Points for our Line
    Vec2 line[2] = {Vec2(0,0), Vec2(100,100)};

    // Set the fill mode
    glPolygonMode(LINE);

    // Draw a line
    drawLine(line[0],line[1],canvas,red);

    // Data for our triangle
    Vec2 tri[3] = {Vec2(160,60), Vec2(150,10), Vec2(75,190)};
    Vec2 tri1[3] = {Vec2(100,200), Vec2(250,75), Vec2(300,175)};
    Vec2 tri2[3] = {Vec2(200,225), Vec2(250,299), Vec2(180,275)};

    // Draw a triangle
    triangle(tri[0],tri[1],tri[2],canvas,red);
    triangle(tri1[0],tri1[1],tri1[2],canvas,green);
    triangle(tri2[0],tri2[1],tri2[2],canvas,blue);

    // Output the final image
    canvas.outputTGAImage("graphics_lab2.ppm");

    return 0;
}
