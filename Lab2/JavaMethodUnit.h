#ifndef JAVAMETHODUNIT_H
#define JAVAMETHODUNIT_H

#include "IMethodUnit.h"

class JavaMethodUnit : public IMethodUnit {
public:
    enum Modifier { STATIC = 1, FINAL = 1 << 1, ABSTRACT = 1 << 2};

    JavaMethodUnit(const std::string& name, const std::string& returnType, Flags flags = 0);

    void add(std::shared_ptr<Unit> unit) override;
    std::string compile(unsigned int level = 0) const override;

private:
    std::string m_name, m_returnType;
    Flags m_flags;
    std::vector<std::shared_ptr<Unit>> m_body;
};

#endif // JAVAMETHODUNIT_H
