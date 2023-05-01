#include "iptvplayer.h"
#include "./ui_iptvplayer.h"
#include <iostream>
#include <QDebug>

IPTVPlayer::IPTVPlayer(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::IPTVPlayer)
{
    ui->setupUi(this);
    channel = qobject_cast<ChannelSelectionDialog*>(parent);
    connect(ui->pb_play, &QPushButton::clicked, this, &IPTVPlayer::runStreamPressed);
    connect(ui->pb_stop, &QPushButton::clicked, this, &IPTVPlayer::stopStreamPressed);
    connect(ui->pb_loadPlaylist, &QPushButton::clicked, this, &IPTVPlayer::selectPlaylistFile);
    connect(ui->pb_openPlaylist, &QPushButton::clicked, this, &IPTVPlayer::showChannelSelectionDialog);
//    connect(mw, &MainWindow::buttonPressed, this, &GstManager::onButtonPressed);
    connect(channel, &QListWidget::itemDoubleClicked, this, &IPTVPlayer::printUri);

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
        qDebug() << "This is teh Path: "  << filePath;
    }
}

void IPTVPlayer::showChannelSelectionDialog()
{
    ChannelSelectionDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        // El usuario ha seleccionado un canal y ha cerrado el cuadro de diálogo
        // ...
    }
}

void IPTVPlayer::printUri(QString uri)
{
    qDebug() << "Esta es la Uri de la señal: " << uri;
}
