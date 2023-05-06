#include "channelselectiondialog.h"
#include "qdebug.h"

#include <QFile>
#include <QVBoxLayout>


ChannelSelectionDialog::ChannelSelectionDialog(QWidget *parent) : QDialog(parent)
{
    m_listWidget = new QListWidget(this);

    // Conectar la señal itemDoubleClicked a la slot doubleClicked
    connect(m_listWidget, &QListWidget::itemDoubleClicked, this, &ChannelSelectionDialog::doubleClicked);
    //connect(m_listWidget, &QListWidget::itemDoubleClicked, this, &IPTVPlayer::printUri);

    // Configurar la ventana
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(m_listWidget);
    setWindowTitle("Channels");
}

void ChannelSelectionDialog::doubleClicked(QListWidgetItem *item)
{
    // Obtener la URI del canal seleccionado y cerrar el cuadro de diálogo
    QString uri = item->data(Qt::UserRole).toString();
    emit channelSelected(uri);
    qDebug()<< "Esta es la Uri seleccionada: " << uri;

    // Enviar la URI a la clase Gstreamer para su reproducción
    // ...
}

void ChannelSelectionDialog::setFilePath(QString *file)
{
    _filePath = file;
    // Leer el archivo .m3u y agregar los canales a la lista
    if(_filePath && !_filePath->isEmpty())
    {
        QFile file(*_filePath);
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
    }
}
