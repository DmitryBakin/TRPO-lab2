#pragma once
#include "ILanguageFactory.h"
#include <vector>

class JavaClassUnit : public IClassUnit {
public:
    static const std::vector<std::string> ACCESS_MODIFIERS;

    enum AccessModifier { PRIVATE, PROTECTED, PUBLIC};

    explicit JavaClassUnit(const std::string& name);

    void add(std::shared_ptr<IUnit> unit, Flags flags = 0) override;
    std::string compile(unsigned int level = 0) const override;

private:
    std::string m_name;
    std::vector<std::vector<std::shared_ptr<IUnit>>> m_fields;
    std::string generateShift(unsigned int level) const;
};

class JavaMethodUnit : public IMethodUnit {
public:
    enum Modifier { STATIC = 1, FINAL = 2, ABSTRACT = 4};

    JavaMethodUnit(const std::string& name, const std::string& returnType, Flags flags = 0);

    void add(std::shared_ptr<IUnit> unit, Flags flags = 0) override;
    std::string compile(unsigned int level = 0) const override;

private:
    std::string m_name, m_returnType;
    Flags m_flags;
    std::vector<std::shared_ptr<IUnit>> m_body;
    std::string generateShift(unsigned int level) const;
};

class JavaPrintOperatorUnit : public IPrintOperatorUnit {
public:
    explicit JavaPrintOperatorUnit(const std::string& text);

    std::string compile(unsigned int level = 0) const override;

private:
    std::string m_text;
    std::string generateShift(unsigned int level) const;
};

class JavaFactory : public ILanguageFactory {
public:
    std::shared_ptr<IClassUnit> createClassUnit(const std::string& name) override;
    std::shared_ptr<IMethodUnit> createMethodUnit(const std::string& name, const std::string& returnType, Flags flags = 0) override;
    std::shared_ptr<IPrintOperatorUnit> createPrintOperatorUnit(const std::string& text) override;
};

