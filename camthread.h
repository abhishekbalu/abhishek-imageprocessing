#ifndef CAMTHREAD_H
#define CAMTHREAD_H
#include<QtCore>
#include "structures.h"
#include "cv.h"

class CamThread : public QThread
{
public:
    CamThread();
    void run();
private:



};

#endif // CAMTHREAD_H
