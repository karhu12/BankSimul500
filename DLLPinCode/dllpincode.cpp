#include "dllpincode.h"

void DLLPinCode::interfaceFunction()
{
    objectUIEngine = new UIEngine;

    objectUIEngine->showFullScreen();
    objectUIEngine->exec();

    valueToReturn= objectUIEngine->returnPass();

    delete objectUIEngine;

}

QString DLLPinCode::interfaceFunctionReturnFunction()
{
    return valueToReturn;
}
