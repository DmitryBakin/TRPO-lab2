#ifndef ILANGUAGEFACTORY_H
#define ILANGUAGEFACTORY_H

#include <string>
#include <memory>

using Flags = unsigned int;

class Unit
{
public:
    virtual ~Unit() = default;
    virtual std::string compile(unsigned int level = 0) const = 0;

protected:
    std::string generateShift(unsigned int level) const;
};

class IClassUnit : public Unit
{
public:
    virtual ~IClassUnit() = default;
    virtual void add(std::shared_ptr<Unit> unit, Flags flags = 0) = 0;
};

class IMethodUnit : public Unit
{
public:
    virtual ~IMethodUnit() = default;
    virtual void add(std::shared_ptr<Unit> unit, Flags flags = 0) = 0;
};

class IPrintOperatorUnit : public Unit {};


class ILanguageFactory {
public:
    virtual ~ILanguageFactory() = default;
    virtual std::shared_ptr<IClassUnit> createClassUnit(const std::string& name) = 0;
    virtual std::shared_ptr<IMethodUnit> createMethodUnit(const std::string& name, const std::string& returnType, Flags flags = 0) = 0;
    virtual std::shared_ptr<IPrintOperatorUnit> createPrintOperatorUnit(const std::string& text) = 0;
};

#endif // ILANGUAGEFACTORY_H
