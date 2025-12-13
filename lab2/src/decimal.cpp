#include "../include/decimal.h"//заголовочный файл
//конструктор по умолчанию число 0, память не выделена
Decimal::Decimal() : _size(0), _array(nullptr) {}

//параметризованный конструктор
Decimal::Decimal(size_t n, unsigned char t) {
    _size = n;//количество цифр сохраняю в поле _size
    if (t>9 or t<0){ throw std::invalid_argument("Error");
    }//проверка корректности цифр
    _array = new unsigned char[n];//выделение динамической памяти под массив из n элементов
    for (size_t i = 0; i <= n-1; ++i){ _array[i] = t;//заполняю все n-кол-во ячеек массива цифрами t
    }
}

//копирующий конструктор
Decimal::Decimal(const Decimal& other):_size{other._size} {
    _array = new unsigned char[_size];//выделяю свою память такого же размер
    for (size_t i = 0; i < _size; ++i) {//поэлементно копирую цифры
        _array[i] = other._array[i];
    }
}
//деструктор
Decimal::~Decimal(){
        delete[] _array;//освобождаю память, когда объект уничтожается
}
//конструктор из строки
Decimal::Decimal(const std::string& str){
    if (str == ""){
        throw std::invalid_argument("Error");
    }
    for (char c : str){//каждый символ проверяю
        if (c < '0' or c > '9'){
            throw std::invalid_argument("Error");
        }
    }
    _size = str.length();//длина строки-размер числа и выделяю память
    _array = new unsigned char[_size];
    for (size_t i = 0; i < _size; ++i) {//заполняю массив в обратном порядке
        _array[i] = str[_size - 1 - i] - '0';
    }
}
//конструктор перемещения
Decimal::Decimal (Decimal&& other) noexcept{
    _array = other._array;//принимаю временный объект
    _size = other._size;//краду у other указатель и размер
    other._array = nullptr;
    other._size = 0;
}

//оператор присваивания копированием
Decimal& Decimal::operator=(const Decimal& other) {
    if (this == &other) {
        return *this;//возвращаю ссылку на текущий объект
    }
    
    delete[] _array;//удаляю свои старые данные.
    
    _size = other._size;//выделяю новую память под копию
    _array = new unsigned char[_size];
    
    for (size_t i = 0; i < _size; i++) {
        _array[i] = other._array[i];
    }
    
    return *this;//копирую цифры и возвращаю ссылку на текущий объект
}

//оператор присваивания перемещением
Decimal& Decimal::operator=(Decimal&& other) noexcept {
    if (this == &other) {//проверка на самоприсваивание сравниваю адреса текущий и другой
        return *this;
    }
    
    delete[] _array;
    _array = other._array;//краду данные у other(перенаправляю указатель) память и размер
    _size = other._size;
    other._array = nullptr;
    other._size = 0;
    
    return *this;
}

//оператор сложения
Decimal Decimal::operator+(const Decimal& other) const {
    //определяем максимальный размер из двух чисел
    size_t maxSize = std::max(_size, other._size);
    //результат с запасом на 1 разряд для возможного переноса
    Decimal result(maxSize + 1, 0);
    // Переменная для хранения переноса в старший разряд
    unsigned char carry = 0;
    
    //проходим по всем разрядам от младших к старшим
    for (size_t i = 0; i < maxSize; i++) {
        // Начинаем сумму с переноса от предыдущего разряда
        unsigned char sum = carry;
        //добавляем цифру из первого числа, если она существует
        if (i < _size) sum += _array[i];
        //добавляем цифру из второго числа, если она существует
        if (i < other._size) sum += other._array[i];
        
        //записываем младшую цифру суммы (остаток от деления на 10)
        result._array[i] = sum % 10;
        //вычисляем перенос для следующего разряда (сколько десятков)
        carry = sum / 10;
    }
    
    //если после сложения всех разрядов остался перенос
    if (carry > 0) {
        //записываем перенос в старший разряд
        result._array[maxSize] = carry;
    } else {
        //если переноса нет, корректируем размер (убираем лишний разряд)
        result._size = maxSize;
    }
    
    //возвращаем результат сложения
    return result;
}

//оператор вычитания
Decimal Decimal::operator-(const Decimal& other) const {
    //проверяем, что первое число не меньше второго
    if (*this < other) {
        //если результат будет отрицательным, бросаем исключение
        throw std::invalid_argument("Result would be negative");
    }
    
    //создаем копию первого числа (из него будем вычитать)
    Decimal result(*this);
    //переменная для хранения "заема" из старшего разряда
    int borrow = 0;
    
    //проходим по всем разрядам результата
    for (size_t i = 0; i < result._size; i++) {
        //вычитаем заем из текущей цифры
        int digitDiff = result._array[i] - borrow;
        
        //вычитаем цифру из второго числа, если она существует
        if (i < other._size) {
            digitDiff -= other._array[i];
        }
        
        //если результат отрицательный, занимаем 10 у старшего разряда
        if (digitDiff < 0) {
            digitDiff += 10;
            borrow = 1;  //устанавливаем флаг заема для следующего разряда
        } else {
            borrow = 0;  //заема не было
        }
        
        // Записываем полученную цифру
        result._array[i] = digitDiff;
    }
    
    // Удаляем ведущие нули (например, 00100 -> 100)
    while (result._size > 1 && result._array[result._size - 1] == 0) {
        result._size--;
    }
    
    // Возвращаем результат вычитания
    return result;
}

//оператор сравнения "меньше" (<)
bool Decimal::operator<(const Decimal& other) const {
    // Если у первого числа меньше цифр, оно точно меньше
    if (_size < other._size) return true;
    // Если у первого числа больше цифр, оно точно больше
    if (_size > other._size) return false;
    
    // Если количество цифр одинаковое, сравниваем от старших к младшим
    for (int i = _size - 1; i >= 0; --i) {
        // Если текущая цифра первого числа меньше, первое число меньше
        if (_array[i] < other._array[i]) return true;
        // Если текущая цифра первого числа больше, первое число больше
        if (_array[i] > other._array[i]) return false;
    }
    
    // Если все цифры равны, числа равны (не меньше)
    return false;
}

//оператор сравнения "больше" (>)
bool Decimal::operator>(const Decimal& other) const {
    // Если у первого числа больше цифр, оно точно больше
    if (_size > other._size) return true;
    // Если у первого числа меньше цифр, оно точно меньше
    if (_size < other._size) return false;
    
    // Если количество цифр одинаковое, сравниваем от старших к младшим
    for (int i = _size - 1; i >= 0; --i) {
        // Если текущая цифра первого числа больше, первое число больше
        if (_array[i] > other._array[i]) return true;
        // Если текущая цифра первого числа меньше, первое число меньше
        if (_array[i] < other._array[i]) return false;
    }
    
    // Если все цифры равны, числа равны (не больше)
    return false;
}

//оператор сравнения "равно" (==)
bool Decimal::operator==(const Decimal& other) const {
    //если количество цифр разное, числа точно разные
    if (_size != other._size) return false;
    
    //сравниваем все цифры от младших к старшим
    for (size_t i = 0; i < _size; ++i) {
        //если хотя бы одна цифра отличается, числа разные
        if (_array[i] != other._array[i]) return false;
    }
    
    //все цифры совпали, числа равны
    return true;
}

//метод вывода числа в поток
void Decimal::print(std::ostream& os) const {
    //вывод цифры от старших к младшим
    for (int i = _size - 1; i >= 0; i--) {
        // unsigned char к int для корректного вывода цифры
        os << (int)_array[i];
    }
}
