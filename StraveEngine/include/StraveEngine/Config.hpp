#pragma once

#define STRAVE_VERSION_MAJOR 1
#define STRAVE_VERSION_MINOR 0
#define STRAVE_VERSION_PATCH 0


#if defined(_WIN32)

    // Windows 
    #define STRAVE_SYSTEM_WINDOWS
#else
    // Unsupported operating system
    #error This operating system is not supported by Strave Engine
#endif

#if defined(STRAVE_SYSTEM_WINDOWS)

    // Exports definitions
    #define STRAVE_SYSTEM_EXPORTS

    // Windows import and export dll files
    #define STRAVE_API_EXPORT __declspec(dllexport)
    #define STRAVE_API_IMPORT __declspec(dllimport)
    
    // Turn off Visual C++ compiler warning
    #ifdef _MSC_VER
        #pragma warning(disable: 4251)
    #endif

    // Turn off compile "function unsafe" errors
    // #define _CRT_SECURE_NO_WARNINGS

#endif
