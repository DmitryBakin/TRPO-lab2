#include "CSharp.h"

const std::vector<std::string> CSharpClassUnit::ACCESS_MODIFIERS = {
    "private", "protected", "public", "internal"
};

CSharpClassUnit::CSharpClassUnit(const std::string& name) : m_name(name) {
    m_fields.resize(ACCESS_MODIFIERS.size());
}

void CSharpClassUnit::add(std::shared_ptr<Unit> unit, Flags flags) {
    int access = PRIVATE;
    if (flags < m_fields.size()) access = flags;
    m_fields[access].push_back(unit);
}

std::string CSharpClassUnit::compile(unsigned int level) const {
    std::string result;

    result += generateShift(level) + "class " + m_name + "\n";
    result += generateShift(level) + "{\n";

    for (size_t i = 0; i < ACCESS_MODIFIERS.size(); ++i) {
        if (m_fields[i].empty()) continue;

        for (const auto& unit : m_fields[i])
        {
            result += generateShift(level + 1) + ACCESS_MODIFIERS[i] + " ";
            result += unit->compile(level + 1);
        }
    }

    result += generateShift(level) + "}\n";

    return result;
}

CSharpMethodUnit::CSharpMethodUnit(const std::string& name, const std::string& returnType, Flags flags)
    : m_name(name), m_returnType(returnType), m_flags(flags) {}

void CSharpMethodUnit::add(std::shared_ptr<Unit> unit, Flags) {
    m_body.push_back(unit);
}

std::string CSharpMethodUnit::compile(unsigned int level) const {

    std::string result;

    if ((m_flags & VIRTUAL) && (m_flags & ABSTRACT)) {
        throw std::runtime_error("C#: method cannot be both virtual and abstract");
    }

    if (m_flags & STATIC)   result += "static ";
    if (m_flags & VIRTUAL)  result += "virtual ";
    if (m_flags & ABSTRACT) result += "abstract ";

    result += m_returnType + " " + m_name + "()";

    if (m_flags & ABSTRACT) {
        result += ";\n";
    }
    else {
        result += " {\n";
        for (const auto& unit : m_body) {
            result += unit->compile(level + 1);
        }
        result += generateShift(level) + "}\n";
    }
    return result;
}

CSharpPrintOperatorUnit::CSharpPrintOperatorUnit(const std::string& text) : m_text(text) {}

std::string CSharpPrintOperatorUnit::compile(unsigned int level) const {
    return generateShift(level) + "Console.WriteLine(\"" + m_text + "\");\n";
}

std::shared_ptr<IClassUnit> CSharpFactory::createClassUnit(const std::string& name) {
    return std::make_shared<CSharpClassUnit>(name);
}

std::shared_ptr<IMethodUnit> CSharpFactory::createMethodUnit(const std::string& name,
                                                             const std::string& returnType,
                                                             Flags flags) {
    return std::make_shared<CSharpMethodUnit>(name, returnType, flags);
}

std::shared_ptr<IPrintOperatorUnit> CSharpFactory::createPrintOperatorUnit(const std::string& text) {
    return std::make_shared<CSharpPrintOperatorUnit>(text);
}
