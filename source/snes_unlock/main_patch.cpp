#include "skyline/inlinehook/And64InlineHook.hpp"
#include "skyline/utils/cpputils.hpp"
#include "skyline/inlinehook/memcpy_controlled.hpp"

//02 20 80 52 04 04 80 52
constinit uint8_t unlock[8] = {0x02, 0x20, 0x80, 0x52, 0x04, 0x04, 0x80, 0x52};

//02 20 80 52 04 04 80 52 20 00 80 52
constinit uint8_t unlock_p[12] = {0x02, 0x20, 0x80, 0x52, 0x04, 0x04, 0x80, 0x52, 0x20, 0x00, 0x80, 0x52};

bool memcmp_f (const unsigned char *s1, const unsigned char *s2, size_t count) {
    while (count-- > 0)
        if (*s1++ != *s2++) 
            return false;
    return true;
}

size_t getCodeSize() {
        return (size_t)skyline::utils::getRegionAddress(skyline::utils::region::Rodata) - (size_t)skyline::utils::getRegionAddress(skyline::utils::region::Text);
}

/* You must provide full instructions in arrays of uint8_t.
It returns pointer to first found code in main 
or 0 if nothing have been found. */
uintptr_t findTextCode(const uint8_t* code, size_t size) {
    if (size % 4 != 0) return 0;
    uintptr_t addr = (uintptr_t)skyline::utils::getRegionAddress(skyline::utils::region::Text);
    size_t addr_size = getCodeSize();	
    uintptr_t addr_start = addr;
    while (addr != addr_start + addr_size) {
        bool result = memcmp_f((const unsigned char*)addr, code, size);
        if (result) return addr;
        addr += 4;
    }
    return 0;
}

void snes_unlock_main() {	
    uintptr_t pointer = findTextCode(&unlock[0], sizeof(unlock));
    if (pointer) {
        sky_memcpy((void*)pointer, &unlock_p[0], sizeof(unlock_p));
    }
}