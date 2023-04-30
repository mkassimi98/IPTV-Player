#include "gstreamermanager.h"
#include <iostream>


GSTreamerManager::GSTreamerManager()
{

}


void GSTreamerManager::configureGst()
{
    try
    {
        std::cout << "The winId es " << winId << std::endl;
        // Initialize GStreamer
        gst_init(NULL, NULL);
        // Create the pipeline
        pipeline = gst_parse_launch("souphttpsrc location=http://shurtorotv.com:8080/Mosin/5Dv7D8TWHwRv/2753 ! decodebin name=decodebin ! videoscale ! videoconvert ! ximagesink name=videosink decodebin. ! queue ! audioconvert ! autoaudiosink", NULL);

        videosink = gst_bin_get_by_name(GST_BIN(pipeline), "videosink");
        // Get the bus
        bus = gst_pipeline_get_bus(GST_PIPELINE(pipeline));

        // Create the GMainLoop
        loop = g_main_loop_new(NULL, FALSE);
        // Push data to IPTVPlayer gui
        gst_video_overlay_set_window_handle(GST_VIDEO_OVERLAY(videosink), winId);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }    
}

void GSTreamerManager::startStream()
{
    std::cout << "Start button pressed!" << std::endl;
    configureGst();
    /* Inicia la pipeline */
    gst_element_set_state(pipeline, GST_STATE_PLAYING);
    // Start the GMainLoop
    g_main_loop_run(loop);
}

void GSTreamerManager::stopStream()
{
    std::cout << "Stop button pressed!" << std::endl;
    gst_element_set_state(pipeline, GST_STATE_NULL);
    // Stop the GMainLoop
    g_main_loop_quit(loop);

    // Cleanup
    g_main_loop_unref(loop);
    gst_object_unref(bus);
    gst_object_unref(pipeline);
}

void GSTreamerManager::setWinid(WId windowId)
{
    winId = windowId;
}

