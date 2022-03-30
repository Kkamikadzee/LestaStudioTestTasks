#pragma once
#include <iterator>
#include <exception>

namespace Kmk
{
    template <typename ValueType>
    inline ValueType GetBlockValue(ValueType n, std::size_t numberBlocks, std::size_t blockSize, std::size_t numberValuesInBlock)
    {
        return (n >> (blockSize * numberBlocks) & (numberValuesInBlock - 1));
    }

    template <typename RandomIterator>
    void RadixSort(RandomIterator begin, RandomIterator end, std::size_t blockSize = 8)
    {
        using difference_type = typename std::iterator_traits<RandomIterator>::difference_type;
        using value_type = typename std::iterator_traits<RandomIterator>::value_type;

        if (begin == end)
            return;

        if (sizeof(*begin) * 8 < blockSize)
        {
            throw std::invalid_argument("Block size (blockSize) is greater than size of value type.");
        }

        std::size_t numberBlocks = (sizeof(*begin) * 8 + blockSize - 1) / blockSize;
        const std::size_t numberValuesInBlock = 1l << blockSize;
        const difference_type bufferSize = std::distance(begin, end);

        value_type buffer[bufferSize];
        std::size_t valuesCount[numberValuesInBlock];
        auto valuesCountEndPtr = valuesCount + numberValuesInBlock;

        for (auto blockNumber = 0; blockNumber < numberBlocks; ++blockNumber)
        {
            for (auto valuePtr = valuesCount; valuePtr != valuesCountEndPtr; ++valuePtr)
                *valuePtr = 0;

            for (auto valuePtr = begin; valuePtr != end; ++valuePtr)
                ++valuesCount[GetBlockValue(*valuePtr, blockNumber, blockSize, numberValuesInBlock)];

            for (auto valuePtr = valuesCount + 1; valuePtr != valuesCountEndPtr; ++valuePtr)
                *valuePtr += *(valuePtr - 1);

            for (auto valuePtr = std::make_reverse_iterator(end); valuePtr != std::make_reverse_iterator(begin); ++valuePtr)
                buffer[--valuesCount[GetBlockValue(*valuePtr, blockNumber, blockSize, numberValuesInBlock)]] = *valuePtr;

            std::copy(buffer, buffer + bufferSize, begin);
        }
    }

} // namespace Kmk
