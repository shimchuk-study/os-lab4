#pragma once

#ifndef FILENAME_CPP
#define FILENAME_CPP

#include <cstdint>
#include <iostream>

union FileName {
    // Put arguments as values cause sizeof(FileName*) > sizeof(FileName)
    friend bool operator==(FileName lfn, FileName rfn); 
    friend bool operator<(FileName lfn, FileName rfn);
    friend std::ostream& operator<<(std::ostream& os, FileName fn);
    
    // Do not set error flags if input parameter is invalid
    friend std::istream& operator>>(std::istream& is, FileName& fn);
private:
    bool m_state = false;
    char m_name[2];
    uint16_t m_comp;
public:
    FileName() = default;
    FileName(std::string_view view);

    inline bool isValid() const { return m_state; }
    inline std::string get() const { char arr[] = { m_name[0], m_name[1], '\0'}; return arr; }
};

#endif // FILENAME_CPP
