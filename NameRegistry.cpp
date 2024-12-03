#include "NameRegistry.h"

NameRegistry::NameRegistry()
{
}

NameRegistry::~NameRegistry()
{
}

void NameRegistry::registerName(const String& base_name)
{
    if (m_name_count.find(base_name) == m_name_count.end())
    {
        m_name_count[base_name] = 0;
    }
}

NameRegistry::String NameRegistry::getUniqueName(const String& base_name)
{
    registerName(base_name);
    int index;

    if (!recycledIndices[base_name].empty())
    {
        index = recycledIndices[base_name].front();
        recycledIndices[base_name].pop();
    }
    else
    {
        index = m_name_count[base_name]++;
    }

    return base_name + "_" + std::to_string(index);
}

void NameRegistry::releaseName(const String& name)
{
    size_t pos = name.find_last_of('_');

    if (pos != String::npos)
    {
        String baseName = name.substr(0, pos);
        int index = std::stoi(name.substr(pos + 1));
        recycledIndices[baseName].push(index);
    }
}
