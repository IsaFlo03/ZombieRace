#ifndef SNOOPY_LEVEL_UTILS_HPP
#define SNOOPY_LEVEL_UTILS_HPP

#include <cstdlib>

inline bool run_level(const char* exe) {
    int result = system(exe);
    // Si el usuario cierra la ventana, típicamente el valor es distinto de 0
    return result == 0;
}

#endif // SNOOPY_LEVEL_UTILS_HPP
