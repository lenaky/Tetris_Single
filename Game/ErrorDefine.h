#ifndef _ERROR_DEFINE_H_
#define _ERROR_DEFINE_H_

#include <cstdint>

namespace TETRIS {

    using ErrorCode = std::int64_t;

    const static ErrorCode TETRIS_ERROR_NONE = 0;

    enum TETRIS_ERROR_BASE
    {
        TETRIS_ERROR_INTERNAL = 0x1000,

    };

    enum INTERNAL_ERROR
    {
        TETRIS_GET_HANDLE_FAILED    = 0x0001 | TETRIS_ERROR_INTERNAL,
        TETRIS_GET_CONSOLE_FAILED   = 0x0002 | TETRIS_ERROR_INTERNAL, 
        TETRIS_SET_CONSOLE_FAILED   = 0x0003 | TETRIS_ERROR_INTERNAL,
    };
}
#endif
