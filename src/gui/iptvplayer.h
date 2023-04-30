#ifndef IPTVPLAYER_H
#define IPTVPLAYER_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class IPTVPlayer; }
QT_END_NAMESPACE

class IPTVPlayer : public QMainWindow
{
    Q_OBJECT

public:
    IPTVPlayer(QWidget *parent = nullptr);
    ~IPTVPlayer();

private:
    Ui::IPTVPlayer *ui;
};
#endif // IPTVPLAYER_H
