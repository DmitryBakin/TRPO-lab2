#ifndef CSHARPPRINTOPERATORUNIT_H
#define CSHARPPRINTOPERATORUNIT_H

#include "IPrintOperatorUnit.h"

class CSharpPrintOperatorUnit : public IPrintOperatorUnit {
public:
    explicit CSharpPrintOperatorUnit(const std::string& text);

    std::string compile(unsigned int level = 0) const override;

private:
    std::string m_text;
};

#endif // CSHARPPRINTOPERATORUNIT_H
