# -------------------------------------------------
# Project created by QtCreator 2010-08-22T14:12:19
# -------------------------------------------------
QT += opengl xml
TARGET = final
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++14
CONFIG += c++14

unix:!macx {
    LIBS += -lGLU
}
macx {
    QMAKE_CFLAGS_X86_64 += -mmacosx-version-min=10.7
    QMAKE_CXXFLAGS_X86_64 = $$QMAKE_CFLAGS_X86_64
    CONFIG += c++11
}
win32 {
    DEFINES += GLEW_STATIC
    LIBS += -lopengl32 -lglu32
}

SOURCES += ui/mainwindow.cpp \
    main.cpp \
    glew-1.10.0/src/glew.c \
    ui/view.cpp \
    ui/viewformat.cpp \
    uniforms/uniformvariable.cpp \
    camera/orbitingcamera.cpp \
    uniforms/varsfile.cpp \
    lib/resourceloader.cpp \
    shapes/openglshape.cpp \
    gl/datatype/FBO.cpp \
    gl/datatype/VBO.cpp \
    gl/datatype/VBOAttribMarker.cpp \
    gl/datatype/VAO.cpp \
    gl/datatype/IBO.cpp \
    gl/textures/Texture.cpp \
    gl/textures/Texture2D.cpp \
    gl/textures/TextureParameters.cpp \
    gl/textures/TextureParametersBuilder.cpp \
    gl/textures/RenderBuffer.cpp \
    gl/textures/DepthBuffer.cpp \
    gl/GLDebug.cpp \
    lib/errorchecker.cpp \
    gl/shaders/CS123Shader.cpp \
    gl/shaders/Shader.cpp \
    lib/RGBA.cpp \
    shapes/trees/SimpleTree.cpp \
    shapes/trees/StringGenerator.cpp \
    shapes/trees/StringParser.cpp

HEADERS += ui/mainwindow.h \
    ui_mainwindow.h \
    glew-1.10.0/include/GL/glew.h \
    ui/view.h \
    ui/viewformat.h \
    uniforms/uniformvariable.h \
    lib/common.h \
    camera/orbitingcamera.h \
    camera/camera.h \
    uniforms/varsfile.h \
    shapes/cube.h \
    lib/resourceloader.h \
    shapes/sphere.h \
    shapes/openglshape.h \
    gl/datatype/FBO.h \
    gl/datatype/VBO.h \
    gl/datatype/VBOAttribMarker.h \
    gl/datatype/VAO.h \
    gl/datatype/IBO.h \
    gl/shaders/ShaderAttribLocations.h \
    gl/textures/Texture.h \
    gl/textures/Texture2D.h \
    gl/textures/TextureParameters.h \
    gl/textures/TextureParametersBuilder.h \
    gl/textures/RenderBuffer.h \
    gl/textures/DepthBuffer.h \
    gl/GLDebug.h \
    lib/errorchecker.h \
    gl/shaders/CS123Shader.h \
    gl/shaders/Shader.h \
    lib/CS123SceneData.h \
    lib/RGBA.h \
    shapes/trees/SimpleTree.h \
    shapes/trees/StringGenerator.h \
    shapes/trees/StringParser.h

FORMS += ui/mainwindow.ui
INCLUDEPATH += glm ui glew-1.10.0/include
DEPENDPATH += glm ui glew-1.10.0/include

DEFINES += _USE_MATH_DEFINES
DEFINES += TIXML_USE_STL
DEFINES += GLM_SWIZZLE GLM_FORCE_RADIANS
OTHER_FILES += shaders/shader.frag \
    shaders/shader.vert \
    shaders/ray.vert \
    shaders/ray.frag \
    shaders/skybox.vert \
    shaders/skybox.frag \
    shaders/normals.vert \
    shaders/normals.frag


# Don't add the -pg flag unless you know what you are doing. It makes QThreadPool freeze on Mac OS X
QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE += -O3
QMAKE_CXXFLAGS_WARN_ON -= -Wall
QMAKE_CXXFLAGS_WARN_ON += -Waddress -Warray-bounds -Wc++0x-compat -Wchar-subscripts -Wformat\
                          -Wmain -Wmissing-braces -Wparentheses -Wreorder -Wreturn-type \
                          -Wsequence-point -Wsign-compare -Wstrict-overflow=1 -Wswitch \
                          -Wtrigraphs -Wuninitialized -Wunused-label -Wunused-variable \
                          -Wvolatile-register-var -Wno-extra

QMAKE_CXXFLAGS += -g

# QMAKE_CXX_FLAGS_WARN_ON += -Wunknown-pragmas -Wunused-function -Wmain

macx {
    QMAKE_CXXFLAGS_WARN_ON -= -Warray-bounds -Wc++0x-compat
}

RESOURCES += \
    resources.qrc

DISTFILES += \
    shaders/normals/normals.vert \
    shaders/normals/normals.frag \
    shaders/normals/normals.gsh \
    shaders/normals/normalsArrow.gsh \
    shaders/normals/normalsArrow.frag \
    shaders/normals/normalsArrow.vert
