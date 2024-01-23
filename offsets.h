#pragma once
#include <cstddef>

namespace client_offsets { // client.dll
    constexpr std::ptrdiff_t dw_local_player_pawn = 0x16D4F48;
}

namespace engine2_offsets { // engine2.dll
    
}

namespace game_info_offsets {
    constexpr std::ptrdiff_t build_number = 0x36A1; // Game build number
}

namespace inputsystem_offsets { // inputsystem.dll
    constexpr std::ptrdiff_t dw_input_system = 0x35760;
}