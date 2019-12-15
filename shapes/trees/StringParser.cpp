#include "StringParser.h"
#include <stack>
#define PI 3.14159265
#include <cmath>
#include "gl/shaders/ShaderAttribLocations.h"
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <iostream>

StringParser::StringParser(int num_recurse, glm::vec3 origin):
    m_generator(num_recurse), m_recurse(num_recurse)
{
    m_enum_list = m_generator.makeString();
    m_coords.reserve(m_enum_list.size());
    m_coords.push_back(origin);
    m_skip_list.reserve(m_enum_list.size());
    m_skip_list.push_back(false);
    m_traversal_order.reserve(m_coords.size());
    m_traversal_order.push_back(0);

}

StringParser::~StringParser()
{
    m_coords.clear();
}


std::vector<glm::vec3> StringParser::getCoords() {
    float phi = 0;
    float theta = 0;
    float X, Y, Z;

    std::stack<int> go_back;

    std::stack<glm::vec3> levels;
    int count = 1;
    for (int i = 0; i < m_enum_list.size(); i++) {
        Instruction elem = m_enum_list[i];
        X = sin(phi) * cos(theta);
        Y = cos(phi);
        Z = sin(phi) * sin(theta);
        glm::vec3 last = m_coords.back();
        if (abs(theta-(2*PI)) < exp(-5)){
            theta = 0;
        }
        switch(elem) {
            case DRAW:
                m_coords.push_back(last + glm::vec3(X, Y, Z));
                m_skip_list.push_back(false);
                m_traversal_order.push_back(count);
                count ++;
                if (m_enum_list[i+1] == DRAW && i+1 < m_enum_list.size()) {
                   go_back.push(m_traversal_order.back());

                }
                break;
            case DRAW_RETURN:
                m_coords.push_back(last + glm::vec3(X, Y, Z));
                m_skip_list.push_back(false);

                m_coords.push_back(last);
                m_skip_list.push_back(true);
                m_traversal_order.push_back(count);
                count++;
                if (!go_back.empty()) {
                    m_traversal_order.push_back(go_back.top());
                    go_back.pop();
                }
                count++;
                phi -= THIRTY;
                break;
            case TILT_ROTATE:
                phi += THIRTY;
                theta += ONE_TWENTY;
                go_back.push(m_traversal_order.back());
                break;
            case TILT_RETURN:
                phi -= THIRTY;
                break;
            case NEW_LEVEL:
                levels.push(last);
                go_back.push(m_traversal_order.back());
                break;
            case END_LEVEL:
                glm::vec3 stack_last = levels.top();
                levels.pop();
                m_traversal_order.push_back(go_back.top());
                go_back.pop();

                m_coords.push_back(stack_last);
                m_skip_list.push_back(true);
                count++;
                break;
        }

    }
    if (m_recurse > 1) {
        m_traversal_order.pop_back();
        while (!go_back.empty()) {
            while(go_back.top() == m_traversal_order.back()){
                go_back.pop();
            }
            m_traversal_order.push_back(go_back.top());
            go_back.pop();
        }
        m_coords[m_coords.size()-1] = glm::vec3(0, 1, 0);
        m_coords.push_back(glm::vec3(0,0,0));
        m_skip_list.push_back(true);
    }

    for (int i = 0; i < m_traversal_order.size(); i++) {
       if (m_skip_list[i] == true) {
       }
    }
    return m_coords;
}

