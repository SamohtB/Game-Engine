#include <unordered_map>
#include <queue>
#include <string>

class NameRegistry
{
public:
    typedef std::string String;

    NameRegistry();
    ~NameRegistry();
    void registerName(const String& base_name);
    String getUniqueName(const String& base_name);
    void releaseName(const String& name);

private:
    std::unordered_map<String, int> m_name_count;
    std::unordered_map<String, std::queue<int>> recycledIndices;
};
