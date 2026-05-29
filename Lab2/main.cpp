#include <QCoreApplication>
#include "iostream"

#include "ILanguageFactory.h"
#include "Cpp.h"
#include "Java.h"
#include "CSharp.h"

int main() {

    // Создаем фабрику для C++
    auto factory = std::make_shared<CppFactory>();

    // Создаем класс с именем MyClass
    auto myClass = factory->createClassUnit("MyClass");

    // Создаем void метод без модификаторов
    auto method1 = factory->createMethodUnit("test_1", "void");

    // Создаем метод с оператором печати
    auto method2 = factory->createMethodUnit("test_2", "void");
    auto print = factory->createPrintOperatorUnit("Hello, World!\\n");

    method2->add(print);

    // Создаем публичный метод
    auto method3 = factory->createMethodUnit("test_3", "int", CppMethodUnit::STATIC);


    // Добавляем методы в класс с разными модификаторами доступа
    myClass->add(method1, CppClassUnit::PUBLIC);
    myClass->add(method2, CppClassUnit::PRIVATE);
    myClass->add(method3, CppClassUnit::PROTECTED);

    std::cout << myClass->compile();

    return 0;

}
