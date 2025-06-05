#include "core/application.h"

int main()
{
    try{
        Application app;
        app.run();
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }
    return 0;
}