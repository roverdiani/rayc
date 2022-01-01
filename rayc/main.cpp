#include "Raycaster.h"

int main(int argc, char *argv[])
{
    std::unique_ptr<Raycaster> raycaster = std::make_unique<Raycaster>();

    while (raycaster->GetIsRunning())
        raycaster->Loop();

    return 0;
}
