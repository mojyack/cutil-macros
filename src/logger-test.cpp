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
                    LOG_ERROR(logger, "error! worker=", num, " ", __LINE__);
                    LOG_WARN(logger, "warn! worker=", num, " ", __LINE__);
                    LOG_INFO(logger, "info! worker=", num, " ", __LINE__);
                    LOG_DEBUG(logger, "debug! worker=", num, " ", __LINE__);
                    std::this_thread::sleep_for(std::chrono::milliseconds(500));
                }
            });
    }
    for(auto& worker : workers) {
        worker.join();
    }
    return 0;
}
