#include "Java.h"


const std::vector<std::string> JavaClassUnit::ACCESS_MODIFIERS = {"private ", "protected ", "public "};

JavaClassUnit::JavaClassUnit(const std::string& name) : m_name(name) {
    m_fields.resize(ACCESS_MODIFIERS.size());
}

void JavaClassUnit::add(std::shared_ptr<IUnit> unit, Flags flags) {
    int access = PRIVATE;
    if (flags < m_fields.size()) access = flags;
    m_fields[access].push_back(unit);
}

std::string JavaClassUnit::compile(unsigned int level) const {
    std::string result;

    result += generateShift(level) + "public class " + m_name + " {\n";

    for (size_t i = 0; i < m_fields.size(); ++i) {
        if (m_fields[i].empty()) continue;

        for (const auto& unit : m_fields[i])
        {
            result += generateShift(level + 1) + ACCESS_MODIFIERS[i];
            result += unit->compile(level + 1);
        }
    }

    result += generateShift(level) + "}\n";
    return result;
}

std::string JavaClassUnit::generateShift(unsigned int level) const {
    return std::string(level * 4, ' ');
}

JavaMethodUnit::JavaMethodUnit(const std::string& name, const std::string& returnType, Flags flags)
    : m_name(name), m_returnType(returnType), m_flags(flags) {}

void JavaMethodUnit::add(std::shared_ptr<IUnit> unit, Flags) {
    m_body.push_back(unit);
}

std::string JavaMethodUnit::compile(unsigned int level) const {
    std::string result;

    if (m_flags & ABSTRACT)
        result += "abstract ";
    else if(m_flags & STATIC && m_flags & FINAL)
        result += "static final ";
    else if(m_flags & STATIC)
        result += "static ";
    else if(m_flags & FINAL)
        result += "final ";

    result += m_returnType + " " + m_name + "()";

    if (m_flags & ABSTRACT) {
        result += ";\n";
        return result;
    }

    result += " {\n";
    for (const auto& unit : m_body) {
        result += unit->compile(level + 1);
    }
    result += generateShift(level) + "}\n";

    return result;
}

std::string JavaMethodUnit::generateShift(unsigned int level) const
{
    return std::string(level * 4, ' ');
}

JavaPrintOperatorUnit::JavaPrintOperatorUnit(const std::string& text) : m_text(text) {}

std::string JavaPrintOperatorUnit::compile(unsigned int level) const
{
    return generateShift(level) + "System.out.println(\"" + m_text + "\");\n";
}

std::string JavaPrintOperatorUnit::generateShift(unsigned int level) const
{
    return std::string(level * 4, ' ');
}

std::shared_ptr<IClassUnit> JavaFactory::createClassUnit(const std::string& name)
{
    return std::make_shared<JavaClassUnit>(name);
}

std::shared_ptr<IMethodUnit> JavaFactory::createMethodUnit(const std::string& name, const std::string& returnType, Flags flags)
{
    return std::make_shared<JavaMethodUnit>(name, returnType, flags);
}

std::shared_ptr<IPrintOperatorUnit> JavaFactory::createPrintOperatorUnit(const std::string& text)
{
    return std::make_shared<JavaPrintOperatorUnit>(text);
}
