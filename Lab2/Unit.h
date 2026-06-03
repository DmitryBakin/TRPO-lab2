#ifndef UNIT_H
#define UNIT_H

#include <vector>
#include <memory>

using Flags = unsigned int;

class Unit
{
public:
    virtual ~Unit() = default;
    virtual std::string compile(unsigned int level = 0) const = 0;

protected:
    std::string generateShift(unsigned int level) const;
};

#endif // UNIT_H
