#include <QCoreApplication>
#include "iostream"

#include "ILanguageFactory.h"
#include "Cpp.h"
#include "Java.h"
#include "CSharp.h"

int main() {

    auto factory = std::make_shared<CppFactory>();

    auto myClass = factory->createClassUnit("MyClass");

    auto methodStaticConst = factory->createMethodUnit("methodStaticConst", "void", CppMethodUnit::STATIC | CppMethodUnit::CONST);

    auto methodVirtual = factory->createMethodUnit("methodVirtual", "void", CppMethodUnit::VIRTUAL);
    auto print = factory->createPrintOperatorUnit("Hello, World!\\n");

    methodVirtual->add(print);

    auto methodStatic = factory->createMethodUnit("methodStatic", "void", CppMethodUnit::STATIC);

    auto methodConst = factory->createMethodUnit("methodConst", "void", CppMethodUnit::CONST);

    auto method = factory->createMethodUnit("method", "void");

    myClass->add(methodStaticConst, CppClassUnit::PUBLIC);
    myClass->add(methodVirtual, CppClassUnit::PRIVATE);
    myClass->add(methodStatic, CppClassUnit::PROTECTED);
    myClass->add(methodConst, CppClassUnit::PRIVATE);
    myClass->add(method, CppClassUnit::PUBLIC);

    std::cout << myClass->compile();

    return 0;

}
