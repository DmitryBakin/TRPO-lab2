#include <QCoreApplication>
#include "iostream"

#include "CppFactory.h"
#include "CppClassUnit.h"
#include "CppMethodUnit.h"
#include "CppPrintOperatorUnit.h"

#include "CSharpFactory.h"
#include "CSharpClassUnit.h"
#include "CSharpMethodUnit.h"
#include "CSharpPrintOperatorUnit.h"

#include "JavaFactory.h"
#include "JavaClassUnit.h"
#include "JavaMethodUnit.h"
#include "JavaPrintOperatorUnit.h"

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

    std::cout << "C++:\n" << myClass->compile() << std::endl;



    auto CSfactory = std::make_shared<CSharpFactory>();

    auto CSmyClass = CSfactory->createClassUnit("MyClass");

    auto CSmethodStatic = CSfactory->createMethodUnit("methodStatic", "void", CSharpMethodUnit::STATIC);

    auto CSmethodVirtual = CSfactory->createMethodUnit("methodVirtual", "void", CSharpMethodUnit::VIRTUAL);
    auto CSprint = CSfactory->createPrintOperatorUnit("Hello, World!\\n");

    CSmethodVirtual->add(CSprint);

    auto CSmethodAbstract = CSfactory->createMethodUnit("methodAbstract", "void", CSharpMethodUnit::ABSTRACT);

    auto CSmethodStaticVirtual = CSfactory->createMethodUnit("methodStaticVirtual", "void", CSharpMethodUnit::STATIC | CSharpMethodUnit::VIRTUAL);

    auto CSmethodStaticAbstract = CSfactory->createMethodUnit("methodStaticVirtual", "void", CSharpMethodUnit::STATIC | CSharpMethodUnit::ABSTRACT);

    auto CSmethod = CSfactory->createMethodUnit("method", "void");

    CSmyClass->add(CSmethodAbstract, CSharpClassUnit::PUBLIC);
    CSmyClass->add(CSmethodVirtual, CSharpClassUnit::PRIVATE);
    CSmyClass->add(CSmethodStatic, CSharpClassUnit::PROTECTED);
    CSmyClass->add(CSmethodStaticVirtual, CSharpClassUnit::PRIVATE);
    CSmyClass->add(CSmethod, CSharpClassUnit::PUBLIC);
    CSmyClass->add(CSmethodStaticAbstract, CSharpClassUnit::PROTECTED);

    std::cout << "\nC#:\n" << CSmyClass->compile() << std::endl;



    auto Jfactory = std::make_shared<JavaFactory>();

    auto JmyClass = Jfactory->createClassUnit("MyClass");

    auto JmethodStatic = Jfactory->createMethodUnit("methodStatic", "void", JavaMethodUnit::STATIC);

    auto JmethodFinal = Jfactory->createMethodUnit("methodFinal", "void", JavaMethodUnit::FINAL);
    auto Jprint = Jfactory->createPrintOperatorUnit("Hello, World!\\n");

    JmethodFinal->add(Jprint);

    auto JmethodAbstract = Jfactory->createMethodUnit("methodAbstract", "void", JavaMethodUnit::ABSTRACT);

    auto JmethodStaticFinal = Jfactory->createMethodUnit("methodStaticFinal", "void", JavaMethodUnit::STATIC | JavaMethodUnit::FINAL);

    auto Jmethod = Jfactory->createMethodUnit("method", "void");

    JmyClass->add(JmethodAbstract, JavaClassUnit::PUBLIC);
    JmyClass->add(JmethodFinal, JavaClassUnit::PRIVATE);
    JmyClass->add(JmethodStatic, JavaClassUnit::PROTECTED);
    JmyClass->add(JmethodStaticFinal, JavaClassUnit::PRIVATE);
    JmyClass->add(Jmethod, JavaClassUnit::PUBLIC);

    std::cout << "\nJava:\n" <<JmyClass->compile() << std::endl;

    return 0;

}
