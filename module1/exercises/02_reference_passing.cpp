#include <thread>
#include <iostream>
using namespace std;

void add10(int & a)
{
    a += 10;
    cout << "Inside thread: " << a << endl;
}

int main()
{
    int number = 5;
    thread t{add10, ref(number)};
    cout << "Before join: " << number << endl;
    t.join();
    cout << "After join: " << number << endl;
    // run add10 function in a thread
    // pass 5 as an argument and read it's value
    return 0;
}

