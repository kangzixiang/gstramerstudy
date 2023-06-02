

#define GL_GLEXT_PROTOTYPES 1

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/glext.h>

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>

#include "LidarGrabber.hpp"
#include "Viewer.hpp"

using namespace std;

void lidarGrabberTest(std::string pcapFile) {
    
    CLidarGrabber lg(pcapFile);

    std::vector<PointXYZI> vec;
    std::function<void (const std::vector<PointXYZI> &)> cloud_cb =
        [&vec](const std::vector<PointXYZI> &cloud) {vec = cloud;};
    
    lg.registerCallback(cloud_cb);


    if (!lg.isRunning())
    {
        lg.start();
        while (lg.isRunning())
        {
            
        }
        lg.stop();
    }
}

int main(int argc, char **argv)
{
    // lidarGrabberTest("");
    glutInit(&argc, argv);
    CViewer viewer;

    viewer.viewerRun();

    return 0;
}