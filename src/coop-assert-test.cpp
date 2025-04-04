#include <coop/generator.hpp>
#include <coop/promise.hpp>
#include <coop/runner.hpp>

#include "coop-unwrap.hpp"

#define _unwrap   coop_unwrap
#define _ensure   coop_ensure
#define _return   co_return
#define _await    co_await
#define Ret(type) coop::Async<type>

#include "assert-test-common.cpp"

auto main() -> int {
    auto runner = coop::Runner();
    runner.push_task(test());
    runner.run();
    if(pass) {
        std::println("pass");
    }
    return 0;
}
