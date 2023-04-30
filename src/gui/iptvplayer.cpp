#include "iptvplayer.h"
#include "./ui_iptvplayer.h"

IPTVPlayer::IPTVPlayer(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::IPTVPlayer)
{
    ui->setupUi(this);
}

IPTVPlayer::~IPTVPlayer()
{
    delete ui;
}

