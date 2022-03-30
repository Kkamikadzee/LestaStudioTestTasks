#include <iostream>
#include <ctime>
#include <functional>

using namespace std;

bool isEven0(int value)
{
    return value % 2 == 0;
}

inline bool isEven1(int value)
{
    return value % 2 == 0;
}

inline bool isEven2(int value)
{
    return !(value & 1);
}

void bench(std::function<bool(int)> f, unsigned int count)
{
    unsigned int start_time, end_time;

    start_time = clock();
    for (auto i = 0; i < count; ++i)
    {
        f(0);
        f(-1);
        f(-2);
        f(1);
        f(2);
    }
    end_time = clock();

    cout << (end_time - start_time) / 1000.0 << endl;
}

int main()
{
    unsigned int count = 100000000;
    unsigned int start_time, end_time;

    bench(isEven0, count);
    bench(isEven1, count);
    bench(isEven2, count);

    system("pause");

    return 0;
}
