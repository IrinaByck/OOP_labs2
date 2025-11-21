#pragma once

#include <iostream>//input//output
#include <string>
#include <stdexcept>//
class Decimal {
    public:
    
        Decimal();//пустой массив
        Decimal(size_t n, unsigned char t = 0);//массив из n элементов, со значением t всех элементов
        Decimal(const std::string &t); //массив из символов строки

        Decimal(const Decimal& other); //копия существующего массива
        Decimal(Decimal&& other) noexcept; //конструктор перемещения

        Decimal& operator=(const Decimal& other);        // Оператор присваивания копированием
        Decimal& operator=(Decimal&& other) noexcept;    // Оператор присваивания перемещением
        ~Decimal() noexcept; //очищает память, когда массив уничтожается
        
        Decimal operator+(const Decimal& other) const;
        Decimal operator-(const Decimal& other) const;

        bool operator==(const Decimal& other) const;
        bool operator>(const Decimal& other) const;
        bool operator<(const Decimal& other) const;
        void print(std::ostream& os) const;

private:
    size_t _size;
    unsigned char* _array;
};
