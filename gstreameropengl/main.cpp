#include <gst/gst.h>

#include <iostream>
using namespace std;

int main (int argc, char** argv) {
    
    /* Initialize GStreamer */
    gst_init (&argc, &argv);
    
    GstElement *pipeline, *appsrc, *gltestsrc, *glimagesink;

    GstBus *bus;
    GstMessage *msg;

    pipeline = gst_pipeline_new("test-pipeline");
    appsrc = gst_element_factory_make("appsrc", "appsrc");
    gltestsrc = gst_element_factory_make("gltestsrc", "gltestsrc");
    glimagesink = gst_element_factory_make("glimagesink", "glimagesink");

    if (!pipeline || !appsrc || !gltestsrc || !glimagesink)
    {
        g_log(G_LOG_DOMAIN, G_LOG_LEVEL_ERROR, "All elements need be created.");
    }

    g_object_set(gltestsrc, "pattern", "smpte", NULL);
    // Pipeline: appsrc 
    gst_bin_add_many(GST_BIN(pipeline), gltestsrc, glimagesink, NULL);

    if (gst_element_link_many(gltestsrc, glimagesink, NULL) != true)
    {
        return 0;
    }

    /* Start playing the pipeline */
    gst_element_set_state(pipeline, GST_STATE_PLAYING);

    /* Create a GLib Main Loop and set it to run */
    // GMainLoop *g_main_loop = g_main_loop_new(NULL, FALSE);
    // g_main_loop_run(g_main_loop);

     /* Wait until error or EOS */
    bus = gst_element_get_bus(pipeline);
    msg =
        gst_bus_timed_pop_filtered(bus, GST_CLOCK_TIME_NONE,
        GstMessageType(GST_MESSAGE_ERROR | GST_MESSAGE_EOS));

    /* See next tutorial for proper error message handling/parsing */
    if (GST_MESSAGE_TYPE (msg) == GST_MESSAGE_ERROR) {
        // g_error ("An error occurred! Re-run with the GST_DEBUG=*:WARN environment "
        //     "variable set for more details.");
        g_log(G_LOG_DOMAIN, G_LOG_LEVEL_ERROR, "An error occurred! Re-run with the GST_DEBUG=*:WARN environment variable set for more details.");
    }

    /* Free resources */
    gst_message_unref (msg);
    gst_object_unref (bus);
    gst_element_set_state (pipeline, GST_STATE_NULL);
    gst_object_unref (pipeline);

    return 0;
}