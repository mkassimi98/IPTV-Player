#ifndef A_H
#define A_H

#include <QObject>

class a : public QObject
{
    Q_OBJECT
public:
    explicit a(QObject *parent = nullptr);

signals:

};

#endif // A_H
