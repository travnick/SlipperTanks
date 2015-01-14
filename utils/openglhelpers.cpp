#include <QOpenGLFunctions>

#include "openglhelpers.hpp"

void utils::enableVertaxAttribPointer(GLuint index,
                                      GLsizei size,
                                      GLenum type,
                                      GLboolean normalized,
                                      GLsizei stride,
                                      GLuint offset)
{
    auto &gl = *QOpenGLContext::currentContext()->functions();

    gl.glEnableVertexAttribArray(index);
    gl.glVertexAttribPointer(index,
                             size,
                             type, normalized,
                             stride,
                             reinterpret_cast<void *>(offset));
}
