#pragma once
#include <source_location>

#ifndef CUTIL_MACROS_NO_AUTO_INCLUDE
#include "util/location-print.hpp"
#endif

#define CUTIL_COMPSTR(cstr) comptime::String<std::string_view(cstr).size()>(std::string_view(cstr))
#define CUTIL_GENERIC_PRINT(err, ...)                             \
    {                                                             \
        constexpr auto loc  = std::source_location::current();    \
        constexpr auto file = CUTIL_COMPSTR(loc.file_name());     \
        constexpr auto func = CUTIL_COMPSTR(loc.function_name()); \
        constexpr auto line = loc.line();                         \
        location_print<file, func, line, err>(__VA_ARGS__);       \
    }

#define PRINT(...) CUTIL_GENERIC_PRINT(false, __VA_ARGS__)
#define WARN(...)  CUTIL_GENERIC_PRINT(true, __VA_ARGS__)
