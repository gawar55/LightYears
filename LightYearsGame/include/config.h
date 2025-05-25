#pragma once
#include <string>

std::string GetResourceDir()
{
#ifdef NDEBUG
    return "assets/";
#else   
    return "/home/gawar/projects/LightYears/LightYearsGame/assets/";
#endif
}
