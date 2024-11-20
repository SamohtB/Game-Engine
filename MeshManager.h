#pragma once
#include "AResourceManager.h"
#include "Prerequisites.h"

class MeshManager : public AResourceManager
{
public:
    MeshManager();
    ~MeshManager();

    MeshPtr createMeshFromFile(const wchar_t* file_path);

protected:
    Resource* createResourceFromFileConcrete(const wchar_t* file_path) override;
};
