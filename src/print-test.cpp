#include <optional>

#include "print.hpp"

auto f() -> void {
    PRINT("func");
}

auto a(int) -> void {
    PRINT("func with args");
}

template <class T, class U>
auto t() -> void {
    PRINT("template func");
}

auto s() -> std::optional<std::optional<const int>> {
    PRINT("space in return type");
    return {};
}

auto p() -> int** {
    PRINT("pointer return type");
    return nullptr;
}

auto cp() -> const int* const* {
    PRINT("const pointer return type");
    return nullptr;
}

struct S {
    static auto s() -> void {
        PRINT("struct static");
    }

    auto f() -> void {
        PRINT("struct method");
    }

    auto c() const -> void {
        PRINT("struct const");
    }

    virtual auto v() -> void {
        PRINT("struct virtual");
    }

    template <class T, class U>
    auto t(int) const -> void {
        PRINT("struct template method");
    }

    S() {
        PRINT("struct constructor");
    }

    ~S() {
        PRINT("struct destructor");
    }
};

namespace ns {
auto f() -> void {
    PRINT("namespace");
}

namespace ns2 {
auto f() -> void {
    PRINT("nested namespace");
}

namespace ns3 {
auto f() -> void {
    PRINT("nested namespace");
}
} // namespace ns3
} // namespace ns2

namespace {
auto f2() -> void {
    PRINT("anonymous namespace");
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
        s.v();
        s.t<int, char>(0);
    }
    ns::f();
    ns::ns2::f();
    ns::ns2::ns3::f();
    ns::f2();
    auto l = [&](int) {
        PRINT("lambda");
    };
    l(0);
    return 0;
}
