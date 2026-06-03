#include "CSharpFactory.h"

std::shared_ptr<IClassUnit> CSharpFactory::createClassUnit(const std::string& name) {
    return std::make_shared<CSharpClassUnit>(name);
}

std::shared_ptr<IMethodUnit> CSharpFactory::createMethodUnit(const std::string& name, const std::string& returnType, Flags flags) {
    return std::make_shared<CSharpMethodUnit>(name, returnType, flags);
}

std::shared_ptr<IPrintOperatorUnit> CSharpFactory::createPrintOperatorUnit(const std::string& text) {
    return std::make_shared<CSharpPrintOperatorUnit>(text);
}
