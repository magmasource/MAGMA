/*
 easyMelts (c) 2020-2024 Einari Suikkanen
 easyMelts (c) 2025 Paula Antoshechkina
*/

#ifndef XLSXWRITER_HPP
#define XLSXWRITER_HPP

#include "melts_interface.hpp"
#include <vector>

class XLSXWriter  {
public:
    XLSXWriter(const std::vector<SilminData> &data, std::string filename);

private:
    bool WriteToFile(const std::vector<SilminData> &data, std::string filename);


};

#endif /* XLSXWRITER_HPP */

