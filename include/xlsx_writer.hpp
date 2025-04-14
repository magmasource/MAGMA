/*
 easyMelts (c) 2020 Einari Suikkanen
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

