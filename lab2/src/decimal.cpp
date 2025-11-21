#include "../include/decimal.h"
//конструктор по умолчанию
Decimal::Decimal() : _size(0), _array(nullptr) {}

//параметризованный конструктор
Decimal::Decimal(size_t n, unsigned char t) {
    _size = n;
    if (t>9 or t<0){ throw std::invalid_argument("Error");
    }
    _array = new unsigned char[n];
    for (size_t i = 0; i <= n-1; ++i){ _array[i] = t;
    }
}

//копирующий конструктор
Decimal::Decimal(const Decimal& other):_size{other._size} {
    _array = new unsigned char[_size];
    for (size_t i = 0; i < _size; ++i) {
        _array[i] = other._array[i];
    }
}
//деструктор
Decimal::~Decimal(){
        delete[] _array;
}
//конструктор из строки
Decimal::Decimal(const std::string& str){
    if (str == ""){
        throw std::invalid_argument("Error");
    }
    for (char c : str){
        if (c < '0' or c > '9'){
            throw std::invalid_argument("Error");
        }
    }
    _size = str.length();
    _array = new unsigned char[_size];
    for (size_t i = 0; i < _size; ++i) {
        _array[i] = str[_size - 1 - i] - '0';
    }
}
//конструктор перемещения
Decimal::Decimal (Decimal&& other) noexcept{
    _array = other._array;
    _size = other._size;
    other._array = nullptr;
    other._size = 0;
}

//оператор присваивания копированием
Decimal& Decimal::operator=(const Decimal& other) {
    if (this == &other) {
        return *this;
    }
    
    delete[] _array;
    
    _size = other._size;
    _array = new unsigned char[_size];
    
    for (size_t i = 0; i < _size; i++) {
        _array[i] = other._array[i];
    }
    
    return *this;
}

//оператор присваивания перемещением
Decimal& Decimal::operator=(Decimal&& other) noexcept {
    if (this == &other) {
        return *this;
    }
    
    delete[] _array;
    _array = other._array;
    _size = other._size;
    other._array = nullptr;
    other._size = 0;
    
    return *this;
}

//оператор сложения
Decimal Decimal::operator+(const Decimal& other) const {
    size_t maxSize = std::max(_size, other._size);
    Decimal result(maxSize + 1, 0);
    unsigned char carry = 0;
    for (size_t i = 0; i < maxSize; i++) {
        unsigned char sum = carry;
        if (i < _size) sum += _array[i];
        if (i < other._size) sum += other._array[i];
        
        result._array[i] = sum % 10;
        carry = sum / 10;
    }
    if (carry > 0) {
        result._array[maxSize] = carry;
    } else {
        result._size = maxSize;
    }
    return result;
}

//оператор вычитания
Decimal Decimal::operator-(const Decimal& other) const {
    if (*this < other) {
        throw std::invalid_argument("Result would be negative");
    }
    Decimal result(*this);
    int borrow = 0;
    for (size_t i = 0; i < result._size; i++) {
        int digitDiff = result._array[i] - borrow;
        if (i < other._size) {
            digitDiff -= other._array[i];
        }
        if (digitDiff < 0) {
            digitDiff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        result._array[i] = digitDiff;
    }
    while (result._size > 1 && result._array[result._size - 1] == 0) {
        result._size--;
    }
    return result;
}

//оператор сранения <
bool Decimal::operator<(const Decimal& other) const {
    if (_size < other._size) return true;
    if (_size > other._size) return false;
    for (int i = _size - 1; i >= 0; --i) {
        if (_array[i] < other._array[i]) return true;
        if (_array[i] > other._array[i]) return false;
    }
    return false;
}

//оператор сравнения >
bool Decimal::operator>(const Decimal& other) const {
    if (_size > other._size) return true;
    if (_size < other._size) return false;
    for (int i = _size - 1; i >= 0; --i) {
        if (_array[i] > other._array[i]) return true;
        if (_array[i] < other._array[i]) return false;
    }
    return false;
}

//оператор сравнения ==
bool Decimal::operator==(const Decimal& other) const {
    if (_size != other._size) return false;
    for (size_t i = 0; i < _size; ++i) {
        if (_array[i] != other._array[i]) return false;
    }
    return true;
}

//метод print
void Decimal::print(std::ostream& os) const {
    for (int i = _size - 1; i >= 0; i--) {
        os << (int)_array[i];
    }
}
