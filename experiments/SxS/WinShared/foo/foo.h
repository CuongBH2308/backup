#pragma once

#ifdef FOO_EXPORTS
#define FOO_API __declspec(dllexport)
#else
#define FOO_API __declspec(dllimport)
#endif

FOO_API void foo();