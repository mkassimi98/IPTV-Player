#include "gstreamermanager.h"
#include <iostream>
#include "gst/video/videooverlay.h"

#define PIPELINE_LOCK()    g_mutex_lock(&_pipeline_mutex)
#define PIPELINE_UNLOCK()  g_mutex_unlock(&_pipeline_mutex)

GSTreamerManager::GSTreamerManager(QObject* parent) : QThread(parent)
{
    // Initialize GStreamer
    gst_init(NULL, NULL);
    g_mutex_init(&_pipeline_mutex);
}


void GSTreamerManager::configureGst()
{
    try
    {
        // TODO: Set location as a private c-string and change it with setter
        std::cout << "The winId is " << winId << std::endl;
        // Create the pipeline
        const auto pipe = QString("souphttpsrc location=%1 name=src ! "
                                  "decodebin name=decodebin ! "
                                  "videoscale ! "
                                  "videoconvert ! "
                                  "ximagesink name=videosink decodebin. ! "
                                  "queue ! "
                                  "audioconvert ! "
                                  "autoaudiosink")
                                  .arg(_location);

        pipeline = gst_parse_launch(pipe.toStdString().c_str(), NULL);

        videosink = gst_bin_get_by_name(GST_BIN(pipeline), "videosink");
        // Get the bus
        bus = gst_pipeline_get_bus(GST_PIPELINE(pipeline));

        // Push data to IPTVPlayer gui
        gst_video_overlay_set_window_handle(GST_VIDEO_OVERLAY(videosink), *winId);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }    
}



void GSTreamerManager::stop()
{
    std::cout << "Stop button pressed!" << std::endl;
    gst_element_set_state(pipeline, GST_STATE_NULL);

    // Cleanup
    gst_object_unref(bus);
    gst_object_unref(videosink);
    gst_object_unref(pipeline);
}

void GSTreamerManager::setWinid(WId *windowId)
{
    winId = windowId;
}

void GSTreamerManager::setChannelSource(const QString url)
{
    PIPELINE_LOCK();
    std::cout << "[GSTreamerManager::setChannelSource] This is the Uri: " << url.toStdString() << std::endl;
    _location = url;
    refresh();
    PIPELINE_UNLOCK();
}

void GSTreamerManager::run()
{
    std::cout << "Start button pressed!" << std::endl;
    configureGst();
    /* Inicia la pipeline */
    gst_element_set_state(pipeline, GST_STATE_PLAYING);
}

void GSTreamerManager::refresh()
{
    std::cout << "[GSTreamerManager::refresh]" << std::endl;
    gst_element_set_state(pipeline, GST_STATE_NULL);
    gst_object_unref(bus);
    gst_object_unref(pipeline);

    /* Inicia la pipeline */
    configureGst();
    gst_element_set_state(pipeline, GST_STATE_PLAYING);
}
