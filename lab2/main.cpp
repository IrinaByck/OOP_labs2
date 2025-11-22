#include "include/decimal.h"

int main()
{
    std::cout << std::boolalpha;
    std::string num1, num2;
    char op;
    std::cout << "Введите первое число (в десятиричной системе): ";
    std::cin >> num1;
    std::cout << "Введите второе число (в десятиричной системе): ";
    std::cin >> num2;
    std::cout << "Введите операцию из [+,-,>,<,==]: ";
    std::cin >> op;

   Decimal first(num1), second(num2);
    std::cout << "\nОтвет: ";
    switch (op) {
    case '+': {
        Decimal sum = first + second;
        sum.print(std::cout);
        break;

    }

    case '-': {
        Decimal diff = first - second;
        diff.print(std::cout);
        break;

    }

    case '=': {
        std::cout << (first == second);
        break;
    }

    case '<': {
        std::cout << (first < second);
        break;
    }

    case '>': {
        std::cout << (first > second);
        break;

    }

    default: {
        std::cerr << "Ошибка: недопустимая операция.\n";
        break;
    }

    }
    std::cout << '\n';
    return 0;
}
