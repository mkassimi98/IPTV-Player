#ifndef GSTREAMERMANAGER_H
#define GSTREAMERMANAGER_H
#include "qwindowdefs.h"
#include <gst/gst.h>
#include "gst/video/videooverlay.h"


class GSTreamerManager
{
public:
    GSTreamerManager();
    ~GSTreamerManager() {stopStream();};
    void startStream();
    void stopStream();
    void setWinid(WId windowId);
private:
    void configureGst();
    GstElement *pipeline,
                *videosink;
    GstBus *bus;
    GMainLoop *loop;
    WId winId;
};

#endif // GSTREAMERMANAGER_H
