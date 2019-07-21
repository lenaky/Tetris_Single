#ifndef _UTIL_H_
#define _UTIL_H_

#include <random>
#include <memory>

namespace TETRIS 
{
    static std::int64_t GetRandom( std::int64_t min, std::int64_t max )
    {
        std::random_device random_device;
        std::mt19937_64 mt( random_device() );
        std::uniform_int_distribution<std::int64_t> range( min, max );

        return range( mt );
    }
}

#endif
