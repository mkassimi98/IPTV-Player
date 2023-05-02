#ifndef GSTREAMERMANAGER_H
#define GSTREAMERMANAGER_H
#include "qwindowdefs.h"
#include <gst/gst.h>
#include <QThread>


class GSTreamerManager : public QThread
{
    Q_OBJECT
public:
    GSTreamerManager(QObject* parent = nullptr);
    ~GSTreamerManager() {stop(); gst_deinit();};
    void stop();
    void setWinid(WId windowId);
    void configureGst();
    void setChannelSource(const std::string& url);

protected:
    void run() override;
private:
    GstElement  *pipeline,
                *videosink,
                *source;
    GstBus      *bus;
    GMainLoop   *loop;
    WId         winId;
};

#endif // GSTREAMERMANAGER_H
