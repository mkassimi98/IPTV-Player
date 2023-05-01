#ifndef IPTVPLAYER_H
#define IPTVPLAYER_H

#include <QMainWindow>
#include "../gstreamer/gstreamermanager.h"
#include "channelselectiondialog.h"
#include "qlabel.h"
#include <QFileDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class IPTVPlayer; }
QT_END_NAMESPACE

class IPTVPlayer : public QMainWindow, public GSTreamerManager
{
    Q_OBJECT

public:
    IPTVPlayer(QWidget *parent = nullptr);
    ~IPTVPlayer();
    // Getters
    QLabel* getVideoDisplay() const;
    bool isPlaying()
    {
        return playing;
    }
    // Setters
    void setPlayStatus(bool status)
    {
        playing = status;
    }

private:
    Ui::IPTVPlayer *ui;
    GSTreamerManager gstmanager;
    bool playing = false;
    WId lbId;
    QString filePath;
    ChannelSelectionDialog dialog;
    ChannelSelectionDialog *channel;


private slots:
    void runStreamPressed();
    void stopStreamPressed();
    void selectPlaylistFile();
    void showChannelSelectionDialog();
    void printUri(QString uri);
};
#endif // IPTVPLAYER_H
