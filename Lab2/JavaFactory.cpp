#include "JavaFactory.h"


std::shared_ptr<IClassUnit> JavaFactory::createClassUnit(const std::string& name)
{
    return std::make_shared<JavaClassUnit>(name);
}

std::shared_ptr<IMethodUnit> JavaFactory::createMethodUnit(const std::string& name, const std::string& returnType, Flags flags)
{
    return std::make_shared<JavaMethodUnit>(name, returnType, flags);
}

std::shared_ptr<IPrintOperatorUnit> JavaFactory::createPrintOperatorUnit(const std::string& text)
{
    return std::make_shared<JavaPrintOperatorUnit>(text);
}
