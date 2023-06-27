
#include "Viewer.hpp"

#include <assert.h>
#include <functional>

int CViewer::offscreen = 0;
GLubyte* CViewer::pixels = NULL;
GLuint CViewer::fbo;
GLuint CViewer::rbo_color;
GLuint CViewer::rbo_depth;
double CViewer::angle = 0.0;
double CViewer::delta_angle = 1.0;

vector<tuple<float, float, float, float>> CViewer::m_vecData;
std::mutex CViewer::m_vecMutex;

CViewer::CViewer()
{

}

CViewer::~CViewer()
{

}

void CViewer::viewerRun()
{
    // glutInit(0, 0);
    if (offscreen) {
        /* TODO: if we use anything smaller than the window, it only renders a smaller version of things. */
        /*glutInitWindowSize(50, 50);*/
        glutInitWindowSize(width, height);
        glut_display = GLUT_SINGLE;
    } else {
        glutInitWindowSize(width, height);
        glutInitWindowPosition(100, 100);
        glut_display = GLUT_DOUBLE;
    }
    glutInitDisplayMode(glut_display | GLUT_RGBA | GLUT_DEPTH);
    glutCreateWindow("Test");
    if (offscreen) {
        /* TODO: if we hide the window the program blocks. */
        /*glutHideWindow();*/
    }
    init();

    glutDisplayFunc(CViewer::display);
    glutIdleFunc(CViewer::idle);
    atexit(CViewer::deinit);
    glutMainLoop();
}

void CViewer::setData(vector<tuple<float, float, float, float>> &vec)
{
    std::lock_guard<std::mutex> lock(m_vecMutex);
    vec.swap(m_vecData);
}

void CViewer::init(void)
{
    int glget;
    int argc = 0;
    char **argv = {};
    // glutInit(&argc, argv);
    if (offscreen) {
        /*  Framebuffer */
        glGenFramebuffers(1, &fbo);
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);

        /* Color renderbuffer. */
        glGenRenderbuffers(1, &rbo_color);
        glBindRenderbuffer(GL_RENDERBUFFER, rbo_color);
        /* Storage must be one of: */
        /* GL_RGBA4, GL_RGB565, GL_RGB5_A1, GL_DEPTH_COMPONENT16, GL_STENCIL_INDEX8. */
        glRenderbufferStorage(GL_RENDERBUFFER, GL_RGB565, width, height);
        glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, rbo_color);

        /* Depth renderbuffer. */
        glGenRenderbuffers(1, &rbo_depth);
        glBindRenderbuffer(GL_RENDERBUFFER, rbo_depth);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, width, height);
        glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rbo_depth);

        glReadBuffer(GL_COLOR_ATTACHMENT0);

        /* Sanity check. */
        assert(glCheckFramebufferStatus(GL_FRAMEBUFFER));
        glGetIntegerv(GL_MAX_RENDERBUFFER_SIZE, &glget);
        assert(width < (unsigned int)glget);
        assert(height < (unsigned int)glget);
    } else {
        glReadBuffer(GL_BACK);
        // glReadBuffer(GL_FRONT);
    }

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);

    time0 = glutGet(GLUT_ELAPSED_TIME);
}

void CViewer::draw_scene(void) {
    if (m_vecData.empty())
    {
        return ;
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
        // glRotatef(angle, 0.0f, 0.0f, -1.0f);
        glBegin(GL_QUADS);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f( 0.0f,  0.5f, 0.0f);
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3f(-0.5f, -0.5f, 0.0f);
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex3f( 0.5f, 0.0f, 0.5f);
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex3f( 0.0f, -0.5f, 0.5f);
        glEnd();
    }
    else
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
        // glRotatef(angle, 0.0f, 0.0f, -1.0f);
        glPointSize(4.0f);
        glBegin(GL_POINTS);
        
        std::lock_guard<std::mutex> lock(m_vecMutex);

        // for (int i = 0; i < m_vecData.size() & i != 10; i++)
        // {
        //     float x = 0.0, y = 0.0, z = 0.0, in =0.0;
        //     x = std::get<0>(m_vecData[i]);
        //     y = std::get<1>(m_vecData[i]);
        //     z = std::get<2>(m_vecData[i]);
        //     in = std::get<3>(m_vecData[i]);
        //     glColor3f(1.0f, 0.0f, 0.0f);
        //     glVertex3f(x, y, z);
        // }
        for (int i = 0; i < 10; i++)
        {
            glColor3f(1.0f, 0.0f, 0.0f);
            GLfloat x = i, y = i + 1, z = i + 2;
            glVertex3f(x, y, z);
        }
        vector<tuple<float, float, float, float>>().swap(m_vecData);
        glEnd();
    }
}

int CViewer::model_finished(void)
{
    return 0;
}

void CViewer::display(void)
{
    draw_scene();
    if (offscreen) {
        glFlush();
    } else {
        glutSwapBuffers();
    }
    if (model_finished())
        exit(EXIT_SUCCESS);
}

int CViewer::model_update(void)
{
    angle += delta_angle;
    return 0;
}

void CViewer::idle(void)
{
    while (model_update());
    glutPostRedisplay();
}

void CViewer::deinit(void)
{
    free(pixels);
    if (offscreen) {
        glDeleteFramebuffers(1, &fbo);
        glDeleteRenderbuffers(1, &rbo_color);
        glDeleteRenderbuffers(1, &rbo_depth);
    }
}


