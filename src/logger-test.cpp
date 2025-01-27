#include <chrono>
#include <thread>

#include "logger.hpp"

auto main() -> int {
    auto logger = Logger("cutil");
    LOG_WARN(logger, "set CUTIL_LOGLEVEL=debug to see full outputs");

    auto workers = std::array<std::thread, 5>();
    for(auto num = 0u; num < workers.size(); num += 1) {
        workers[num] = std::thread(
            [&logger, num]() {
                for(auto i = 0; i < 3; i += 1) {
                    LOG_ERROR(logger, "error! worker={}", num);
                    LOG_WARN(logger, "warn! worker={}", num);
                    LOG_INFO(logger, "info! worker={}", num);
                    LOG_DEBUG(logger, "debug! worker={}", num);
                    std::this_thread::sleep_for(std::chrono::milliseconds(500));
                }
            });
    }
    for(auto& worker : workers) {
        worker.join();
    }
    return 0;
}
