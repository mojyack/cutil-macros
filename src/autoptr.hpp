#include <memory>

#pragma push_macro("declare_autoptr")
#undef declare_autoptr

#define declare_autoptr(Name, Type, func)                 \
    struct Name##Deleter {                                \
        static auto operator()(Type* const ptr) -> void { \
            func(ptr);                                    \
        }                                                 \
    };                                                    \
    using Auto##Name = std::unique_ptr<Type, Name##Deleter>;
