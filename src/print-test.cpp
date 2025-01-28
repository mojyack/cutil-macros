#include <optional>

#include "print.hpp"

#define MARKER(name)                                       \
    std::println(stderr, "(raw {})", __PRETTY_FUNCTION__); \
    PRINT(name);

auto f() -> void {
    MARKER("func");
}

auto a(int) -> void {
    MARKER("func with args");
}

template <class T, class U>
auto t() -> void {
    MARKER("template func");
}

auto s() -> std::optional<std::optional<const int>> {
    MARKER("space in return type");
    return {};
}

auto p() -> int** {
    MARKER("pointer return type");
    return nullptr;
}

auto cp() -> const int* const* {
    MARKER("const pointer return type");
    return nullptr;
}

struct S {
    static auto s() -> void {
        MARKER("struct static");
    }

    auto f() -> void {
        MARKER("struct method");
    }

    auto c() const -> void {
        MARKER("struct const");
    }

    auto c2(std::optional<std::string>) -> void {
        [&](int) {
            MARKER("lambda");
        }(0);
    }

    virtual auto v() -> void {
        MARKER("struct virtual");
    }

    template <class T, class U>
    auto t(int) const -> void {
        MARKER("struct template method");
    }

    S() {
        MARKER("struct constructor");
    }

    ~S() {
        MARKER("struct destructor");
    }
};

namespace ns {
auto f() -> void {
    MARKER("namespace");
}

namespace ns2 {
auto f() -> void {
    MARKER("nested namespace");
}

namespace ns3 {
auto f() -> void {
    MARKER("nested namespace");
}
} // namespace ns3
} // namespace ns2

namespace {
auto f2() -> void {
    MARKER("anonymous namespace");
}
} // namespace
} // namespace ns

auto main() -> int {
    f();
    a(0);
    t<int, std::basic_string<char>>();
    s();
    p();
    cp();
    {
        auto s = S();
        s.f();
        s.s();
        s.c();
        s.c2({});
        s.v();
        s.t<int, char>(0);
    }
    ns::f();
    ns::ns2::f();
    ns::ns2::ns3::f();
    ns::f2();
    auto l = [&](int) {
        MARKER("lambda");
    };
    l(0);
    auto var = 0;
    PRINT("pointer {}", &var);
    return 0;
}
