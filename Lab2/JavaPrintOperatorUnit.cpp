#include "JavaPrintOperatorUnit.h"

JavaPrintOperatorUnit::JavaPrintOperatorUnit(const std::string& text) : m_text(text) {}

std::string JavaPrintOperatorUnit::compile(unsigned int level) const
{
    return generateShift(level) + "System.out.println(\"" + m_text + "\");\n";
}
