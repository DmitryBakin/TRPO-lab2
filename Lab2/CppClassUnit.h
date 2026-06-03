#ifndef CPPCLASSUNIT_H
#define CPPCLASSUNIT_H

#include "IClassUnit.h"

class CppClassUnit : public IClassUnit
{
public:
    static const std::vector<std::string> ACCESS_MODIFIERS;

    enum Access { PRIVATE, PROTECTED, PUBLIC };

    explicit CppClassUnit(const std::string& name);

    void add(std::shared_ptr<Unit> unit, Flags flags) override;
    std::string compile(unsigned int level = 0) const override;

private:
    std::string m_name;
    std::vector<std::vector<std::shared_ptr<Unit>>> m_fields;
};

#endif // CPPCLASSUNIT_H
