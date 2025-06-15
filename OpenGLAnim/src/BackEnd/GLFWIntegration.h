#pragma once
#include "../Common/QwertyEnums.h"
#include <vector>

namespace GLFWIntegration {
    bool Init(API api, WindowedMode windowedMode);

    void MakeContextCurrent();

    void* GetWindowPointer();

    bool WindowIsOpen();

    void BeginFrame(API api);
    void EndFrame(API api);
}