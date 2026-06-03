#include "CppClassUnit.h"

const std::vector<std::string> CppClassUnit::ACCESS_MODIFIERS = {"private:", "protected:", "public:"};

CppClassUnit::CppClassUnit(const std::string& name) : m_name(name) {
    m_fields.resize(ACCESS_MODIFIERS.size());
}

void CppClassUnit::add(std::shared_ptr<Unit> unit, Flags flags) {
    int access = PRIVATE;
    if (flags < m_fields.size()) access = flags;
    m_fields[access].push_back(unit);
}

std::string CppClassUnit::compile(unsigned int level) const {
    std::string result = generateShift(level) + "class " + m_name + " {\n";
    for (size_t i = 0; i < ACCESS_MODIFIERS.size(); ++i) {
        if (m_fields[i].empty()) continue;
        result += generateShift(level) + ACCESS_MODIFIERS[i] + "\n";
        for (const auto& u : m_fields[i])
            result += u->compile(level + 1);
        result += "\n";
    }
    result += generateShift(level) + "};\n";
    return result;
}
