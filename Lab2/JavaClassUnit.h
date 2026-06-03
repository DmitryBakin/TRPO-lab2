#ifndef JAVACLASSUNIT_H
#define JAVACLASSUNIT_H

#include "IClassUnit.h"

class JavaClassUnit : public IClassUnit {
public:
    static const std::vector<std::string> ACCESS_MODIFIERS;

    enum AccessModifier { PRIVATE, PROTECTED, PUBLIC};

    explicit JavaClassUnit(const std::string& name);

    void add(std::shared_ptr<Unit> unit, Flags flags = 0) override;
    std::string compile(unsigned int level = 0) const override;

private:
    std::string m_name;
    std::vector<std::vector<std::shared_ptr<Unit>>> m_fields;
};

#endif // JAVACLASSUNIT_H
