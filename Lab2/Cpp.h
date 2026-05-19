#pragma once
#include "ILanguageFactory.h"
#include <vector>

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

class CppMethodUnit : public IMethodUnit
{
public:
    enum Modifier { STATIC = 1, CONST = 1 << 1, VIRTUAL = 1 << 2 };

    CppMethodUnit(const std::string& name, const std::string& returnType, Flags flags);

    void add(std::shared_ptr<Unit> unit, Flags flags = 0) override;
    std::string compile(unsigned int level = 0) const override;

private:

    std::string m_name, m_returnType;
    Flags m_flags;
    std::vector<std::shared_ptr<Unit>> m_body;
};

class CppPrintOperatorUnit : public IPrintOperatorUnit
{
public:

    explicit CppPrintOperatorUnit(const std::string& text);

    std::string compile(unsigned int level = 0) const override;

private:
    std::string m_text;
};

class CppFactory : public ILanguageFactory
{
    std::shared_ptr<IClassUnit> createClassUnit(const std::string& name) override;
    std::shared_ptr<IMethodUnit> createMethodUnit(const std::string& name, const std::string& returnType, Flags flags = 0) override;
    std::shared_ptr<IPrintOperatorUnit> createPrintOperatorUnit(const std::string& text) override;
};
