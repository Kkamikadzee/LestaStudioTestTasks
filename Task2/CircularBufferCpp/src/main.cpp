#include <iostream>
#include <memory>
#include "CircularBufferArray.h"
#include "CircularBufferList.h"

void testCba();
void testCbl();

int main()
{
    testCbl();

    std::cout << "Hello, from CircularBuffer!\n";

    return 0;
}

void testCba()
{
    Kmk::CircularBufferArray<std::shared_ptr<int>, 5> cba{
        std::shared_ptr<int>(new int(54)),
        std::shared_ptr<int>(new int(45)),
        std::shared_ptr<int>(nullptr)};

    {
        auto &tmp = cba.Head();
        std::cout << *tmp << std::endl;
        *tmp = 5;
        std::cout << *tmp << std::endl;
    }
    {
        auto &tmp = cba.Head();
        std::cout << *tmp << std::endl;
    }

    cba.Next();
    {
        auto &tmp = cba.Head();
        std::cout << *tmp << std::endl;
        *tmp = 4;
        std::cout << *tmp << std::endl;
    }
    {
        auto &tmp = cba.Head();
        std::cout << *tmp << std::endl;
    }
    cba.Next();
    {
        auto &tmp = cba.Head();
        std::cout << *tmp << std::endl;
    }
}

void testCbl()
{
    Kmk::CircularBufferList<int> cbl{
        54,
        45,
        0,
        545};

    {
        auto &tmp = cbl.Head();
        std::cout << tmp << std::endl;
        tmp = 5;
        std::cout << tmp << std::endl;
    }
    {
        auto &tmp = cbl.Head();
        std::cout << tmp << std::endl;
    }

    cbl.Next();
    {
        auto &tmp = cbl.Head();
        std::cout << tmp << std::endl;
        tmp = 4;
        std::cout << tmp << std::endl;
    }
    {
        auto &tmp = cbl.Head();
        std::cout << tmp << std::endl;
    }
    cbl.Next();
    {
        auto &tmp = cbl.Head();
        std::cout << tmp << std::endl;
    }

    Kmk::CircularBufferList<int> cbl2(std::move(cbl));

    Kmk::CircularBufferList<int> cbl3(cbl2);
    // cbl2.Next();
    // {
    //     auto &tmp = cbl2.Head();
    //     std::cout << tmp << std::endl;
    // }

    while (cbl3.HasHead())
    {
        std::cout << cbl3.Head() << std::endl;
        cbl3.PopFront();
    }
    std::cout << "+++===+++" << std::endl;

    while (cbl2.HasHead())
    {
        std::cout << cbl2.Head() << std::endl;
        cbl2.PopFront();

        break;
    }

    Kmk::CircularBufferList<int> cbl4;
    cbl4 = cbl2;
    Kmk::CircularBufferList<int> cbl5;
    cbl5 = std::move(cbl2);

    cbl2.~CircularBufferList();
    std::cout << "+++===+++" << std::endl;
}