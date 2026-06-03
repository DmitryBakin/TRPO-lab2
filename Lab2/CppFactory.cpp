#include "CppFactory.h"

std::shared_ptr<IClassUnit> CppFactory::createClassUnit(const std::string& name)
{
    return std::make_shared<CppClassUnit>(name);
}

std::shared_ptr<IMethodUnit> CppFactory::createMethodUnit(const std::string& name, const std::string& returnType, Flags flags)
{
    return std::make_shared<CppMethodUnit>(name, returnType, flags);
}
std::shared_ptr<IPrintOperatorUnit> CppFactory::createPrintOperatorUnit(const std::string& text)
{
    return std::make_shared<CppPrintOperatorUnit>(text);
}
