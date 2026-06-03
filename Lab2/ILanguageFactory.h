#ifndef ILANGUAGEFACTORY_H
#define ILANGUAGEFACTORY_H

#include <string>
#include <memory>

#include "IClassUnit.h"
#include "IMethodUnit.h"
#include "IPrintOperatorUnit.h"

class ILanguageFactory {
public:
    virtual ~ILanguageFactory() = default;
    virtual std::shared_ptr<IClassUnit> createClassUnit(const std::string& name) = 0;
    virtual std::shared_ptr<IMethodUnit> createMethodUnit(const std::string& name, const std::string& returnType, Flags flags = 0) = 0;
    virtual std::shared_ptr<IPrintOperatorUnit> createPrintOperatorUnit(const std::string& text) = 0;
};

#endif // ILANGUAGEFACTORY_H
