#include <QCoreApplication>
#include "iostream"

#include "ILanguageFactory.h"
#include "cpp.h"
#include "Java.h"

std::string generateProgram(std::shared_ptr<ILanguageFactory> factory)
{
    auto myClass = factory->createClassUnit("MyClass");

    auto method1 = factory->createMethodUnit("testFunc1", "void", 3);
    auto method2 = factory->createMethodUnit("testFunc2", "void", 2);
    auto method3 = factory->createMethodUnit("testFunc3", "void", 4);
    auto method4 = factory->createMethodUnit("testFunc4", "void", 1);

    auto printOp = factory->createPrintOperatorUnit("Hello, world!\\n");
    method4->add(printOp);

    myClass->add(method1, 0);
    myClass->add(method2, 2);
    myClass->add(method3, 4);
    myClass->add(method4, 1);

    return myClass->compile();
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    std::cout << generateProgram(std::make_shared<CppFactory>()) << std::endl;

    std::cout << generateProgram(std::make_shared<JavaFactory>()) << std::endl;

    return a.exec();
}
