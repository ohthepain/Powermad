/*
	myassert.h
*/

#pragma once

namespace Atomic {
#ifndef NDEBUG
void write();
void dowrite(const char* s);
void dowrite(int i);
template<typename Arg1, typename... Args>
void write(const Arg1 arg1, const Args&... args)
{
	dowrite(arg1);
	write(args...);
}
template<typename Arg1, typename... Args>
void write3(const char* s, int l, const Arg1 arg1, const Args&... args)
{
	dowrite(s);
	dowrite(":");
	dowrite(l);
	dowrite(": ");
	dowrite(arg1);
	write(args...);
}
#endif
}

#ifdef __cplusplus
extern "C" {
namespace Atomic {
#endif

#include "_ansi.h"

void __attribute__((noreturn)) __my_assert_func(const char*, int, const char*, const char* message=nullptr);

#ifdef NDEBUG           /* required by ANSI standard */
# define myassert(__e) ((void)0)
# define myassert(__e,__m) ((void)0)
# define msg(m,...) ((void)0)
#else
# define myassert(__e) ((__e) ? (void)0 : __my_assert_func(__FILE__, __LINE__, #__e))
# define myassertmsg(__e,__m) ((__e) ? (void)0 : __my_assert_func(__FILE__, __LINE__, #__e, __m))
//# define msg(...) write(__VA_ARGS__)
# define msg(...) Atomic::write3(__FILE__, __LINE__, __VA_ARGS__)
#endif
#ifdef __cplusplus
}
}
#endif
