#include "StringGenerator.h"
#include <math.h>

#include <cmath>
#include "gl/shaders/ShaderAttribLocations.h"
#include "glm/glm.hpp"            // glm::vec*, mat*, and basic glm functions
#include "glm/gtx/transform.hpp"  // glm::translate, scale, rotate
#include "glm/gtc/type_ptr.hpp"   // glm::value_ptr

StringGenerator::StringGenerator(int num_recurse):

    m_instructions({DRAW_RETURN})
{
    m_depth = num_recurse;
    m_instructions.reserve(pow(2, m_depth));
}

StringGenerator::~StringGenerator()
{
    m_instructions.clear();
}

std::vector<Instruction> StringGenerator::makeString(){
    std::vector<Instruction> temp;
    temp.reserve(pow(2, m_depth));
    for (int i = 0; i < m_depth; i++){
        for (int i = 0; i < m_instructions.size(); i++){
            Instruction curr = m_instructions[i];

            switch(curr){
                case DRAW:
                    temp.push_back(DRAW);
                    temp.push_back(DRAW);

                    break;
                case DRAW_RETURN:
                    temp.push_back(NEW_LEVEL);
                    temp.push_back(DRAW);
                    temp.push_back(TILT_ROTATE);
                    temp.push_back(DRAW_RETURN);
                    temp.push_back(TILT_ROTATE);
                    temp.push_back(DRAW_RETURN);
                    temp.push_back(TILT_ROTATE);
                    temp.push_back(DRAW_RETURN);
                    temp.push_back(TILT_RETURN);
                    temp.push_back(END_LEVEL);
                    break;
                default:
                    temp.push_back(curr);
                    break;
            }
        }
        m_instructions = temp;
        temp.clear();
    }
    return m_instructions;
}

