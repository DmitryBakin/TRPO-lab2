#ifndef ILANGUAGEFACTORY_H
#define ILANGUAGEFACTORY_H

#include <string>
#include <memory>

using Flags = unsigned int;

class IUnit
{
public:
    virtual ~IUnit() = default;
    virtual std::string compile(unsigned int level = 0) const = 0;
};

class IClassUnit : public IUnit
{
public:
    virtual ~IClassUnit() = default;
    virtual void add(std::shared_ptr<IUnit> unit, Flags flags = 0) = 0;
};

class IMethodUnit : public IUnit
{
public:
    virtual ~IMethodUnit() = default;
    virtual void add(std::shared_ptr<IUnit> unit, Flags flags = 0) = 0;
};

class IPrintOperatorUnit : public IUnit {};


class ILanguageFactory {
public:
    virtual ~ILanguageFactory() = default;
    virtual std::shared_ptr<IClassUnit> createClassUnit(const std::string& name) = 0;
    virtual std::shared_ptr<IMethodUnit> createMethodUnit(const std::string& name, const std::string& returnType, Flags flags = 0) = 0;
    virtual std::shared_ptr<IPrintOperatorUnit> createPrintOperatorUnit(const std::string& text) = 0;
};

#endif // ILANGUAGEFACTORY_H
