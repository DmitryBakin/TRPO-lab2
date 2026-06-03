#ifndef CSHARPCLASSUNIT_H
#define CSHARPCLASSUNIT_H

#include "IClassUnit.h"


class CSharpClassUnit : public IClassUnit {
public:
    enum AccessModifier { PRIVATE, PROTECTED, PUBLIC, INTERNAL };
    static const std::vector<std::string> ACCESS_MODIFIERS;

    explicit CSharpClassUnit(const std::string& name);

    void add(std::shared_ptr<Unit> unit, Flags flags = 0) override;
    std::string compile(unsigned int level = 0) const override;

private:
    std::string m_name;
    std::vector<std::vector<std::shared_ptr<Unit>>> m_fields;
};

#endif // CSHARPCLASSUNIT_H
