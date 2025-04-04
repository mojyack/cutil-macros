#include "unwrap.hpp"

#define _unwrap unwrap
#define _ensure ensure
#define _return return
#define _await
#define Ret(type) type

#include "assert-test-common.cpp"

auto main() -> int {
    test();
    if(pass) {
        std::println("pass");
    }
    ASSERT(false, "with {}", "message");
    PANIC();
    return 0;
}
