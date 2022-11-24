#include <chrono>
#include <iostream>
#include <mutex>
#include <vector>
#include <thread>

using namespace std::chrono_literals;

int main() {
    // TODO: Implement your solution :)

    std::mutex mt;
    std::vector<std::thread> threads;

    for(int i = 0; i < 20; i++)
    {
        threads.emplace_back( [&] (auto number) { std::this_thread::sleep_for(1s);
                                                  mt.lock();
                                                  std::cout << number << '\n';
                                                  mt.unlock(); }
                                                  , i);
    }

    for(auto& el : threads)
    {
        el.join();
    }

    return 0;
}
