#pragma once
#include <string>

class Resource
{
public:
    Resource(const wchar_t* full_path);
    virtual ~Resource() = 0;

protected:
    std::wstring m_full_path;
};

