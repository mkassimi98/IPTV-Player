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
    void setWinid(WId *windowId);
    void configureGst();
    void setChannelSource(const QString url);

protected:
    void run() override;
private:
    GstElement  *pipeline,
                *videosink;
    GstBus      *bus;
//    GMainLoop   *loop;
    GMutex      _pipeline_mutex;
    WId         *winId;
    QString     _location;
    void refresh();
};

#endif // GSTREAMERMANAGER_H
