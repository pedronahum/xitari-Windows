#pragma once

#ifdef SWIG
#define final
#define explicit
#define static_assert(condition, message)
#define __attribute__(x)
#endif

#ifdef _WIN32
#ifdef XITARYV1LIBRARYDLL
#define XITARI_API __declspec(dllexport)
#else
#define XITARI_API __declspec(dllimport)
#endif
#define _SCL_SECURE_NO_WARNINGS
#else // no DLLs on Linux
#define XITARI_API
#endif







