

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
    CViewer viewer;
    std::thread *ThreadHandle = new std::thread(&CViewer::viewerRun, &viewer);
    //viewer.viewerRun();

    if (!lg.isRunning())
    {
        lg.start();
        while (lg.isRunning())
        {
            if (!vec.empty())
            {   vector<tuple<float, float, float, float>> vecDta;
                for (int i = 0; i < vec.size(); i++)
                {
                    tuple<float, float, float, float> t(vec[i].x, vec[i].y, vec[i].z, vec[i].i);
                    vecDta.push_back(t);
                }
                vec.clear();
                viewer.setData(vecDta);
            }
        }
        lg.stop();
        if (nullptr != ThreadHandle)
        {
            ThreadHandle->join();
            delete ThreadHandle;
            ThreadHandle = nullptr;
        }
    }
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    lidarGrabberTest("/tmp/sensor/lidar/test.pcap");

    return 0;
}