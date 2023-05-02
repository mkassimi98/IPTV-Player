#include "gstreamermanager.h"
#include <iostream>
#include "gst/video/videooverlay.h"

GSTreamerManager::GSTreamerManager(QObject* parent)
{
    // Initialize GStreamer
    gst_init(NULL, NULL);
}


void GSTreamerManager::configureGst()
{
    try
    {
        // TODO: Set location as a private c-string and change it with setter
        std::cout << "The winId es " << winId << std::endl;
        // Create the pipeline
        pipeline = gst_parse_launch("souphttpsrc location=http://shurtorotv.com:8080/Mosin/5Dv7D8TWHwRv/2753 name=src ! "
                                    "decodebin name=decodebin ! "
                                    "videoscale ! "
                                    "videoconvert ! "
                                    "ximagesink name=videosink decodebin. ! "
                                    "queue ! "
                                    "audioconvert ! "
                                    "autoaudiosink", NULL);

        source = gst_bin_get_by_name(GST_BIN(pipeline), "src");
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

void GSTreamerManager::run()
{
    std::cout << "Start button pressed!" << std::endl;
    configureGst();
    /* Inicia la pipeline */
    gst_element_set_state(pipeline, GST_STATE_PLAYING);
    // Start the GMainLoop
    g_main_loop_run(loop);
}

void GSTreamerManager::stop()
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

void GSTreamerManager::setChannelSource(const std::string& url)
{
    std::cout << "[GSTreamerManager::setChannelSource] Hi! ";
    std::cout << "[GSTreamerManager::setChannelSource] Esta es la Uri de la señal: " << url;
    g_object_set(source, "location", url.c_str(), NULL);
}
