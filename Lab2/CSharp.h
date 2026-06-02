#pragma once
#include "ILanguageFactory.h"
#include <vector>

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

class CSharpMethodUnit : public IMethodUnit {
public:
    enum Modifier { STATIC = 1, VIRTUAL = 1 << 1, ABSTRACT = 1 << 2 };

    CSharpMethodUnit(const std::string& name, const std::string& returnType, Flags flags = 0);

    void add(std::shared_ptr<Unit> unit) override;
    std::string compile(unsigned int level = 0) const override;

private:
    std::string m_name, m_returnType;
    Flags m_flags;
    std::vector<std::shared_ptr<Unit>> m_body;
};

class CSharpPrintOperatorUnit : public IPrintOperatorUnit {
public:
    explicit CSharpPrintOperatorUnit(const std::string& text);

    std::string compile(unsigned int level = 0) const override;

private:
    std::string m_text;
};

class CSharpFactory : public ILanguageFactory {
public:
    std::shared_ptr<IClassUnit> createClassUnit(const std::string& name) override;
    std::shared_ptr<IMethodUnit> createMethodUnit(const std::string& name,
                                                  const std::string& returnType,
                                                  Flags flags = 0) override;
    std::shared_ptr<IPrintOperatorUnit> createPrintOperatorUnit(const std::string& text) override;
};
