#include "ILanguageFactory.h"

std::string Unit::generateShift(unsigned int level) const
{
    return std::string(level * 4, ' ');
}
