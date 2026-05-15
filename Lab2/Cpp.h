#include "ILanguageFactory.h"
#include "MethodUnit.h"
#include "ClassUnit.h"
#include "PrintOperatorUnit.h"

class CppUnit : public ILanguageFactory
{

};

class CppMethodUnit : public IMethodUnit
{

};

class CppClassUnit : public IClassUnit
{

};

class CppPrintOperatorUnit : IPrintOperatorUnit
{

};
