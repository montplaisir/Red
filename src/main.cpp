#include "RedMgr.hpp"

int main(int argc, char ** argv)
{  
    auto evaluator = std::make_unique<Evaluator>();
    int numThreads = 4;
    if (argc > 1)
    {
        numThreads = std::atoi(argv[1]);
    }
    RedMgr redmgr(std::move(evaluator), numThreads);

    bool success = redmgr.run();
    std::cout << "VRM: success? " << success << std::endl;

    return 0;
}
