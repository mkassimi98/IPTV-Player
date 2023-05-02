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

signals:
    void channelSelected(QString uri);

private:
    QListWidget *m_listWidget;
    QStringListModel *m_channelsModel;
    QString m_selectedUri;

public slots:
    void doubleClicked(QListWidgetItem *item);
//    void onChannelListDoubleClicked(QModelIndex index);
};

#endif // CHANNELSELECTIONDIALOG_H
