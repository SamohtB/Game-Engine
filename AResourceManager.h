#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include <exception>

#include "Prerequisites.h"

typedef std::string String;
typedef std::unordered_map<std::wstring, ResourcePtr> ResourceTable;

class AResourceManager
{
public:
    AResourceManager();
    ~AResourceManager();

    ResourcePtr createResourceFromFile(const wchar_t* file_path);

protected:
    virtual Resource* createResourceFromFileConcrete(const wchar_t* file_path) = 0;

private:
    ResourceTable m_map_resources;
};
