#pragma once

#include <iostream>
#include <string>
#include <stdexcept>
class Decimal {
    public:
    
        Decimal();
        Decimal(size_t n, unsigned char t = 0);
        Decimal(const std::string &t);

        Decimal(const Decimal& other);
        Decimal(Decimal&& other) noexcept;
 
        Decimal& operator=(const Decimal& other);
        Decimal& operator=(Decimal&& other) noexcept;
        ~Decimal() noexcept;
        
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
