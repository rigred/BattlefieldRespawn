#include <stdio.h>
#include <stdlib.h>
#include <string>

// three dimensional floating point vector
struct float3 // 12 bytes
{
    float x;
    float y;
    float z;
};


// bounding box
struct aabb // 24 bytes
{
    float3 min;
    float3 max;
};


// 4x4 transformation matrix
struct matrix4 // 64 bytes
{
    float m[4][4];
};


