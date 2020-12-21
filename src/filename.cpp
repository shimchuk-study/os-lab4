#include "filename.hpp"

#include <cctype>

using namespace std;

FileName::FileName(std::string_view view)
{
    auto len = view.length();

    if (len == 1) {
        auto c = view[0];
        if (isalnum(view[0])) {
            m_name[0] = c;
            m_name[1] = '\0';
        }
    }
    else if (len == 2) {
        auto c0 = view[0], c1 = view[1];
        if (isalnum(c0) && isalnum(c1)) {
            m_name[0] = c0;
            m_name[1] = c1;
        }
    }
}

bool operator==(FileName lfn, FileName rfn)
{
    if (rfn.isValid() && lfn.isValid())
        return lfn.m_comp == rfn.m_comp;

    return false;
}

bool operator<(FileName lfn, FileName rfn)
{
    if (rfn.isValid() && lfn.isValid())
        return lfn.m_comp < rfn.m_comp;

    return false;
}

ostream& operator<<(ostream& os, FileName fn)
{
    if (fn.isValid())
        return os << fn.m_name[0] 
                  << (fn.m_name[1] == '\0' ? ' ' : fn.m_name[1]);
    return os << "<invalid file name>";
}

istream& operator>>(istream& is, FileName& fn)
{
    string buf;
    is >> buf;

    fn = FileName(buf);

    return is;
}
