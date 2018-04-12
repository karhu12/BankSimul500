#ifndef DLLPINCODE_H
#define DLLPINCODE_H

#include "dllpincode_global.h"
#include "uiengine.h"
#include <QDebug>

class DLLPINCODESHARED_EXPORT DLLPinCode
{

public:
    void interfaceFunction();
    QString interfaceFunctionReturnFunction();

private:
    UIEngine *objectUIEngine;
    QString valueToReturn;

};

#endif // DLLPINCODE_H
