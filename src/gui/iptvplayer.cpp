#include "iptvplayer.h"
#include "./ui_iptvplayer.h"
#include <iostream>

IPTVPlayer::IPTVPlayer(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::IPTVPlayer)
{
    ui->setupUi(this);
    connect(ui->pb_play, &QPushButton::clicked, this, &IPTVPlayer::runStreamPressed);
    connect(ui->pb_stop, &QPushButton::clicked, this, &IPTVPlayer::stopStreamPressed);
}

IPTVPlayer::~IPTVPlayer()
{
    delete ui;
}

void IPTVPlayer::runStreamPressed()
{
    lbId = ui->lb_videoDisplay->winId();
    gstmanager.setWinid(lbId);
    gstmanager.startStream();
}

void IPTVPlayer::stopStreamPressed()
{
    gstmanager.stopStream();
}

QLabel* IPTVPlayer::getVideoDisplay() const
{
    return ui->lb_videoDisplay;
}
