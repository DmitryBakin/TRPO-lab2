#include "CppMethodUnit.h"

CppMethodUnit::CppMethodUnit(const std::string& name, const std::string& returnType, Flags flags)
    : m_name(name), m_returnType(returnType), m_flags(flags) {}

void CppMethodUnit::add(std::shared_ptr<Unit> unit) {
    m_body.push_back(unit);
}

std::string CppMethodUnit::compile(unsigned int level) const {
    std::string result = generateShift(level);

    if ((m_flags & STATIC) && (m_flags & VIRTUAL)) {
        throw std::runtime_error("C++: method cannot be both static and virtual");
    }

    if (m_flags & STATIC)
        result += "static ";
    if (m_flags & VIRTUAL)
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
