#ifndef SERVICEFEE_GLOBAL_H
#define SERVICEFEE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(SERVICEFEE_LIBRARY)
#  define SERVICEFEESHARED_EXPORT Q_DECL_EXPORT
#else
#  define SERVICEFEESHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // SERVICEFEE_GLOBAL_H