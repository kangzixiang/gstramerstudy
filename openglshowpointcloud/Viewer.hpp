
#define GL_GLEXT_PROTOTYPES 1

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/glext.h>

class CViewer 
{
public:
    CViewer();
    virtual ~CViewer();

    void viewerRun();

private:

    void init(void);
    static void draw_scene(void);
    static int model_finished(void);
    static void display(void);
    static int model_update(void);
    static void idle(void);
    static void deinit(void);

    static double angle;
    static double delta_angle;

    GLint glut_display;
    static GLubyte *pixels;
    static int offscreen;
    static GLuint fbo;
    static GLuint rbo_color;
    static GLuint rbo_depth;
    unsigned int height = 600;
    unsigned int width = 800;
    unsigned int time0;
};