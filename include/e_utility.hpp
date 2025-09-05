/*
 easyMelts (c) 2020-2024 Einari Suikkanen
 easyMelts (c) 2025 Paula Antoshechkina
*/

#ifndef E_UTILITY_HPP
#define E_UTILITY_HPP

#include <chrono>
#include <ctime>
#include <vector>
#include <string>
#include <utility>
#include <sstream>
#include <iomanip> //setprecision

class MyFont {
    public:
        static const char LiberationSans_Regular_compressed_data_base85[143735+1];
};

enum Severity {
    NOTICE = 0, CAUTION = 1, WARNING = 2, CRITICAL = 3
};

class Elog {

private:
    Elog();
    virtual ~Elog();
    std::vector<std::pair<std::string, Severity>> log;

public:

    Elog(Elog const&) = delete;
    void operator=(Elog const&) = delete;

    static Elog& Log();

    void AddLog(std::string msg, Severity severity);
    void SaveLogOverwriteOld();

    std::vector<std::pair<std::string, Severity>> const & GetLog();

};

namespace MyUtil {

void SplitString(const std::string &s, char delim, std::vector<std::string> elems);

std::vector<std::string> Split(const std::string &s, char delim);

std::string FloatAsString2(float arg);

std::string DoubleAsString(double arg, int precision);

template <typename T, typename std::enable_if<std::is_arithmetic<T>::value>::type* = nullptr>
void Limit(T low, T high, T* arg) {
    if (*arg < low) *arg = low;
    if (*arg > high) *arg = high;
}


}



#endif /* E_UTILITY_HPP */

