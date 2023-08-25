#ifndef BIGINT_H
#define BIGINT_H

#include<iostream>
#include<string>
#include<sstream>
#include<vector>
#include<tuple>
#include<random>
#include<fstream>
using namespace std;

class BigInt {
private:
    std::string _num;
    bool _negative;
private:
    int _charIntToInt(char) const;
    char _intToChar(int) const;
    std::string _reverse(const std::string&) const;
    std::string _removeLeadingZeros(const std::string&) const;
    void _addLeadingZeros(std::string&, int) const;
    void _addTrailingZeros(std::string&, int) const;
    bool _validate(const std::string&);
    bool _isNegative(const std::string&);
    std::string _absolute(const std::string&);
public:
    BigInt();
    BigInt(const std::string&);
    BigInt(const std::string&, bool);
    BigInt(const BigInt&);
    void operator=(const BigInt&);
    BigInt(int value) {
        std::stringstream ss;
        ss << value;
        _num = ss.str();
    }
    ~BigInt();
public:
    bool isNegative() const;
public:
    std::string getNum() const;
    void setNegative(bool);
    char& operator[](const int);
    bool operator<(const BigInt&) const;
    bool operator<(const std::string&) const;
    bool operator>(const BigInt&) const;
    bool operator>(const std::string&) const;
    bool operator==(const BigInt&) const;
    bool operator==(const std::string&) const;
    bool operator!=(const BigInt&) const;
    bool operator!=(const std::string&) const;
    bool operator<=(const BigInt&) const;
    bool operator<=(const std::string&) const;
    bool operator>=(const BigInt&) const;
    bool operator>=(const std::string&) const;
    BigInt operator+(const BigInt&) const;
    BigInt operator+(const std::string&) const;
    void operator+=(const BigInt&);
    void operator+=(const std::string&);
    BigInt operator-(const BigInt&) const;
    BigInt operator-(const std::string&) const;
    void operator-=(const BigInt&);
    void operator-=(const std::string&);
    BigInt operator*(const BigInt&) const;
    BigInt operator*(const std::string&) const;
    void operator*=(const BigInt&);
    void operator*=(const std::string&);
    std::tuple<BigInt, BigInt> operator/(const BigInt&) const;
    std::tuple<BigInt, BigInt> operator/(const std::string&) const;
    void operator /=(const BigInt&);
    void operator /=(const std::string&);
    BigInt operator%(const BigInt&) const;
    BigInt operator%(const std::string&) const;
    void operator%=(const BigInt&);
public:
    static BigInt max(const BigInt&, const BigInt&);
    static BigInt modularAddition(const BigInt&, const BigInt&, const BigInt&);
    static BigInt modularMultiplication(const BigInt&, const BigInt&, const BigInt&);
    static BigInt GCD(BigInt, BigInt);
    static std::tuple<BigInt, BigInt, BigInt> Bezout(const BigInt&, const BigInt&);
    static BigInt inverseModulo(const BigInt&, const BigInt&);
    BigInt modularExponentiation(const BigInt& base, const BigInt& exponent, const BigInt& modulo) const;
    bool isPrime() const;
    int toInt() const;

    string randomString(int length) {
        mt19937 rng;
        rng.seed(random_device()());
        uniform_int_distribution<int> dist(1, 9);

        string randomStr;
        for (int i = 0; i < length; i++) {
            randomStr += to_string(dist(rng));
        }
        return randomStr;
    }
public:
    friend std::istream& operator>>(std::istream&, BigInt&);
    friend std::ostream& operator<<(std::ostream&, const BigInt&);
    friend std::ostream& operator<<(std::ostream&, const std::tuple<BigInt, BigInt, BigInt>&);


};

#endif