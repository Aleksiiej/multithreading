#include <chrono>
#include <iostream>
#include <mutex>
#include <vector>
#include <thread>

using namespace std::chrono_literals;

void showId(const int &number, std::mutex &m)
{
    for (int j = 0; j < number; j++)
    {
        std::lock_guard<std::mutex> lock{m};
        std::cout << std::this_thread::get_id() << std::endl;
    }
}

int main()
{
    std::mutex m;
    int number = 4;
    std::vector<std::thread> threads;
    for (int i = 0; i < 4; i++)
    {
        threads.emplace_back(std::thread{showId, std::ref(number), std::ref(m)});
    }
    for (auto &thread : threads)
    {
        if (thread.joinable())
        {
            thread.join();
        }
    }
}