#ifndef CPPMETHODUNIT_H
#define CPPMETHODUNIT_H

#include "IMethodUnit.h"

class CppMethodUnit : public IMethodUnit
{
public:
    enum Modifier { STATIC = 1, CONST = 1 << 1, VIRTUAL = 1 << 2 };

    CppMethodUnit(const std::string& name, const std::string& returnType, Flags flags);

    void add(std::shared_ptr<Unit> unit) override;
    std::string compile(unsigned int level = 0) const override;

private:

    std::string m_name, m_returnType;
    Flags m_flags;
    std::vector<std::shared_ptr<Unit>> m_body;
};


#endif // CPPMETHODUNIT_H
