##Отчёт по лабораторной работе №2

##1. Постановка задачи
Разработано приложение, которое генерирует исходный код на C++ для простых классов, содержащих методы и операторы печати. Структура построена на базе класса Unit, от которого наследуются ClassUnit, MethodUnit, PrintOperatorUnit. Функция generateProgram() жёстко создаёт код только на C++.

Требование: модернизировать приложение так, чтобы оно могло генерировать код также для C# и Java. Также, необходимо обеспечить расширяемость архитектуры.

##2. Предлагаемое решение
###2.1 Общая идея
Использовать паттерн «Абстрактная фабрика» (Abstract Factory). Он позволяет создавать семейства связанных объектов (класс, метод, оператор печати) для каждого целевого языка, не привязывая клиентский код к конкретным классам.

###2.2. Архитектура решения
Введены следующие абстрактные сущности (интерфейсы):

Unit – базовый класс для всех генерируемых элементов, содержит чисто виртуальный метод compile() и вспомогательную функцию generateShift() для отступов.

IClassUnit, IMethodUnit, IPrintOperatorUnit – интерфейсы, наследующие от Unit, описывающие поведение классов, методов и операторов печати соответственно.

ILanguageFactory – абстрактная фабрика, объявляющая методы createClassUnit(), createMethodUnit(), createPrintOperatorUnit().

Конкретные реализации для каждого языка:

C++: классы CppClassUnit, CppMethodUnit, CppPrintOperatorUnit и фабрика CppFactory.

C#: классы CSharpClassUnit, CSharpMethodUnit, CSharpPrintOperatorUnit и фабрика CSharpFactory.

Java: классы JavaClassUnit, JavaMethodUnit, JavaPrintOperatorUnit и фабрика JavaFactory.

Клиентская функция generateProgram() принимает shared_ptr<ILanguageFactory> и через неё создаёт все необходимые элементы, не зная их конкретных типов.

UML-диаграмма
https://drive.google.com/file/d/1wv8_hEGs6u-Y7TlTek0WuXtc2JfNX_bF/view

##3.Инструкция пользователя

Пользователь выбирает нужный язык, создавая соответствующую фабрику.
```
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

    // Создаем void метод с оператором печати
    auto method2 = factory->createMethodUnit("test_2", "void");
    auto print = factory->createPrintOperatorUnit("Hello, World!\\n");

    method2->add(print);

    // Создаем int метод с модификатором static
    auto method3 = factory->createMethodUnit("test_3", "int", CppMethodUnit::STATIC);


    // Добавляем методы в класс с разными модификаторами доступа
    myClass->add(method1, CppClassUnit::PUBLIC);
    myClass->add(method2, CppClassUnit::PRIVATE);
    myClass->add(method3, CppClassUnit::PROTECTED);

    std::cout << myClass->compile();

    return 0;

}
```

Вывод программы:
```
class MyClass {
    private:
        void test_2() {
            std::cout << "Hello, World!\n" << std::endl;
        }

    protected:
        static int test_3() {
        }

    public:
        void test_1() {
        }

};
```