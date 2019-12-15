#include "view.h"

#include "viewformat.h"
#include <QApplication>
#include <QKeyEvent>
#include <iostream>

#include <QMouseEvent>
#include <sstream>

#include "shapes/sphere.h"
#include "shapes/cube.h"
#include "camera/orbitingcamera.h"
#include "lib/resourceloader.h"
#include "uniforms/varsfile.h"
#include "gl/shaders/ShaderAttribLocations.h"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "gl/textures/Texture2D.h"

#include "shapes/trees/SimpleTree.h"

UniformVariable *View::s_skybox = NULL;
UniformVariable *View::s_projection = NULL;
UniformVariable *View::s_model = NULL;
UniformVariable *View::s_view = NULL;
UniformVariable *View::s_mvp = NULL;
UniformVariable *View::s_time = NULL;
UniformVariable *View::s_size = NULL;
UniformVariable *View::s_mouse = NULL;
std::vector<UniformVariable*> *View::s_staticVars = NULL;

View::View(QWidget *parent) : QGLWidget(ViewFormat(), parent),
    m_time(), m_timer(), m_captureMouse(false), m_isDragging(false),
    m_sphere(nullptr), m_cube(nullptr), m_quad(nullptr), skybox_cube(nullptr),
    m_phongShader(nullptr)
{
//    camera = new OrbitingCamera();
//    QObject::connect(camera, SIGNAL(viewChanged(glm::mat4)), this, SLOT(viewChanged(glm::mat4)));
//    QObject::connect(camera, SIGNAL(projectionChanged(glm::mat4)), this, SLOT(projectionChanged(glm::mat4)));
//    QObject::connect(camera, SIGNAL(modelviewProjectionChanged(glm::mat4)), this, SLOT(modelviewProjectionChanged(glm::mat4)));
    activeUniforms = new QList<const UniformVariable *>();
    // View needs all mouse move events, not just mouse drag events
    mouseDown = false;

    setMouseTracking(true);

    // Hide the cursor
    if (m_captureMouse) {
        QApplication::setOverrideCursor(Qt::BlankCursor);
    }

    // View needs keyboard focus
    setFocusPolicy(Qt::StrongFocus);

    // The update loop is implemented using a timer
    connect(&m_timer, SIGNAL(timeout()), this, SLOT(tick()));

    s_staticVars = new std::vector<UniformVariable*>();
}

View::~View()
{
    delete camera;
    delete activeUniforms;
    foreach (const UniformVariable *v, permUniforms) {
        delete v;
    }
}

void View::loadPhongShader() {
    std::string vertexSource = ResourceLoader::loadResourceFileToString(":/shaders/default.vert");
    std::string fragmentSource = ResourceLoader::loadResourceFileToString(":/shaders/default.frag");
    m_phongShader = std::make_unique<CS123Shader>(vertexSource, fragmentSource);
}

void View::loadRayShader(){
    std::string vertexSource = ResourceLoader::loadResourceFileToString(":/shaders/ray.vert");
    std::string fragmentSource = ResourceLoader::loadResourceFileToString(":/shaders/ray.frag");
    m_rayShader = std::make_unique<CS123Shader>(vertexSource, fragmentSource);
}

void View::initializeSceneMaterial() {
    m_material.clear();
    m_material.cAmbient.r = 0.2f;
    m_material.cAmbient.g = 0.1f;
    m_material.cAmbient.b = 0.0f;
    m_material.cDiffuse.r = 0.2f;
    m_material.cDiffuse.g = 0.1f;
    m_material.cDiffuse.b = 0.0f;
    m_material.cSpecular.r = m_material.cSpecular.g = m_material.cSpecular.b = 0.5;
    m_material.shininess = 64;

    glEnable(GL_CULL_FACE);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void View::initializeSceneLight() {
    // Use a white directional light from the upper left corner
    memset(&m_light, 0, sizeof(m_light));
    m_light.type = LightType::LIGHT_DIRECTIONAL;
    m_light.dir = m_lightDirection;
    m_light.color.r = m_light.color.g = m_light.color.b = 1;
    m_light.id = 0;
}

bool View::saveUniforms(QString path)
{
    QList<const UniformVariable *> toSave;
    foreach (const UniformVariable *v, *activeUniforms) {
        toSave += v;
    }
    foreach (const UniformVariable *v, permUniforms) {
        toSave += v;
    }

    return VarsFile::save(path, &toSave);
}

bool View::loadUniforms(QString path)
{
    QList<const UniformVariable*> fromFile;

    foreach (const UniformVariable *v, permUniforms) {
        delete v;
    }
    permUniforms.clear();

    if (!VarsFile::load(path, &fromFile, context()->contextHandle())) return false;

    bool match;
    foreach (const UniformVariable *v, fromFile) {
        match = false;
        foreach (const UniformVariable *u, *activeUniforms) {
            if (!v->getName().compare(u->getName()) && v->getType() == u->getType()) {
                UniformVariable *utemp = const_cast<UniformVariable *>(u);
                utemp->setPermanent(v->getPermanent());
                emit(changeUniform(u, v->toString()));
                match = true;
            }
        }

        if (!match && v->getPermanent()) {
            permUniforms += v;
        } else {
            delete v;
        }
    }
    return true;
}

void View::initializeScene(){
    camera = new OrbitingCamera();
    QObject::connect(camera, SIGNAL(viewChanged(glm::mat4)), this, SLOT(viewChanged(glm::mat4)));
    QObject::connect(camera, SIGNAL(projectionChanged(glm::mat4)), this, SLOT(projectionChanged(glm::mat4)));
    QObject::connect(camera, SIGNAL(modelviewProjectionChanged(glm::mat4)), this, SLOT(modelviewProjectionChanged(glm::mat4)));

    initializeSceneLight();
    initializeSceneMaterial();
    loadPhongShader();
    loadRayShader();
//    activeUniforms = new QList<const UniformVariable *>();
//    current_shader = NULL;
//    // View needs all mouse move events, not just mouse drag events
//    mouseDown = false;

//    setMouseTracking(true);

//    // Hide the cursor
//    if (m_captureMouse) {
//        QApplication::setOverrideCursor(Qt::BlankCursor);
//    }

//    // View needs keyboard focus
//    setFocusPolicy(Qt::StrongFocus);

//    // The update loop is implemented using a timer
//    connect(&m_timer, SIGNAL(timeout()), this, SLOT(tick()));

//    s_staticVars = new std::vector<UniformVariable*>();
}

void View::initializeGL() {
    //initialize glew
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        /* Problem: glewInit failed, something is seriously wrong. */
        std::cerr << "Something is very wrong, glew initialization failed." << std::endl;
    }
    std::cout << "Using GLEW " <<  glewGetString( GLEW_VERSION ) << std::endl;
    initializeScene();
    // Start a timer that will try to get 60 frames per second (the actual
    // frame rate depends on the operating system and other running programs)
    m_time.start();
    m_timer.start(1000 / 60);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_CUBE_MAP);

    glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_BLEND);
    glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    skybox_shader = ResourceLoader::newShaderProgram(context(), ":/shaders/skybox.vert", ":/shaders/skybox.frag");

    s_skybox = new UniformVariable(this->context()->contextHandle());
    s_skybox->setName("skybox");
    s_skybox->setType(UniformVariable::TYPE_TEXCUBE);
    //top, bottom, left, right, front, back
    s_skybox->parse(":/skybox/posy.jpg,:/skybox/negy.jpg,:/skybox/negx.jpg,:/skybox/posx.jpg,:/skybox/negz.jpg,:/skybox/posz.jpg");

    s_model = new UniformVariable(this->context()->contextHandle());
    s_model->setName("model");
    s_model->setType(UniformVariable::TYPE_MAT4);
    s_model->parse("1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1");

    s_projection = new UniformVariable(this->context()->contextHandle());
    s_projection->setName("projection");
    s_projection->setType(UniformVariable::TYPE_MAT4);

    s_view = new UniformVariable(this->context()->contextHandle());
    s_view->setName("view");
    s_view->setType(UniformVariable::TYPE_MAT4);

    s_mvp = new UniformVariable(this->context()->contextHandle());
    s_mvp->setName("mvp");
    s_mvp->setType(UniformVariable::TYPE_MAT4);

    s_time = new UniformVariable(this->context()->contextHandle());
    s_time->setName("time");
    s_time->setType(UniformVariable::TYPE_TIME);

    s_size = new UniformVariable(this->context()->contextHandle());
    s_size->setName("size");
    s_size->setType(UniformVariable::TYPE_FLOAT2);

    s_mouse = new UniformVariable(this->context()->contextHandle());
    s_mouse->setName("mouse");
    s_mouse->setType(UniformVariable::TYPE_FLOAT3);

    s_staticVars->push_back(s_skybox);
    s_staticVars->push_back(s_model);
    s_staticVars->push_back(s_projection);
    s_staticVars->push_back(s_view);
    s_staticVars->push_back(s_mvp);
    s_staticVars->push_back(s_time);
    s_staticVars->push_back(s_size);
    s_staticVars->push_back(s_mouse);

    std::vector<GLfloat> sphereData = SPHERE_VERTEX_POSITIONS;
    m_sphere = std::make_unique<OpenGLShape>();
    m_sphere->setVertexData(&sphereData[0], sphereData.size(), VBO::GEOMETRY_LAYOUT::LAYOUT_TRIANGLES, NUM_SPHERE_VERTICES);
    m_sphere->setAttribute(ShaderAttrib::POSITION, 3, 0, VBOAttribMarker::DATA_TYPE::FLOAT, false);
    m_sphere->setAttribute(ShaderAttrib::NORMAL, 3, 0, VBOAttribMarker::DATA_TYPE::FLOAT, false);
    m_sphere->buildVAO();

    std::vector<GLfloat> cubeData = CUBE_DATA_POSITIONS;
    skybox_cube = std::make_unique<OpenGLShape>();
    skybox_cube->setVertexData(&cubeData[0], cubeData.size(), VBO::GEOMETRY_LAYOUT::LAYOUT_TRIANGLES, NUM_CUBE_VERTICES);
    skybox_cube->setAttribute(ShaderAttrib::POSITION, 3, 0, VBOAttribMarker::DATA_TYPE::FLOAT, false);
    skybox_cube->setAttribute(ShaderAttrib::NORMAL, 3, 3*sizeof(GLfloat), VBOAttribMarker::DATA_TYPE::FLOAT, false);
    skybox_cube->buildVAO();

    std::vector<GLfloat> quadData = {-1, 1, 0, 0, 1,
                                     -1, -1, 0, 0, 0,
                                     1, 1, 0, 1, 1,
                                     1, -1, 0, 1, 0};
    m_quad = std::make_unique<OpenGLShape>();
    m_quad->setVertexData(&quadData[0], quadData.size(), VBO::GEOMETRY_LAYOUT::LAYOUT_TRIANGLE_STRIP, 4);
    m_quad->setAttribute(ShaderAttrib::POSITION, 3, 0, VBOAttribMarker::DATA_TYPE::FLOAT, false);
    m_quad->setAttribute(ShaderAttrib::TEXCOORD0, 2, 3*sizeof(GLfloat), VBOAttribMarker::DATA_TYPE::FLOAT, false);
    m_quad->buildVAO();
    camera->mouseScrolled(0);
    camera->updateMats();
    update();
}

void View::updateMatrices(){
    m_phongShader->setUniform("p", camera->getProjectionMatrix());
    m_phongShader->setUniform("v", camera->getModelviewMatrix());
    m_phongShader->setUniform("m", glm::mat4(1.0f));
}

void View::buildTrees(){
    SimpleTree tree(glm::vec3(0,-2,0), 2);
    tree.buildAndSet();
    tree.draw();
    SimpleTree tree2(glm::vec3(1,-2.5,0), 2);
    tree2.buildAndSet();
    tree2.draw();
    SimpleTree tree3(glm::vec3(-1.3,-2.5,-2), 2);
    tree3.buildAndSet();
    tree3.draw();
}

void View::paintGL() {
    m_phongShader->bind();
    firstPass();
    secondPass();

    m_rayShader->bind();
    glViewport(0, 0, m_width, m_height);
    //fetch texture from occlusion FBO
    glActiveTexture(GL_TEXTURE1);
    m_occludeFBO->getColorAttachment(0).bind();
    GLint ocLocation = glGetUniformLocation(m_rayShader->getID(), "firstPass");
    glUniform1i(ocLocation, 1);
    //fetch texture from phong FBO
    glActiveTexture(GL_TEXTURE2);
    m_phongFBO->getColorAttachment(0).bind();
    GLint newLocation = glGetUniformLocation(m_rayShader->getID(), "secondPass");
    glUniform1i(newLocation, 2);
    //draw full screen quad
    m_quad->draw();

}

void View::firstPass(){
    m_occludeFBO->bind();
    glViewport(0, 0, m_width, m_height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    clearLights();
    setLights(camera->getModelviewMatrix());
    CS123SceneMaterial black;
    black.clear();
    black.cAmbient.r = 0.0f;
    black.cAmbient.g = 0.0f;
    black.cAmbient.b = 0.0f;
    black.cDiffuse.r = 0.0f;
    black.cDiffuse.g = 0.0f;
    black.cDiffuse.b = 0.0f;
    black.cSpecular.r = black.cSpecular.g = black.cSpecular.b = 0;
    black.cEmissive.r = 0.0f;
    black.cEmissive.g = 0.0f;
    black.cEmissive.b = 0.0f;
    black.shininess = 0;
    m_phongShader->setUniform("useArrowOffsets", false);
    m_phongShader->applyMaterial(black);
    updateMatrices();
    buildTrees();
    setSunUniforms();
    renderSun();
    m_occludeFBO->unbind();
}

void View::secondPass(){
    m_phongFBO->bind();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, m_width, m_height);
    clearLights();
    setLights(camera->getModelviewMatrix());
    m_phongShader->setUniform("useArrowOffsets", false);
    m_phongShader->applyMaterial(m_material);
    updateMatrices();
    buildTrees();
    setSunUniforms();
    renderSun();

    m_phongShader->unbind();

    skybox_shader->bind();
    glViewport(0, 0, m_width, m_height);

    projectionChanged(camera->getProjectionMatrix());
    viewChanged(camera->getModelviewMatrix());
    s_skybox->setValue(skybox_shader);
    s_projection->setValue(skybox_shader);
    s_view->setValue(skybox_shader);
    glCullFace(GL_FRONT);
    skybox_cube->draw();
    glCullFace(GL_BACK);
    skybox_shader->release();
    m_phongFBO->unbind();
}

void View::setSunUniforms(){
    glm::mat4 t = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, 10.0f));
    glm::mat4 s = glm::scale(glm::vec3(0.8f, 0.8f, 0.8f));
    glm::mat4 m = t*s;
    m_phongShader->setUniform("m", m);
}

void View::renderSun(){
    CS123SceneMaterial sun_mat;
    sun_mat.clear();
    sun_mat.cAmbient.r = 1.0f;
    sun_mat.cAmbient.g = 1.0f;
    sun_mat.cAmbient.b = 1.0f;
    sun_mat.cDiffuse.r = 1.0f;
    sun_mat.cDiffuse.g = 1.0f;
    sun_mat.cDiffuse.b = 1.0f;
    sun_mat.cSpecular.r = sun_mat.cSpecular.g = sun_mat.cSpecular.b = 0;
    sun_mat.shininess = 1000;
    m_phongShader->applyMaterial(sun_mat);
    m_sphere->draw();
}

void View::resizeGL(int w, int h) {
    float ratio = static_cast<QGuiApplication *>(QCoreApplication::instance())->devicePixelRatio();
    w = static_cast<int>(w / ratio);
    h = static_cast<int>(h / ratio);
    m_width = w;
    m_height = h;
    m_phongFBO = std::make_unique<FBO>(1, FBO::DEPTH_STENCIL_ATTACHMENT::DEPTH_ONLY, m_width, m_height, TextureParameters::WRAP_METHOD::CLAMP_TO_EDGE);
    m_occludeFBO = std::make_unique<FBO>(1, FBO::DEPTH_STENCIL_ATTACHMENT::DEPTH_ONLY, m_width, m_height, TextureParameters::WRAP_METHOD::CLAMP_TO_EDGE);

    glViewport(0, 0, w, h);
    s_size->parse(QString("%1,%2").arg(QString::number(w), QString::number(h)));
    camera->setAspectRatio(((float) w) / ((float) h));
    updateMatrices();
}

void View::uniformDeleted(const UniformVariable *uniform)
{
    foreach (UniformVariable *sv, *s_staticVars) {
        if (uniform == sv) return;
    }

    foreach (const UniformVariable *v, *activeUniforms) {
        if (uniform == v)
            delete v;
    }
    activeUniforms->removeAll(uniform);
}

void View::uniformAdded(const UniformVariable *uniform)
{
    activeUniforms->append(uniform);
}

void View::viewChanged(const glm::mat4 &modelview)
{
    std::stringstream s;
    const float *data = glm::value_ptr(glm::transpose(modelview));
    for (int i = 0; i < 16; i++) {
        s << data[i];
        if (i < 15)
            s << ",";
    }
    s_view->parse(QString::fromStdString(s.str()));

}

void View::projectionChanged(const glm::mat4 &projection)
{
    std::stringstream s;
    const float *data = glm::value_ptr(glm::transpose(projection));
    for (int i = 0; i < 16; i++) {
        s << data[i];
        if (i < 15)
            s << ",";
    }
    s_projection->parse(QString::fromStdString(s.str()));


}

void View::modelviewProjectionChanged(const glm::mat4 &modelviewProjection)
{
    std::stringstream s;
    const float *data = glm::value_ptr(glm::transpose(modelviewProjection * model));
    for (int i = 0; i < 16; i++) {
        s << data[i];
        if (i < 15)
            s << ",";
    }
    s_mvp->parse(QString::fromStdString(s.str()));


}

void View::modelChanged(const glm::mat4 &modelview)
{
    std::stringstream s;
    const float *data = glm::value_ptr(glm::transpose(modelview));
    for (int i = 0; i < 16; i++) {
        s << data[i];
        if (i < 15)
            s << ",";
    }
    s_model->parse(QString::fromStdString(s.str()));


}

void View::clearLights() {
    for (int i = 0; i < 10; i++) {
        std::ostringstream os;
        os << i;
        std::string indexString = "[" + os.str() + "]"; // e.g. [0], [1], etc.
        m_phongShader->setUniform("lightColors" + indexString, glm::vec3(0.0f, 0.0f, 0.0f));
    }
}

void View::setLights(const glm::mat4 viewMatrix) {
    m_light.dir = glm::inverse(viewMatrix) * m_lightDirection;

    clearLights();
    m_phongShader->setLight(m_light);
}

void View::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::RightButton) {
        camera->mouseDown(event->x(), event->y());
        m_isDragging = true;
    }
    camera->mouseDown(event->x(), event->y());
    mouseDown = true;
    s_mouse->parse(QString("%1,%2,%3").arg(
                       QString::number(event->x()),
                       QString::number(event->y()),
                       QString::number(mouseDown)));

}

void View::wheelEvent(QWheelEvent *event)
{
    camera->mouseScrolled(event->delta());
    camera->updateMats();
    updateMatrices();

}

void View::mouseMoveEvent(QMouseEvent *event) {
    // This starter code implements mouse capture, which gives the change in
    // mouse position since the last mouse movement. The mouse needs to be
    // recentered after every movement because it might otherwise run into
    // the edge of the screen, which would stop the user from moving further
    // in that direction. Note that it is important to check that deltaX and
    // deltaY are not zero before recentering the mouse, otherwise there will
    // be an infinite loop of mouse move events.
    if (m_isDragging) {
        camera->mouseDragged(event->x(), event->y());
        camera->updateMats();
        updateMatrices();
    }
    if(m_captureMouse) {
        int deltaX = event->x() - width() / 2;
        int deltaY = event->y() - height() / 2;
        if (!deltaX && !deltaY) return;
        QCursor::setPos(mapToGlobal(QPoint(width() / 2, height() / 2)));

        // TODO: Handle mouse movements here
        if (event->buttons() & Qt::LeftButton) {
            camera->mouseDragged(event->x(), event->y());
        }
        s_mouse->parse(QString("%1,%2,%3").arg(
                           QString::number(event->x()),
                           QString::number(event->y()),
                           QString::number(mouseDown)));
    }

}

void View::mouseReleaseEvent(QMouseEvent *event) {
    if (m_isDragging && event->button() == Qt::RightButton) {
        camera->mouseUp(event->x(), event->y());
        m_isDragging = false;
    }
    mouseDown = false;
    s_mouse->parse(QString("%1,%2,%3").arg(
                       QString::number(event->x()),
                       QString::number(event->y()),
                       QString::number(mouseDown)));
     updateMatrices();

}

void View::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Escape) QApplication::quit();
}

void View::keyReleaseEvent(QKeyEvent *event) {

}

void View::tick() {
    // Get the number of seconds since the last tick (variable update rate)
    float seconds = m_time.restart() * 0.001f;

    // TODO: Implement the demo update here

    // Flag this view for repainting (Qt will call paintGL() soon after)
    updateMatrices();
    update();
}
