#include <chrono>
#include <iostream>
#include <mutex>
#include <sstream>
#include <thread>
#include <vector>
using namespace std;

// Secure your code so that each thread can safely enter its full text into the stream.

void do_work(int id, mutex &m)
{
    this_thread::sleep_for(100ms);
    stringstream ss;
    ss << "Thread [" << id << "]: " << "Job done!" << endl;
    const lock_guard<mutex> lock{m};
    cout << ss.str();
}

int main()
{
    mutex m;
    vector<thread> threads;
    for (int i = 0; i < 20; i++)
    {
        threads.emplace_back(do_work, i, ref(m));
    }
    for (auto &&t : threads)
    {
        t.join();
    }
    return 0;
}
