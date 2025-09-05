/*
 easyMelts (c) 2020-2024 Einari Suikkanen
 easyMelts (c) 2025 Paula Antoshechkina
*/

#include "e_utility.hpp"

#include <algorithm>
#include <fstream>

Elog::Elog() {}

Elog::~Elog() {
    //SaveLogOverwriteOld();
}

//Simple logging system
Elog &Elog::Log() {
    static Elog instance;
    return instance;
};

void Elog::AddLog(std::string msg, Severity severity) {
    auto t0 = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::string timestring = std::ctime(&t0);
    timestring.erase(std::remove(timestring.begin(), timestring.end(), '\n'), timestring.end()); //Erases newline from string returned by ctime
    std::string error;
    switch (severity) {
    case NOTICE:
        error = "";
        break;
    case CAUTION:
        error = "(CAUTION) ";
        break;
    case WARNING:
        error = "(WARNING) ";
        break;
    case CRITICAL:
        error = "(CRITICAL ERROR) ";
        break;
    }
    log.push_back(std::make_pair(timestring + ": " + error + msg, severity));
}

std::vector<std::pair<std::string, Severity>> const &Elog::GetLog() {
    return log;
}
/*
 Works only in Windows because in OsX current path could be system root /
 */
void Elog::SaveLogOverwriteOld() {
    std::ofstream file;
    std::string path = "session.log";//std::filesystem::current_path().string() + "/session.log";

    file.open(path.c_str());

    for (auto it = log.rbegin(); it != log.rend(); ++it) {
        file << (*it).first << "\n";
    }
    file.close();
}

namespace MyUtil {

void SplitString(const std::string &s, char delim, std::vector<std::string> elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
}

std::vector<std::string> Split(const std::string &s, char delim) {
    std::vector<std::string> words;
    SplitString(s, delim, words);
    return words;
}

/*
 Returns float as std::string with precision of two decimal places
 */
std::string FloatAsString2(float arg) {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(2) << arg;
    return ss.str();
}

std::string DoubleAsString(double arg, int precision) {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(precision) << arg;
    return ss.str();
}

} // namespace MyUtil