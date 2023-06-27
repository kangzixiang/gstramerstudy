
#define GL_GLEXT_PROTOTYPES 1

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/glext.h>

#include <vector>
#include <tuple>
#include <mutex>

using namespace std;

class CViewer 
{
public:
    CViewer();
    virtual ~CViewer();

    void viewerRun();
    void setData(vector<tuple<float, float, float, float>> &vec);

private:

    void init(void);
    static void draw_scene(void);
    static int model_finished(void);
    static void display(void);
    static int model_update(void);
    static void idle(void);
    static void deinit(void);

    static vector<tuple<float, float, float, float>> m_vecData;
    static std::mutex m_vecMutex;

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