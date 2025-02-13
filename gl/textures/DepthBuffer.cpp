#include "DepthBuffer.h"

#include "GL/glew.h"

using namespace CS123::GL;

DepthBuffer::DepthBuffer(int width, int height) :
    m_width(width),
    m_height(height)
{
    // TODO [Task 8] bind() the render buffer and call glRenderbufferStorageEXT
    glBindRenderbuffer(GL_RENDERBUFFER, m_handle);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, m_width, m_height);
    // TODO Don't forget to unbind()!
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}
