#ifndef MATH_H_INCLUDED
#define MATH_H_INCLUDED

#include <math.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <GL/glew.h>
#include <GL/glu.h>

glm::mat4 getOrtho(int left, int right, int top, int bottom, int near, int far)
{
    glm::mat4 orthomatrix;

    orthomatrix[0].x = 2.0/(right-left);
    orthomatrix[0].y = 0;
    orthomatrix[0].z = 0;
    orthomatrix[0].w = 0;

    orthomatrix[1].x = 0;
    orthomatrix[1].y = 2.0/(top-bottom);
    orthomatrix[1].z = 0;
    orthomatrix[1].w = 0;

    orthomatrix[2].x = 0;
    orthomatrix[2].y = 0;
    orthomatrix[2].z = 2.0/(far-near);
    orthomatrix[2].w = 0;

    orthomatrix[3].x = -(right+left)/(right-left);
    orthomatrix[3].y = -(top+bottom)/(top-bottom);
    orthomatrix[3].z = -(far+near)/(far-near);
    orthomatrix[3].w = 1;

    return orthomatrix;
}

#endif // MATH_H_INCLUDED
