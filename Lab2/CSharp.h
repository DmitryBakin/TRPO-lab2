#include "ILanguageFactory.h"
#include "MethodUnit.h"
#include "ClassUnit.h"
#include "PrintOperatorUnit.h"

class CSharpUnit : public ILanguageFactory
{

};

class CSharpMethodUnit : public IMethodUnit
{

};

class CSharpClassUnit : public IClassUnit
{

};

class CSharpPrintOperatorUnit : IPrintOperatorUnit
{

};
