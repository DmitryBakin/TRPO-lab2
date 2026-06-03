#include "JavaClassUnit.h"

const std::vector<std::string> JavaClassUnit::ACCESS_MODIFIERS = {"private ", "protected ", "public "};

JavaClassUnit::JavaClassUnit(const std::string& name) : m_name(name) {
    m_fields.resize(ACCESS_MODIFIERS.size());
}

void JavaClassUnit::add(std::shared_ptr<Unit> unit, Flags flags) {
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
