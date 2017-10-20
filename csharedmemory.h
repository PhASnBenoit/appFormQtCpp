#ifndef CSHAREDMEMORY_H
#define CSHAREDMEMORY_H

#include <QSharedMemory>

class CSharedMemory : public QSharedMemory
{
    Q_OBJECT
public:
    explicit CSharedMemory(QObject *parent = 0);

signals:

public slots:

};

#endif // CSHAREDMEMORY_H
