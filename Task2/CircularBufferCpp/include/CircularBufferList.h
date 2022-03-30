#pragma once
#include <cstddef>
#include <memory>

namespace Kmk
{
    using std::size_t;

    template <typename ValueType>
    class CircularBufferList
    {
    public:
        CircularBufferList() : _headPtr(), _tailPtr()
        {
        }

        CircularBufferList(std::initializer_list<ValueType> il) : CircularBufferList()
        {
            for (auto valuePtr = il.begin(); valuePtr != il.end(); ++valuePtr)
            {
                Push(*valuePtr);
            }
        }

        CircularBufferList(const CircularBufferList &rhs) : CircularBufferList()
        {
            if (!rhs.HasHead())
            {
                return;
            }

            auto currentNode = rhs._headPtr;
            do
            {
                Push(currentNode->Value);
                currentNode = currentNode->Next;
            } while (&*currentNode != &*(rhs._headPtr));
        }

        CircularBufferList(CircularBufferList &&rhs) noexcept : _headPtr(rhs._headPtr), _tailPtr(rhs._tailPtr)
        {
            rhs._headPtr.reset();
            rhs._tailPtr.reset();
        }

        ~CircularBufferList() noexcept
        {
            Free();
        }

        CircularBufferList &operator=(const CircularBufferList &rhs)
        {
            if (this != &rhs)
            {
                Free();

                if (!rhs.HasHead())
                {
                    return *this;
                }

                auto currentNode = rhs._headPtr;
                do
                {
                    Push(currentNode->Value);
                    currentNode = currentNode->Next;
                } while (&*currentNode != &*(rhs._headPtr));
            }

            return *this;
        }

        CircularBufferList &operator=(CircularBufferList &&rhs) noexcept
        {
            if (this != &rhs)
            {
                Free();

                _headPtr = rhs._headPtr;
                _tailPtr = rhs._tailPtr;

                rhs._headPtr.reset();
                rhs._tailPtr.reset();
            }

            return *this;
        }

        void Push(const ValueType &value)
        {
            auto valueCopy(value);
            Push(std::move(valueCopy));
        }

        void Push(ValueType &&value)
        {
            if (!_tailPtr)
            {
                _tailPtr.reset();
                _tailPtr = std::make_shared<CircularBufferNode>(value);

                _tailPtr->Next = _tailPtr;
                _tailPtr->Previous = _tailPtr;
                _headPtr = _tailPtr;
                return;
            }

            auto newNode = std::make_shared<CircularBufferNode>(value);
            newNode->Previous = _tailPtr;
            _tailPtr->Next->Previous = newNode;
            newNode->Next = _tailPtr->Next;
            _tailPtr->Next = newNode;

            _tailPtr = newNode;
        }

        void PopFront()
        {
            if (!_headPtr)
            {
                return;
            }

            if (&*_headPtr == &*(_headPtr->Next))
            {
                _headPtr->Next.reset();
                _headPtr->Previous.reset();
                _headPtr.reset();
                _tailPtr.reset();
                return;
            }

            auto nextNode = _headPtr->Next;
            auto previousNode = _headPtr->Previous;
            nextNode->Previous = previousNode;
            previousNode->Next = nextNode;
            _headPtr.reset();
            _headPtr = nextNode;
        }

        ValueType &Head()
        {
            return _headPtr->Value;
        }

        inline bool HasHead() const
        {
            return static_cast<bool>(_headPtr);
        }

        void Next()
        {
            _headPtr = _headPtr->Next;
        }

    private:
        struct CircularBufferNode
        {
            ValueType Value;
            std::shared_ptr<CircularBufferNode> Next;
            std::shared_ptr<CircularBufferNode> Previous;

            explicit CircularBufferNode(const ValueType &value) : Value(value)
            {
            }

            CircularBufferNode(const CircularBufferNode &rhs) = delete;
            CircularBufferNode(CircularBufferNode &&rhs) = delete;

            ~CircularBufferNode()
            {
            }
        };

        std::shared_ptr<CircularBufferNode> _headPtr, _tailPtr;

        void Free()
        {
            if (_tailPtr)
            {
                auto currentNode = _headPtr;
                do
                {
                    auto nextNode = currentNode->Next;
                    currentNode->Next.reset();
                    currentNode->Previous.reset();
                    currentNode = nextNode;
                } while (&*currentNode != &*_headPtr);
            }
        }
    };

} // namespace Kmk