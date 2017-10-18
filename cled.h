#ifndef CLED_H
#define CLED_H

#include <QObject>

class CLed : public QObject
{
    Q_OBJECT

public:
    explicit CLed(QObject *parent = 0);

signals:

public slots:
};

#endif // CLED_H
