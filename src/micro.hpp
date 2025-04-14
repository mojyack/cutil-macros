#include <print>

#if !defined(MICRO_MACRO_H)

#define MICRO_MACRO_H
#pragma push_macro("ensure")
#pragma push_macro("unwrap")
#undef ensure
#define ensure(cond, act)                                                      \
    if(!(cond)) {                                                              \
        std::println(stderr, "assertion failed at {}:{}", __FILE__, __LINE__); \
        act;                                                                   \
    }
#undef unwrap
#define unwrap(var, exp, act) \
    auto var##_o = (exp);     \
    ensure(var##_o, act);     \
    auto& var = *var##_o;

#else

#undef MICRO_MACRO_H
#pragma pop_macro("ensure")
#pragma pop_macro("unwrap")

#endif
