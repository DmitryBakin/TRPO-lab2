67## Отчёт по лабораторной работе №2

## 1. Постановка задачи
Разработано приложение, которое генерирует исходный код на C++ для простых классов, содержащих методы и операторы печати. Структура построена на базе класса Unit, от которого наследуются ClassUnit, MethodUnit, PrintOperatorUnit. Функция generateProgram() жёстко создаёт код только на C++.

Требование: модернизировать приложение так, чтобы оно могло генерировать код также для C# и Java. Также, необходимо обеспечить расширяемость архитектуры.

## 2. Предлагаемое решение
### 2.1 Общая идея
Использовать паттерн «Абстрактная фабрика» (Abstract Factory). Он позволяет создавать семейства связанных объектов (класс, метод, оператор печати) для каждого целевого языка, не привязывая клиентский код к конкретным классам.

### 2.2. Архитектура решения
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
https://drive.google.com/file/d/1s-lPOXgO5WDjOSd7V-VREDnLNxjaC7Hp/view?usp=drive_link

## 3.Инструкция пользователя

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

## 4. Тестирование

### Тестирование для C++

```
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
```
Вывод программы:
```
class MyClass {
private:
    virtual void methodVirtual() {
        std::cout << "Hello, World!\n" << std::endl;
    }
    void methodConst() const {
    }

protected:
    static void methodStatic() {
    }

public:
    static void methodStaticConst() const {
    }
    void method() {
    }

};
```
### Тестирование для C#
```
#include <QCoreApplication>
#include "iostream"

#include "ILanguageFactory.h"
#include "Cpp.h"
#include "Java.h"
#include "CSharp.h"

int main() {

    auto factory = std::make_shared<CSharpFactory>();

    auto myClass = factory->createClassUnit("MyClass");

    auto methodStatic = factory->createMethodUnit("methodStatic", "void", CSharpMethodUnit::STATIC);

    auto methodVirtual = factory->createMethodUnit("methodVirtual", "void", CSharpMethodUnit::VIRTUAL);
    auto print = factory->createPrintOperatorUnit("Hello, World!\\n");

    methodVirtual->add(print);

    auto methodAbstract = factory->createMethodUnit("methodAbstract", "void", CSharpMethodUnit::ABSTRACT);

    auto methodStaticVirtual = factory->createMethodUnit("methodStaticVirtual", "void", CSharpMethodUnit::STATIC | CSharpMethodUnit::VIRTUAL);

    auto methodStaticAbstract = factory->createMethodUnit("methodStaticVirtual", "void", CSharpMethodUnit::STATIC | CSharpMethodUnit::ABSTRACT);

    auto method = factory->createMethodUnit("method", "void");

    myClass->add(methodAbstract, CppClassUnit::PUBLIC);
    myClass->add(methodVirtual, CppClassUnit::PRIVATE);
    myClass->add(methodStatic, CppClassUnit::PROTECTED);
    myClass->add(methodStaticVirtual, CppClassUnit::PRIVATE);
    myClass->add(method, CppClassUnit::PUBLIC);
    myClass->add(methodStaticAbstract, CppClassUnit::PROTECTED);

    std::cout << myClass->compile();

    return 0;

}
```
Вывод программы:
```
class MyClass
{
    private virtual void methodVirtual() {
        Console.WriteLine("Hello, World!\n");
    }
    private static virtual void methodStaticVirtual() {
    }
    protected static void methodStatic() {
    }
    protected static abstract void methodStaticVirtual();
    public abstract void methodAbstract();
    public void method() {
    }
}
```

### Тестирование для Java
```
#include <QCoreApplication>
#include "iostream"

#include "ILanguageFactory.h"
#include "Cpp.h"
#include "Java.h"
#include "CSharp.h"

int main() {

    auto factory = std::make_shared<JavaFactory>();

    auto myClass = factory->createClassUnit("MyClass");

    auto methodStatic = factory->createMethodUnit("methodStatic", "void", JavaMethodUnit::STATIC);

    auto methodFinal = factory->createMethodUnit("methodFinal", "void", JavaMethodUnit::FINAL);
    auto print = factory->createPrintOperatorUnit("Hello, World!\\n");

    methodFinal->add(print);

    auto methodAbstract = factory->createMethodUnit("methodAbstract", "void", JavaMethodUnit::ABSTRACT);

    auto methodStaticFinal = factory->createMethodUnit("methodStaticFinal", "void", JavaMethodUnit::STATIC | JavaMethodUnit::FINAL);

    auto method = factory->createMethodUnit("method", "void");

    myClass->add(methodAbstract, CppClassUnit::PUBLIC);
    myClass->add(methodFinal, CppClassUnit::PRIVATE);
    myClass->add(methodStatic, CppClassUnit::PROTECTED);
    myClass->add(methodStaticFinal, CppClassUnit::PRIVATE);
    myClass->add(method, CppClassUnit::PUBLIC);

    std::cout << myClass->compile();

    return 0;

}
```
Вывод программы:
```
public class MyClass {
    private final void methodFinal() {
        System.out.println("Hello, World!\n");
    }
    private static final void methodStaticFinal() {
    }
    protected static void methodStatic() {
    }
    public abstract void methodAbstract();
    public void method() {
    }
}
```
