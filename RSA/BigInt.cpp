#include"BigInt.h"

int BigInt::_charIntToInt(char c) const {
    return c - '0';
}

std::string BigInt::getNum() const {
    return this->_num;
}

char BigInt::_intToChar(int num) const {
    return num + '0';
}

std::string BigInt::_reverse(const std::string& str) const {
    return std::string(str.rbegin(), str.rend());
}

std::string BigInt::_removeLeadingZeros(const std::string& num) const {
    std::stringstream ss;
    bool valid = false;

    for (int i = 0; i < (int)num.length(); ++i) {
        if (num[i] == '0' && !valid) {
            continue;
        }
        else {
            valid = true;
            ss << num[i];
        }
    }

    if (ss.str().length() == 0) {
        ss << 0;
    }

    return ss.str();
}

void BigInt::_addLeadingZeros(std::string& num, int totalZeros) const {
    std::stringstream ss;

    for (int i = 1; i <= totalZeros; ++i) {
        ss << 0;
    }
    ss << num;

    num = ss.str();
}

void BigInt::_addTrailingZeros(std::string& num, int totalZeros) const {
    std::stringstream ss;

    ss << num;
    for (int i = 1; i <= totalZeros; ++i) {
        ss << 0;
    }

    num = ss.str();
}

bool BigInt::_validate(const std::string& num) {
    for (int i = 0; i < (int)num.length(); ++i) {
        if (i == 0 && num[i] == '-') continue;
        else if (num[i] >= '0' && num[i] <= '9') continue;
        else return false;
    }
    return true;
}

bool BigInt::_isNegative(const std::string& num) {
    return num[0] == '-';
}

std::string BigInt::_absolute(const std::string& num) {
    return num.substr(1, num.length() - 1);
}

BigInt::BigInt() {
    _negative = false;
    _num = "0";
}

BigInt::BigInt(const std::string& num) {
    if (!_validate(num)) {
        throw std::runtime_error("Invalid integer format");
    }

    _negative = _isNegative(num);

    _num = (_negative) ? _removeLeadingZeros(_absolute(num)) : _removeLeadingZeros(num);
}

BigInt::BigInt(const std::string& num, bool negative) {
    _num = _removeLeadingZeros(num);
    _negative = negative;
}

BigInt::BigInt(const BigInt& num) {
    _num = num._num;
    _negative = num._negative;
}

void BigInt::setNegative(bool negativity) {
    _negative = negativity;
}

void BigInt::operator=(const BigInt& num) {
    _num = num._num;
    _negative = num._negative;
}

BigInt::~BigInt() {
}

bool BigInt::isNegative() const {
    return _negative;
}

char& BigInt::operator[](const int index) {
    if (index < 0 || index >(int)_num.length()) {
        throw std::runtime_error("Index out of bound");
    }
    return _num[index];
}

bool BigInt::operator<(const BigInt& num) const {

    if (num.isNegative() != isNegative()) {
        return isNegative();
    }

    if (_num.length() != num._num.length()) {
        return (isNegative()) ? (_num.length() > num._num.length())
            : (_num.length() < num._num.length());
    }

    return isNegative() ? (_num > num._num) : (_num < num._num);
}

bool BigInt::operator<(const std::string& num) const {
    return *this < BigInt(num);
}

bool BigInt::operator>(const BigInt& num) const {
    return !(*this <= num);
}

bool BigInt::operator>(const std::string& num) const {
    return *this > BigInt(num);
}

bool BigInt::operator==(const BigInt& num) const {
    return (_num == num._num) && (_negative == num._negative);
}

bool BigInt::operator==(const std::string& num) const {
    return *this == BigInt(num);
}

bool BigInt::operator!=(const BigInt& num) const {
    return !(*this == num);
}

bool BigInt::operator!=(const std::string& num) const {
    return *this != BigInt(num);
}

bool BigInt::operator<=(const BigInt& num) const {
    return (*this == num || *this < num);
}

bool BigInt::operator<=(const std::string& num) const {
    return *this <= BigInt(num);
}

bool BigInt::operator>=(const BigInt& num) const {
    return (*this == num || *this > num);
}

bool BigInt::operator>=(const std::string& num) const {
    return *this >= num;
}

BigInt BigInt::operator+(const BigInt& num) const {

    if (isNegative() != num.isNegative()) {
        return isNegative() ? num - BigInt(_num, !isNegative()) : *this - BigInt(num._num, !num.isNegative());
    }

    std::stringstream ss;

    std::string firstNum = _num;
    std::string secondNum = num._num;

    if ((int)_num.length() > (int)secondNum.length()) {
        _addLeadingZeros(secondNum, (int)(firstNum.length() - secondNum.length()));
    }
    else if ((int)_num.length() < (int)secondNum.length()) {
        _addLeadingZeros(firstNum, (int)(secondNum.length() - firstNum.length()));
    }

    int carry = 0;
    for (int i = (int)firstNum.length() - 1; i >= 0; --i) {
        int currentSum = _charIntToInt(firstNum[i]) + _charIntToInt(secondNum[i]) + carry;

        ss << currentSum % 10;
        carry = currentSum / 10;
    }

    if (carry > 0) {
        while (carry > 0) {
            ss << carry % 10;
            carry /= 10;
        }
    }

    return BigInt(_reverse(ss.str()), isNegative());
}

BigInt BigInt::operator+(const std::string& num) const {
    return *this + BigInt(num);
}

void BigInt::operator+=(const BigInt& num) {
    *this = *this + num;
}

void BigInt::operator+=(const std::string& num) {
    *this += BigInt(num);
}

BigInt BigInt::operator-(const BigInt& num) const {

    if (isNegative() != num.isNegative()) {
        BigInt result = BigInt(_num) + BigInt(num._num);
        result.setNegative(isNegative());
        return result;
    }

    if (isNegative() && num.isNegative()) {
        return BigInt(num._num) - BigInt(_num);
    }

    if (num == "0") {
        return *this;
    }

    if (_num == "0" && num != "0") {
        BigInt result = num;
        result.setNegative(!num.isNegative());
        return result;
    }

    std::stringstream ss;

    std::string firstNum = _num;
    std::string secondNum = num._num;

    if ((int)_num.length() > (int)secondNum.length()) {
        _addLeadingZeros(secondNum, (int)(firstNum.length() - secondNum.length()));
    }
    else if ((int)_num.length() < (int)secondNum.length()) {
        _addLeadingZeros(firstNum, (int)(secondNum.length() - firstNum.length()));
    }

    if (*this < num) {
        std::swap(firstNum, secondNum);
    }

    firstNum = _reverse(firstNum);
    secondNum = _reverse(secondNum);

    int carry = 0;

    for (int i = 0; i < (int)firstNum.length(); i++) {
        int sub = _charIntToInt(firstNum[i]) - _charIntToInt(secondNum[i]) - carry;
        if (sub < 0) {
            sub += 10;
            carry = 1;
        }
        else {
            carry = 0;
        }
        ss << sub;
    }

    return BigInt(_reverse(ss.str()), (*this < num));
}

BigInt BigInt::operator-(const std::string& num) const {
    return *this - BigInt(num);
}

void BigInt::operator-=(const BigInt& num) {
    *this = *this - num;
}

void BigInt::operator-=(const std::string& num) {
    *this -= BigInt(num);
}

BigInt BigInt::operator*(const BigInt& num) const {
    std::stringstream ss;

    std::string firstNum = _num;
    std::string secondNum = num._num;

    if (firstNum == "0" || secondNum == "0") {
        return BigInt("0");
    }

    BigInt result;

    int carry = 0;
    for (int i = (int)secondNum.length() - 1; i >= 0; --i) {
        if (secondNum[i] == '0') continue;
        for (int j = (int)firstNum.length() - 1; j >= 0; --j) {
            int current_prod = _charIntToInt(firstNum[j]) * _charIntToInt(secondNum[i]) + carry;

            ss << current_prod % 10;
            carry = current_prod / 10;
        }

        while (carry > 0) {
            ss << carry % 10;
            carry /= 10;
        }

        std::string lineResult = _reverse(ss.str());
        _addTrailingZeros(lineResult, secondNum.length() - i - 1);

        result += BigInt(lineResult); ss.str("");
    }
    result.setNegative(isNegative() != num.isNegative());

    return result;
}

BigInt BigInt::operator*(const std::string& num) const {
    return *this * BigInt(num);
}

void BigInt::operator*=(const BigInt& num) {
    *this = *this * num;
}

void BigInt::operator*=(const std::string& num) {
    *this *= BigInt(num);
}

std::tuple<BigInt, BigInt> BigInt::operator/(const BigInt& num) const {
    BigInt zero("0");

    if (num == zero) {
        throw std::runtime_error("Zero divison");
    }

    std::vector<BigInt> kb(11, zero);

    for (int i = 1; i <= 10; ++i) {
        kb[i] = kb[i - 1] + num;
    }

    BigInt c(zero);
    std::string hold = "";

    for (int i = 0; i < (int)_num.length(); ++i) {
        hold = hold + _num[i];

        int k = 0;
        for (; kb[k] <= hold; ++k);

        c._num += _intToChar(k - 1);

        hold = (BigInt(hold) - kb[k - 1])._num;
    }

    c._num = _removeLeadingZeros(c._num);

    return std::make_tuple(BigInt(c), BigInt(hold));
}

std::tuple<BigInt, BigInt> BigInt::operator/(const std::string& num) const {
    return *this / BigInt(num);
}

void BigInt::operator/=(const BigInt& num) {
    *this = std::get<0>(*this / num);
}

void BigInt::operator/=(const std::string& num) {
    *this /= BigInt(num);
}

BigInt BigInt::operator%(const BigInt& base) const {
    auto result = *this / base;

    if (*this < "0") {
        return base - std::get<1>(result);
    }

    return std::get<1>(*this / base);
}

BigInt BigInt::operator%(const std::string& base) const {
    return *this % BigInt(base);
}

void BigInt::operator%=(const BigInt& num) {
    // Goes brrr
    *this = *this % num;
}

BigInt BigInt::max(const BigInt& a, const BigInt& b) {
    return (a > b) ? a : b;
}

BigInt BigInt::modularAddition(const BigInt& a, const BigInt& b, const BigInt& m) {
    BigInt zero("0");

    if (m <= zero) {
        throw std::runtime_error("Invalid modular base");
    }

    BigInt first = (a >= zero) ? a : (m - a);
    BigInt second = (b >= zero) ? b : (m - b);
    return ((first % m) + (second % m)) % m;
}

BigInt BigInt::modularMultiplication(const BigInt& a, const BigInt& b, const BigInt& m) {
    BigInt zero("0");

    if (m <= zero) {
        throw std::runtime_error("Invalid modular base");
    }

    BigInt first = (a >= zero) ? a : m - a;
    BigInt second = (b >= zero) ? b : m - b;
    return ((first % m) * (second % m)) % m;
}

BigInt BigInt::GCD(BigInt a, BigInt b) {
    BigInt c = a % b;
    while (c > "0") {
        a = b; b = c; c = a % b;
    }
    return b;
}

std::tuple<BigInt, BigInt, BigInt> BigInt::Bezout(const BigInt& a, const BigInt& b) {
    if (a == "0") {
        return std::tuple<BigInt, BigInt, BigInt>{b, BigInt("0"), BigInt("1")};
    }

    auto recursiveResult = Bezout(b % a, a);

    std::tuple<BigInt, BigInt, BigInt> result{
        std::get<0>(recursiveResult),
        std::get<2>(recursiveResult) - std::get<0>(b / a) * std::get<1>(recursiveResult),
        std::get<1>(recursiveResult)
    };

    return result;
}

BigInt BigInt::inverseModulo(const BigInt& a, const BigInt& m) {
    auto res = Bezout(a, m);

    if (std::get<0>(res) != "1") {
        throw std::runtime_error("Inverse modulo doesn't exist");
    }

    return std::get<1>(res) % m;
}

std::istream& operator>>(std::istream& in, BigInt& num) {
    std::string s; in >> s;
    num = BigInt(s);
    return in;
}

std::ostream& operator<<(std::ostream& out, const BigInt& num) {
    if (num.isNegative()) {
        out << '-';
    }
    out << num._num;
    return out;
}

std::ostream& operator<<(std::ostream& out, const std::tuple<BigInt, BigInt, BigInt>& numVector) {
    out << std::get<0>(numVector);
    out << ' ';
    out << std::get<1>(numVector);
    out << ' ';
    out << std::get<2>(numVector);
    out << ' ';
    return out;
}
BigInt BigInt::modularExponentiation(const BigInt& base, const BigInt& exponent, const BigInt& modulo) const {
    BigInt result = 1;
    BigInt x = base % modulo;
    BigInt e = exponent;
    while (e > BigInt("0")) {
        if (e % BigInt("2") == BigInt("1")) result = (result * x) % modulo;
        x = (x * x) % modulo;
        e /= BigInt("2");
    }
    return result;
}
bool BigInt::isPrime() const {

    if (*this == BigInt("0") || *this == BigInt("1")) return false;
    if (*this % BigInt("2") == BigInt("0") && *this != BigInt("2")) return false;

    BigInt d = *this - BigInt("1");
    int s = 0;
    while (d % BigInt("2") == BigInt("0")) {
        d /= BigInt("2");
        s++;
    }

    mt19937 rng;
    rng.seed(random_device()());
    BigInt lowerLimit("2");
    BigInt upperLimit = *this - BigInt("2");
    uniform_int_distribution<unsigned long long int> dist(lowerLimit.toInt(), upperLimit.toInt());
    for (int i = 0; i < 20; i++) {
        BigInt a = dist(rng);
        BigInt x = modularExponentiation(a, d, *this);
        if (x == BigInt("1") || x == *this - BigInt("1")) continue;
        for (int j = 0; j < s - 1; j++) {
            x = x * x % *this;
            if (x == *this - BigInt("1")) break;
        }
        if (x != *this - BigInt("1")) return false;
    }
    return true;
}
int BigInt::toInt() const {
    int result = 0;
    for (int i = 0; i < _num.size(); i++) {
        result = result * 10 + _charIntToInt(_num[i]);
    }
    return _negative ? -result : result;

}

