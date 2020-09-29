#ifndef __BASEINCLUDE_H__
#define __BASEINCLUDE_H__

#ifndef __linux__
#include <Windows.h>
#else
#include <unistd.h>
#include <sys/syscall.h>
#include <dlfcn.h>
#endif // !__linux__



#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <deque>
#include <thread>
#include <mutex>
#include <chrono>
#include <filesystem>
#include <sstream>
#include <fstream>
#include <iomanip>


#endif // !__BASEINCLUDE_H__
