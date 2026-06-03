#ifndef IMETHODUNIT_H
#define IMETHODUNIT_H

#include "Unit.h"

class IMethodUnit : public Unit
{
public:
    virtual ~IMethodUnit() = default;
    virtual void add(std::shared_ptr<Unit> unit) = 0;
};

#endif // IMETHODUNIT_H
