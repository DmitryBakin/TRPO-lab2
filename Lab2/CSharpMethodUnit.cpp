#include "CSharpMethodUnit.h"

CSharpMethodUnit::CSharpMethodUnit(const std::string& name, const std::string& returnType, Flags flags)
    : m_name(name), m_returnType(returnType), m_flags(flags) {}

void CSharpMethodUnit::add(std::shared_ptr<Unit> unit) {
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
