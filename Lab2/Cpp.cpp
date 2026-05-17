#include "Cpp.h"

const std::vector<std::string> CppClassUnit::ACCESS_MODIFIERS = {"private:", "protected:", "public:"};

CppClassUnit::CppClassUnit(const std::string& name) : m_name(name) {
    m_fields.resize(ACCESS_MODIFIERS.size());
}

void CppClassUnit::add(std::shared_ptr<IUnit> unit, Flags flags) {
    int access = PRIVATE;
    if (flags < m_fields.size()) access = flags;
    m_fields[access].push_back(unit);
}

std::string CppClassUnit::compile(unsigned int level) const {
    std::string result = generateShift(level) + "class " + m_name + " {\n";
    for (size_t i = 0; i < ACCESS_MODIFIERS.size(); ++i) {
        if (m_fields[i].empty()) continue;
        result += generateShift(level + 1) + ACCESS_MODIFIERS[i] + "\n";
        for (const auto& u : m_fields[i])
            result += u->compile(level + 2);
        result += "\n";
    }
    result += generateShift(level) + "};\n";
    return result;
}

std::string CppClassUnit::generateShift(unsigned int level) const
{
    return std::string(level * 4, ' ');
}

CppMethodUnit::CppMethodUnit(const std::string& name, const std::string& returnType, Flags flags)
    : m_name(name), m_returnType(returnType), m_flags(flags) {}

void CppMethodUnit::add(std::shared_ptr<IUnit> unit, Flags) {
    m_body.push_back(unit);
}

std::string CppMethodUnit::generateShift(unsigned int level) const {
    return std::string(level * 4, ' ');
}

std::string CppMethodUnit::compile(unsigned int level) const {
    std::string result = generateShift(level);

    if (m_flags & STATIC)
        result += "static ";
    else if (m_flags & VIRTUAL)
        result += "virtual ";

    result += m_returnType + " " + m_name + "()";
    if (m_flags & CONST) result += " const";

    result += " {\n";
    for (const auto& unit : m_body) {
        result += unit->compile(level + 1);
    }
    result += generateShift(level) + "}\n";

    return result;
}

CppPrintOperatorUnit::CppPrintOperatorUnit(const std::string& text) : m_text(text) {}


std::string CppPrintOperatorUnit::generateShift(unsigned int level) const {
    return std::string(level * 4, ' ');
}

std::string CppPrintOperatorUnit::compile(unsigned int level) const {
    return generateShift(level) + "std::cout << \"" + m_text + "\" << std::endl;\n";
}

std::shared_ptr<IClassUnit> CppFactory::createClassUnit(const std::string& name)
{
    return std::make_shared<CppClassUnit>(name);
}

std::shared_ptr<IMethodUnit> CppFactory::createMethodUnit(const std::string& name, const std::string& returnType, Flags flags)
{
    return std::make_shared<CppMethodUnit>(name, returnType, flags);
}
std::shared_ptr<IPrintOperatorUnit> CppFactory::createPrintOperatorUnit(const std::string& text)
{
    return std::make_shared<CppPrintOperatorUnit>(text);
}
