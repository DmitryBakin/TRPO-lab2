#ifndef ICLASSUNIT_H
#define ICLASSUNIT_H

#include "Unit.h"

class IClassUnit : public Unit
{
public:
    virtual ~IClassUnit() = default;
    virtual void add(std::shared_ptr<Unit> unit, Flags flags = 0) = 0;
};


#endif // ICLASSUNIT_H
