#ifndef CSHARPFACTORY_H
#define CSHARPFACTORY_H

#include "ILanguageFactory.h"

#include "CSharpClassUnit.h"
#include "CSharpMethodUnit.h"
#include "CSharpPrintOperatorUnit.h"

class CSharpFactory : public ILanguageFactory {
public:
    std::shared_ptr<IClassUnit> createClassUnit(const std::string& name) override;
    std::shared_ptr<IMethodUnit> createMethodUnit(const std::string& name, const std::string& returnType, Flags flags = 0) override;
    std::shared_ptr<IPrintOperatorUnit> createPrintOperatorUnit(const std::string& text) override;
};

#endif // CSHARPFACTORY_H
