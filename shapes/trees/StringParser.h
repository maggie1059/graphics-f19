#ifndef STRINGPARSER_H
#define STRINGPARSER_H

#define PI 3.14159265
#include "StringGenerator.h"
#include "glm/glm.hpp"            // glm::vec*, mat*, and basic glm functions
#include "glm/gtx/transform.hpp"  // glm::translate, scale, rotate
#include "glm/gtc/type_ptr.hpp"   // glm::value_ptr
#include "GL/glew.h"
#include <memory>
#include <vector>
#include "shapes/openglshape.h"

#define THIRTY 30.0f * (PI/180.0f)
#define ONE_TWENTY 120.0f * (PI/180.0f)

class StringParser
{
public:
    StringParser(int num_recurse, glm::vec3 origin);
    virtual ~StringParser();
    std::vector<glm::vec3> getCoords();
    std::vector<bool> m_skip_list;
    std::vector<int> m_traversal_order;

protected:


private:
    StringGenerator m_generator;
    std::vector<Instruction> m_enum_list;
    std::vector<glm::vec3> m_coords;

};

#endif // STRINGPARSER_H
