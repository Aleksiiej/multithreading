#include <iostream>
#include <mutex>
#include <numeric>
#include <utility>
#include <vector>
#include <thread>

namespace my
{
    template <class InputIt, class T>
    T accumulate(InputIt first, InputIt last, T init)
    {
        std::cout << "Accumulate lives!" << std::endl;

        // calculating number of elements in collection
        int numberOfElements = 0;
        auto begin = first;
        auto end = last;
        while (begin != end)
        {
            numberOfElements++;
            begin++;
        }
        begin = first;
        // std::cout << numberOfElements << std::endl;

        int numberOfThreads = std::thread::hardware_concurrency() - 1;
        int elementsInThread = numberOfElements / std::thread::hardware_concurrency();
        std::vector<std::thread> threads;
        for (uint8_t i = 0; i < std::thread::hardware_concurrency(); i++)
        {
            threads.emplace_back(std::accumulate, std::ref(begin + (i * numberOfThreads)), std::ref(begin + ((i + 1) * numberOfThreads)), 0);
        }
        for (auto &thread : threads)
        {
            if (thread.joinable())
            {
                thread.join();
            }
        }

        return init;
    }
}

int main()
{
    std::cout << "Optimal number of threads: " << std::thread::hardware_concurrency() << std::endl;
    std::vector<int> numbers{};
    for (int i = 0; i < 10'000; i++)
    {
        numbers.push_back(i);
    }
    int sum = my::accumulate(begin(numbers), end(numbers), 0);
    std::cout << sum << std::endl;
}