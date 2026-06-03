#ifndef JAVAPRINTOPERATORUNIT_H
#define JAVAPRINTOPERATORUNIT_H

#include "IPrintOperatorUnit.h"

class JavaPrintOperatorUnit : public IPrintOperatorUnit {
public:
    explicit JavaPrintOperatorUnit(const std::string& text);

    std::string compile(unsigned int level = 0) const override;

private:
    std::string m_text;
};


#endif // JAVAPRINTOPERATORUNIT_H
