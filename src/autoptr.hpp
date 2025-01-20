#pragma once
#include <memory>

#define declare_autoptr(Name, Type, func)                 \
    struct Name##Deleter {                                \
        static auto operator()(Type* const ptr) -> void { \
            func(ptr);                                    \
        }                                                 \
    };                                                    \
    using Auto##Name = std::unique_ptr<Type, Name##Deleter>;
