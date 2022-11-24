#include <thread>
#include <stdexcept>
#include <chrono>
#include <iostream>
using namespace std;

class scoped_thread
{
public:
    scoped_thread(void (*func)(int i), int number) : t_(std::thread(func, number))
    {
    }
    explicit scoped_thread(std::thread &&t) : t_(std::move(t))
    {
    }
    scoped_thread(const scoped_thread &other) = delete;
    scoped_thread &operator=(const scoped_thread &other) = delete;
    scoped_thread(scoped_thread &&other) = default;
    scoped_thread &operator=(scoped_thread &&other) = default;
    ~scoped_thread()
    {
        if (t_.joinable())
        {
            t_.join();
        }
    }

private:
    std::thread t_;
};

void do_sth(int)
{
    this_thread::sleep_for(1s);
    cout << this_thread::get_id() << '\n';
}

void do_sth_unsafe_in_current_thread()
{
    throw runtime_error("Whoa!");
}

int main()
try
{
    // TODO: Uncomment
    scoped_thread st(std::thread(do_sth, 42));
    // auto st2 = st; // copying not allowed
    [[maybe_unused]] auto st3 = move(st);
    scoped_thread st4(do_sth, 42);
    do_sth_unsafe_in_current_thread();
    return 0;
}
catch (const exception &e)
{
    cout << e.what() << endl;
    return -1;
} // thread is safely destroyed
