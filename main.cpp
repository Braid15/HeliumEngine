#ifdef _DEBUG
#include "S:\SDKs\Visual_Leak_Detector\include\vld.h"
#endif

#include "src/helium_engine.h"


using namespace HeliumEngine;

int main() {

    int exit_code = Engine::run();

    system("PAUSE");
    return exit_code;
}

