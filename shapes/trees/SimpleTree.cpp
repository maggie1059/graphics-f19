#include "SimpleTree.h"
#include <cmath>
#include "gl/shaders/ShaderAttribLocations.h"
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
#include <glm/gtx/perpendicular.hpp>
#include "glm/gtc/type_ptr.hpp"
#include <iostream>
#include "../openglshape.h"

SimpleTree::SimpleTree(glm::vec3 origin, int levels):
    m_radius(0.05),
    m_wedges(20),
    m_parser(levels, origin)
{
    m_coords = m_parser.getCoords();
    m_skip_list = m_parser.m_skip_list;
    m_traversal_order = m_parser.m_traversal_order;
}


SimpleTree::~SimpleTree(){
    m_coords.clear();
}

std::vector<std::vector<glm::vec3>> SimpleTree::buildCircles() {
    std::vector<std::vector<glm::vec3>> circle_points;
    circle_points.reserve(m_wedges * m_coords.size());


    // first circle (special case)
    std::vector<glm::vec3> points;
    points.reserve(m_wedges);
    float increment = (2*PI)/m_wedges;
    float y = m_coords[0].y;
    float x = m_coords[0].x;
    float z = m_coords[0].z;
    float theta = 0;

    for (int i = 0; i < m_wedges; i++){
        points.push_back(glm::vec3{x+(m_radius*cos(theta)), y, z+(m_radius*sin(theta))});
        theta += increment;
    }

    circle_points.push_back(points);

    for (int i = 1; i< m_coords.size(); i++){
        if (m_skip_list[i] == true) {
            circle_points.push_back(circle_points[m_traversal_order[i]]);
            continue;
        }
        std::vector<glm::vec3> points;
        points.reserve(m_wedges);
        glm::vec3 end = m_coords[i];

        glm::vec3 direction = end - m_coords[i-1];

        for (glm::vec3 point : circle_points.back()){
            float t_num = (-direction.x * point.x) - (direction.y * point.y) - (direction.z * point.z) + (direction.x * end.x) + (direction.y * end.y ) + (direction.z * end.z);
            float t_denom = pow(direction.x, 2) + pow(direction.y, 2) + pow(direction.z, 2);
            float t = t_num/t_denom;
            float new_x = direction.x * t;
            float new_y = direction.y * t;
            float new_z = direction.z * t;
            float x = point.x + new_x;
            float y = point.y + new_y;
            float z = point.z + new_z;
            points.push_back(glm::vec3{x,y,z});
        }
        circle_points.push_back(points);
    }
    return circle_points;
}


void SimpleTree::build(){
    std::vector<std::vector<glm::vec3>> circles = buildCircles();
    for (int i = 0; i< m_coords.size() - 1; i++){
        std::vector<glm::vec3> start = circles[i];
        std::vector<glm::vec3> end = circles[i+1];
        bool isNegative = true;

        float theta = (2*PI)/m_wedges;
        for (int j = 0; j < m_wedges; j++){
            if (j > m_wedges/2) {
                isNegative = false;
            }
            int next = j+1;
            if (j == m_wedges-1){
                next = 0;
            }
            glm::vec3  normal1 = getNormal(end[j], start[j], start[next], isNegative);
            // triangle 1

            // coord 1
            m_barrelData.push_back(end[j].x);
            m_barrelData.push_back(end[j].y);
            m_barrelData.push_back(end[j].z);

            // normal
            m_barrelData.push_back(normal1.x);
            m_barrelData.push_back(normal1.y);
            m_barrelData.push_back(normal1.z);

            // coord 2
            m_barrelData.push_back(start[j].x);
            m_barrelData.push_back(start[j].y);
            m_barrelData.push_back(start[j].z);

            // normal
            m_barrelData.push_back(normal1.x);
            m_barrelData.push_back(normal1.y);
            m_barrelData.push_back(normal1.z);

            // coord 3
            m_barrelData.push_back(start[next].x);
            m_barrelData.push_back(start[next].y);
            m_barrelData.push_back(start[next].z);

            // normal
            m_barrelData.push_back(normal1.x);
            m_barrelData.push_back(normal1.y);
            m_barrelData.push_back(normal1.z);

            // triangle 2
            glm::vec3  normal2 = getNormal(end[j], start[next], end[next], isNegative);

            // coord 1
            m_barrelData.push_back(end[j].x);
            m_barrelData.push_back(end[j].y);
            m_barrelData.push_back(end[j].z);

            // normal
            m_barrelData.push_back(normal2.x);
            m_barrelData.push_back(normal2.y);
            m_barrelData.push_back(normal2.z);


            // coord 2
            m_barrelData.push_back(start[next].x);
            m_barrelData.push_back(start[next].y);
            m_barrelData.push_back(start[next].z);

            // normal
            m_barrelData.push_back(normal2.x);
            m_barrelData.push_back(normal2.y);
            m_barrelData.push_back(normal2.z);

            // coord 3
            m_barrelData.push_back(end[next].x);
            m_barrelData.push_back(end[next].y);
            m_barrelData.push_back(end[next].z);

            // normal
            m_barrelData.push_back(normal2.x);
            m_barrelData.push_back(normal2.y);
            m_barrelData.push_back(normal2.z);
        }
    }
}

glm::vec3 SimpleTree::getNormal(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, bool isNegative) {
    glm::vec3 u = p2 - p1;
    glm::vec3 v = p3 - p1;

    glm::vec3 normal;
    normal.x = (u.y * v.z) - (u.z * v.y);
    normal.y = (u.z * v.x) - (u.x * v.z);
    normal.z = (u.x * v.y) - (u.y * v.x);
    return glm::cross(u, v);
}

void SimpleTree::buildAndSet() {
    build();

    m_strip = std::make_unique<OpenGLShape>();
    m_strip->setVertexData(m_barrelData.data(), m_barrelData.size(), VBO::GEOMETRY_LAYOUT::LAYOUT_TRIANGLES, m_barrelData.size()/6);
    m_strip->setAttribute(ShaderAttrib::POSITION, 3, 0, VBOAttribMarker::DATA_TYPE::FLOAT, false);
    m_strip->setAttribute(ShaderAttrib::NORMAL, 3, 12, VBOAttribMarker::DATA_TYPE::FLOAT, false);
    m_strip->buildVAO();
}

void SimpleTree::draw(){
    m_strip->draw();
}
