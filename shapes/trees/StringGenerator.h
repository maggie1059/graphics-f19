#ifndef STRINGGENERATOR_H
#define STRINGGENERATOR_H

#include <cmath>
#include "gl/shaders/ShaderAttribLocations.h"
#include "glm/glm.hpp"            // glm::vec*, mat*, and basic glm functions
#include "glm/gtx/transform.hpp"  // glm::translate, scale, rotate
#include "glm/gtc/type_ptr.hpp"   // glm::value_ptr
#include "GL/glew.h"
#include <memory>
#include <vector>
#include "shapes/openglshape.h"


enum Instruction {
    DRAW,
    DRAW_RETURN,
    TILT_ROTATE,
    TILT_RETURN,
    NEW_LEVEL,
    END_LEVEL
};

class StringGenerator
{
public:
    StringGenerator(int num_recurse);
    std::vector<Instruction> makeString();
    virtual ~StringGenerator();

private:
    int m_depth;
    std::vector<Instruction> m_instructions;

};

#endif // STRINGGENERATOR_H
