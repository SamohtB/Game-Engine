#pragma once
#include <string>

class SceneWriter
{
public:
    typedef std::string String;
    SceneWriter(String directory);
    ~SceneWriter();

    void WriteToFile();

private:
    String directory;
};
