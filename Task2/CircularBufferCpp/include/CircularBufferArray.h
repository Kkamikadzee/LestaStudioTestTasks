#pragma once
#include <cstddef>
#include <array>

namespace Kmk
{
    using std::size_t;

    template <typename ValueType, size_t BufferSize>
    class CircularBufferArray
    {
    public:
        CircularBufferArray() : _buffer(), _headIndex(0), _tailIndex(0)
        {
        }

        CircularBufferArray(std::initializer_list<ValueType> il) : CircularBufferArray()
        {
            if (il.size() > BufferSize)
            {
                throw std::invalid_argument("Initializer list is too long.");
            }

            std::copy(il.begin(), il.end(), _buffer.begin());
            if (il.size() != BufferSize)
            {
                _tailIndex = il.size();
            }
        }

        CircularBufferArray(const CircularBufferArray &rhs) : _buffer(), _headIndex(rhs._headIndex), _tailIndex(rhs._tailIndex)
        {
            std::copy(rhs._buffer.cbegin(), rhs._buffer.cend(), _buffer.begin());
        }

        CircularBufferArray(CircularBufferArray &&rhs) noexcept : _buffer(std::move(rhs._buffer)), _headIndex(rhs._headIndex), _tailIndex(rhs._tailIndex)
        {
            rhs._buffer = nullptr;
        }

        ~CircularBufferArray() noexcept = default;

        CircularBufferArray &operator=(const CircularBufferArray &rhs)
        {
            if (this != &rhs)
            {
                std::copy(rhs._buffer.cbegin(), rhs._buffer.cend(), _buffer.begin());
                _headIndex = rhs._headIndex;
                _tailIndex = rhs._tailIndex;
            }

            return *this;
        }

        CircularBufferArray &operator=(CircularBufferArray &&rhs) noexcept
        {
            if (this != &rhs)
            {
                _buffer = std::move(rhs._buffer);
                rhs._buffer = nullptr;

                _headIndex = rhs._headIndex;
                _tailIndex = rhs._tailIndex;
            }

            return *this;
        }

        // TODO: Добавить Push с &&value
        void Push(const ValueType &value)
        {
            _buffer[_tailIndex] = value;

            _tailIndex = GetNextIndex(_tailIndex);
        }

        ValueType &Head()
        {
            return _buffer[_headIndex];
        }

        void Next()
        {
            _headIndex = GetNextIndex(_headIndex);
        }

        size_t GetCapacity() const
        {
            return BufferSize;
        }

    private:
        std::array<ValueType, BufferSize> _buffer;
        size_t _headIndex, _tailIndex;

        inline size_t GetNextIndex(const size_t index)
        {
            return (index + 1) % BufferSize;
        }
    };
} // namespace Kmk
