#pragma once

#include <iostream>//input//output
#include <string>
#include <stdexcept>//исключения
class Decimal {
    public:
    
        Decimal();//конструктор по умолчанию
        Decimal(size_t n, unsigned char t = 0);//параметризованный конструктор-массив из n элементов, со значением t всех элементов
        Decimal(const std::string &t); //конструктор из строки(ссылка на существующую строку)

        Decimal(const Decimal& other); //копия существующего массива(ссылка на существующий объект Decimal)
        Decimal(Decimal&& other) noexcept; //конструктор перемещения
 
        Decimal& operator=(const Decimal& other);// Оператор присваивания копированием
        Decimal& operator=(Decimal&& other) noexcept;// Оператор присваивания перемещением
        ~Decimal() noexcept; //очищает динамическую память, когда массив уничтожается
        
        Decimal operator+(const Decimal& other) const;//арифметические операторы
        Decimal operator-(const Decimal& other) const;

        bool operator==(const Decimal& other) const;//операторы сравнения
        bool operator>(const Decimal& other) const;
        bool operator<(const Decimal& other) const;
        void print(std::ostream& os) const;//метод вывода числа в поток

private:
    size_t _size;//количество цифр в числе
    unsigned char* _array;//указатель на массив в динамической памяти, где каждая ячейка хранит цифру типа unsigned char
};
