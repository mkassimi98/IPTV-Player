#include "iptvplayer.h"
#include "./ui_iptvplayer.h"
#include <iostream>
#include <QDebug>

IPTVPlayer::IPTVPlayer(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::IPTVPlayer)
    , dialog(this)
{
    ui->setupUi(this);
    gstmanager = new GSTreamerManager(this);
    dialog.hide();
    connect(ui->pb_play, &QPushButton::clicked, this, &IPTVPlayer::runStreamPressed);
    connect(ui->pb_stop, &QPushButton::clicked, this, &IPTVPlayer::stopStreamPressed);
    connect(ui->pb_loadPlaylist, &QPushButton::clicked, this, &IPTVPlayer::selectPlaylistFile);
    connect(ui->pb_openPlaylist, &QPushButton::clicked, this, &IPTVPlayer::showChannelSelectionDialog);
    connect(&dialog, &ChannelSelectionDialog::channelSelected, this, &IPTVPlayer::printUri);
}

IPTVPlayer::~IPTVPlayer()
{
    gstmanager->stop();
    gstmanager->wait();
    delete gstmanager;
    delete ui;
}

void IPTVPlayer::runStreamPressed()
{
    lbId = ui->lb_videoDisplay->winId();
    gstmanager->setWinid(lbId);
    gstmanager->configureGst();
    gstmanager->start();
}

void IPTVPlayer::stopStreamPressed()
{
    gstmanager->stop();
}

QLabel* IPTVPlayer::getVideoDisplay() const
{
    return ui->lb_videoDisplay;
}

void IPTVPlayer::selectPlaylistFile()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile); // Only allow to choose one file
    dialog.setNameFilter(tr("Playlists files (*.m3u)")); // Filter of diles
    
    QStringList fileNames;
    if (dialog.exec()) {
        fileNames = dialog.selectedFiles();
        filePath = fileNames.at(0); // Save the first choosed
        // Show the filePath
        qDebug() << "This is the Path: "  << filePath;
    }
}

void IPTVPlayer::showChannelSelectionDialog()
{
    dialog.show();
    if (dialog.exec() == QDialog::Accepted) {
        // El usuario ha seleccionado un canal y ha cerrado el cuadro de diálogo
        // ...
        dialog.hide();
    }
}

void IPTVPlayer::printUri(QString uri)
{
//    gstmanager->stop();
    gstmanager->setChannelSource(uri.toStdString());
//    gstmanager->start();
    qDebug() << "[IPTVPlayer::printUri] Esta es la Uri de la señal: " << uri;
}
