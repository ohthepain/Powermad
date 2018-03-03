/*
	myassert.h
*/

#pragma once

#ifdef __cplusplus
extern "C" {
namespace Atomic {
#endif

#include "_ansi.h"

void __attribute__((noreturn)) __my_assert_func(const char*, int, const char*);

#ifdef NDEBUG           /* required by ANSI standard */
# define myassert(__e) ((void)0)
#else
# define myassert(__e) ((__e) ? (void)0 : __my_assert_func(__FILE__, __LINE__, #__e))
#endif
#ifdef __cplusplus
}
}
#endif
