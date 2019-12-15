#ifndef SIMPLETREE_H
#define SIMPLETREE_H
#pragma once

#include "GL/glew.h"
#include <memory>
#include <vector>
#include "StringParser.h"
#define PI 3.14159265
#include "shapes/openglshape.h"
#include "glm/gtc/type_ptr.hpp"   // glm::value_ptr
#include "gl/datatype/VBO.h"
#include "gl/datatype/VBOAttribMarker.h"
#include "glm/glm.hpp"            // glm::vec*, mat*, and basic glm functions
#include "glm/gtx/transform.hpp"  // glm::translate, scale, rotate

class OpenGLShape;
class SimpleTree
{
public:
    SimpleTree(glm::vec3 origin, int levels);
    void drawTree();
    virtual ~SimpleTree();
    void build();
    glm::vec3 getNormal(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, bool isNegative);
    void buildAndSet();
    void draw();

private:
    StringParser m_parser;
    std::vector<glm::vec3> m_coords;
    float m_radius;
    int m_wedges;
    std::unique_ptr<OpenGLShape> m_strip;
    std::vector<GLfloat> m_barrelData;
    std::vector<glm::vec3> getCirclePoints(glm::vec3 center, glm::vec3 prev);
    std::vector<std::vector<glm::vec3>> buildCircles();
    std::vector<bool> m_skip_list;
    std::vector<int> m_traversal_order;

};

#endif // SIMPLETREE_H
