#include "ILanguageFactory.h"
#include "MethodUnit.h"
#include "ClassUnit.h"
#include "PrintOperatorUnit.h"

class JavaUnit : public ILanguageFactory
{

};

class JavaMethodUnit : public IMethodUnit
{

};

class JavaClassUnit : public IClassUnit
{

};

class JavaPrintOperatorUnit : IPrintOperatorUnit
{

};

