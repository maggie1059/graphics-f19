#ifndef VIEW_H
#define VIEW_H
#include "shapes/openglshape.h"
#include "camera/camera.h"
#include "uniforms/uniformvariable.h"

#include <qgl.h>
#include <QGLWidget>

#include <QTime>
#include <QTimer>
#include "glm/glm.hpp"            // glm::vec*, mat*, and basic glm functions
#include "glm/gtx/transform.hpp"  // glm::translate, scale, rotate
#include "glm/gtc/type_ptr.hpp"   // glm::value_ptr

#include <memory>  // std::unique_ptr

#include "gl/datatype/FBO.h"
#include "lib/CS123SceneData.h"
#include "gl/shaders/CS123Shader.h"
#include "GL/glew.h"

class Cube;

class QGLShaderProgram;

#define colorToArgs(floatArray) floatArray[0], floatArray[1], floatArray[2], floatArray[3]
enum AnimType { ANIM_NONE, ANIM_MOVE, ANIM_SCALE, ANIM_MOVE_AND_SCALE, ANIM_ROTATE, ANIM_ROTATE_2};
enum WireframeType { WIREFRAME_NORMAL, WIREFRAME_VERT };


class View : public QGLWidget {
    Q_OBJECT

public:
    View(QWidget *parent);
    ~View();

signals:
    void addUniform(UniformVariable::Type type, const QString &name, bool editable = true, int size = 1);
    void addUniform(UniformVariable *uniform, bool editable = true);
    void changeUniform(const UniformVariable *uniform, const QString &newVal);
    void changeUniform(const QString &name, const QString &newVal);


public slots:
    void uniformDeleted(const UniformVariable *uniform);
    void uniformAdded(const UniformVariable *uniform);
    void viewChanged(const glm::mat4 &modelview);
    void projectionChanged(const glm::mat4 &projection);
    void modelviewProjectionChanged(const glm::mat4 &modelviewProjection);
    void modelChanged(const glm::mat4 &modelview);

protected:
    QTime m_time;
    QTimer m_timer;
    bool m_captureMouse;

    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);

    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

private slots:
    void tick();

private:
    bool saveUniforms(QString path);
    bool loadUniforms(QString path);
    void initializeSceneLight();
    void initializeSceneMaterial();
    void updateMatrices();
    void initializeScene();
    void renderSun();
    void setSunUniforms();
    void buildTrees();
    void setLights(const glm::mat4 viewMatrix);
    void clearLights();
    void loadRayShader();
    void loadPhongShader();
    void firstPass();
    void secondPass();

    static UniformVariable* s_skybox;
    static UniformVariable* s_model;
    static UniformVariable* s_view;
    static UniformVariable* s_projection;
    static UniformVariable* s_mvp;
    static UniformVariable* s_mouse;
    static UniformVariable* s_time;
    static UniformVariable* s_size;
    static std::vector<UniformVariable*> *s_staticVars;

    std::unique_ptr<CS123::GL::CS123Shader> m_phongShader;
    std::unique_ptr<CS123::GL::CS123Shader> m_rayShader;
    QGLShaderProgram *skybox_shader;

    std::unique_ptr<FBO> m_occludeFBO;
    std::unique_ptr<FBO> m_phongFBO;

    QList<const UniformVariable*> *activeUniforms;
    QList<const UniformVariable*> permUniforms;

    std::unique_ptr<OpenGLShape> m_sphere;
    std::unique_ptr<OpenGLShape> m_cube;
    std::unique_ptr<OpenGLShape> m_quad;
    std::unique_ptr<OpenGLShape> skybox_cube;

    glm::vec4 m_lightDirection = glm::normalize(glm::vec4(1.f, -1.f, -1.f, 0.f));
    CS123SceneLightData m_light;
    CS123SceneMaterial m_material;

    Camera *camera;

    glm::mat4 model;

    int m_width;
    int m_height;

    bool mouseDown;
    bool m_isDragging;
};

#endif // VIEW_H
