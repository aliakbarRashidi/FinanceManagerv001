//!  Globals.
/*!
  Contains global variables used throughout the logger.

  \author Esmerald Aliaj
  \version 0.1 06/03/16.
*/

#ifndef LOGGLOBAL_H
#define LOGGLOBAL_H

#include <QtGlobal>

// This is specific to Windows dll's
#if defined(Q_OS_WIN)
    #if defined(FINANCEMANAGERLIB_EXPORT)
        #define DECLSPEC Q_DECL_EXPORT
    #elif defined(FINANCEMANAGERLIB_IMPORT)
        #define DECLSPEC Q_DECL_IMPORT
    #endif
#endif
#if !defined(DECLSPEC)
    #define DECLSPEC
#endif

#endif // LOGGLOBAL_H

