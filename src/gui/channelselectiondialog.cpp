#include "channelselectiondialog.h"
#include "qdebug.h"
#include "iptvplayer.h"

#include <QFile>
#include <QVBoxLayout>


ChannelSelectionDialog::ChannelSelectionDialog(QWidget *parent) : QDialog(parent)
{
    m_listWidget = new QListWidget(this);

    // Leer el archivo .m3u y agregar los canales a la lista
    QFile file("/home/mkassimi/Downloads/tv_channels_Mosin_plus.m3u");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            if (line.startsWith("#EXTINF:")) {
                // Filtrar el canal deseado y agregarlo a la lista
                QString channelName = line.section(",", 1);
                QString channelUri = in.readLine();
                QListWidgetItem *item = new QListWidgetItem(channelName);
                item->setData(Qt::UserRole, channelUri);
                m_listWidget->addItem(item);
            }
        }
    }
    file.close();

    // Conectar la señal itemDoubleClicked a la slot doubleClicked
    connect(m_listWidget, &QListWidget::itemDoubleClicked, this, &ChannelSelectionDialog::onChannelListDoubleClicked);

    // Configurar la ventana
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(m_listWidget);
    setWindowTitle("Channels");
}

//void ChannelSelectionDialog::doubleClicked(QListWidgetItem *item)
//{
//    // Obtener la URI del canal seleccionado y cerrar el cuadro de diálogo
//    QString uri = item->data(Qt::UserRole).toString();
//    qDebug()<< "Esta es la Uri seleccionada: " << uri;
//    close();

//    // Enviar la URI a la clase Gstreamer para su reproducción
//    // ...
//}

void ChannelSelectionDialog::onChannelListDoubleClicked(QModelIndex index)
{
    m_selectedUri = m_channelsModel->data(index).toString();
    emit channelSelected(m_selectedUri);
    accept();
}
