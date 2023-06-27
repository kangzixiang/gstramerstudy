
#include "PointViewer.hpp"

CPointViewer::CPointViewer()
{
    int argc;
    char **argv;
    glutInit(&argc, argv);
}

CPointViewer::~CPointViewer()
{
}

void CPointViewer::viewerRun()
{
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

    glutCreateWindow("Test");

    init();

    void (CPointViewer::*display)() = &CPointViewer::display;
    void (CPointViewer::*idle)() = &CPointViewer::idle;
    void (CPointViewer::*deinit)() = &CPointViewer::deinit;
    
    // glutDisplayFunc(display);
    // glutIdleFunc(idle);
    // atexit(deinit);
    glutMainLoop();
}

void CPointViewer::init(void)
{
    glReadBuffer(GL_BACK);

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    glViewport(0, 0, 800, 600);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
}

void CPointViewer::draw_scene(void)
{

}

int CPointViewer::model_finished(void)
{
    return 0;
}

void CPointViewer::display(void)
{
}

int CPointViewer::model_update(void)
{
    return 0;
}

void CPointViewer::idle(void)
{
}

void CPointViewer::deinit(void)
{
}
