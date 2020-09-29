#include "Logger.h"

int main()
{
    while (true)
    {
        LOG_ERROR("hello test!");
        Util::Sleep(100);
    }
    

    return 0;
}
