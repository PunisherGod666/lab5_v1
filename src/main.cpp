#include <chrono>
#include <exception>
#include <future>
#include <iomanip>
#include <iostream>
#include <string>
#include <syncstream>
#include <thread>

namespace {

using namespace std::chrono_literals;

void compute(const std::string& name, std::chrono::seconds duration) {
    std::this_thread::sleep_for(duration);
    std::osyncstream(std::cout) << name << std::endl;
}

void slow(const std::string& name) { compute(name, 7s); }

void quick(const std::string& name) { compute(name, 1s); }

}  // namespace

void work() {
    const auto start = std::chrono::steady_clock::now();

    std::future<void> t1 = std::async(std::launch::async, [] {
        quick("A1");
        quick("C1");
        quick("C2");
        quick("D2");
    });

    slow("A2");
    t1.get();
    slow("B");
    quick("D1");

    const std::chrono::duration<double> elapsed = std::chrono::steady_clock::now() - start;
    std::osyncstream(std::cout) << "Execution time: " << std::fixed << std::setprecision(3)
                                << elapsed.count() << " s\n"
                                << "Work is done!" << std::endl;
}

int main() {
    try {
        work();
    } catch (const std::exception& e) {
        std::osyncstream(std::cerr) << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
