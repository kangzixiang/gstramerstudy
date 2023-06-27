
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/glext.h>

class CPointViewer
{
public:
    CPointViewer();
    virtual ~CPointViewer();

    void viewerRun();
private:
    void init(void);

    void draw_scene(void);
    int model_finished(void);
    void display(void);
    int model_update(void);
    void idle(void);
    void deinit(void);


};