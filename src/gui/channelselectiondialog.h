#ifndef CHANNELSELECTIONDIALOG_H
#define CHANNELSELECTIONDIALOG_H

#include "qdialog.h"
#include <QListWidget>
#include <QStringListModel>
#include <QWidget>

class ChannelSelectionDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ChannelSelectionDialog(QWidget *parent = nullptr);
    void setFilePath(QString *file);

signals:
    void channelSelected(QString uri);

private:
    QListWidget *m_listWidget;
    QStringListModel *m_channelsModel;
    QString m_selectedUri;
    QString *_filePath;

public slots:
    void doubleClicked(QListWidgetItem *item);
};

#endif // CHANNELSELECTIONDIALOG_H
