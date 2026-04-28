#pragma once
#include "Unit.h"
#include <string>

class PrintOperatorUnit : public Unit {
public:
    explicit PrintOperatorUnit(const std::string& text) : m_text(text) { }
    std::string compile(unsigned int level = 0) const override {
        return generateShift(level) + "printf( \"" + m_text + "\" );\n";
    }
private:
    std::string m_text;
};
