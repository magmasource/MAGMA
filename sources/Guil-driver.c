#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main (int argc, char *argv[]) {

  char *data_guil[135][13] = { 
/* these are Lydia's data: SiO2, TiO2, Al2O3, FeO, MnO, MgO, CaO, Na2O, K2O, P2O5, H2O, deltaNNO */
    { "X225CE_H2O_8_fO2_-2", "70.16", "0.72", "14.58", "3.45", "0.00", "0.81", "2.70", "4.12", "3.45", "0.00", "8.00", "-2.00" }, 
    { "X225CE_H2O_7_fO2_-2", "70.16", "0.72", "14.58", "3.45", "0.00", "0.81", "2.70", "4.12", "3.45", "0.00", "7.00", "-2.00" }, 
    { "X225CE_H2O_6_fO2_-2", "70.16", "0.72", "14.58", "3.45", "0.00", "0.81", "2.70", "4.12", "3.45", "0.00", "6.00", "-2.00" }, 
    { "X225CE_H2O_5_fO2_-2", "70.16", "0.72", "14.58", "3.45", "0.00", "0.81", "2.70", "4.12", "3.45", "0.00", "5.00", "-2.00" }, 
    { "X225CE_H2O_4_fO2_-2", "70.16", "0.72", "14.58", "3.45", "0.00", "0.81", "2.70", "4.12", "3.45", "0.00", "4.00", "-2.00" }, 
    { "X225CE_H2O_3_fO2_-2", "70.16", "0.72", "14.58", "3.45", "0.00", "0.81", "2.70", "4.12", "3.45", "0.00", "3.00", "-2.00" }, 
    { "X225CE_H2O_2_fO2_-2", "70.16", "0.72", "14.58", "3.45", "0.00", "0.81", "2.70", "4.12", "3.45", "0.00", "2.00", "-2.00" }, 
    { "X225CE_H2O_1_fO2_-2", "70.16", "0.72", "14.58", "3.45", "0.00", "0.81", "2.70", "4.12", "3.45", "0.00", "1.00", "-2.00" }, 
    { "X225CE_H2O_0.5_fO2_-2", "70.16", "0.72", "14.58", "3.45", "0.00", "0.81", "2.70", "4.12", "3.45", "0.00", "0.50", "-2.00" }, 
    { "X225CE_H2O_8_fO2_-1", "70.16", "0.72", "14.58", "3.45", "0.00", "0.81", "2.70", "4.12", "3.45", "0.00", "8.00", "-1.00" }, 
    { "X225CE_H2O_7_fO2_-1", "70.16", "0.72", "14.58", "3.45", "0.00", "0.81", "2.70", "4.12", "3.45", "0.00", "7.00", "-1.00" }, 
    { "X225CE_H2O_6_fO2_-1", "70.16", "0.72", "14.58", "3.45", "0.00", "0.81", "2.70", "4.12", "3.45", "0.00", "6.00", "-1.00" }, 
    { "X225CE_H2O_5_fO2_-1", "70.16", "0.72", "14.58", "3.45", "0.00", "0.81", "2.70", "4.12", "3.45", "0.00", "5.00", "-1.00" }, 
    { "X225CE_H2O_4_fO2_-1", "70.16", "0.72", "14.58", "3.45", "0.00", "0.81", "2.70", "4.12", "3.45", "0.00", "4.00", "-1.00" }, 
    { "X225CE_H2O_3_fO2_-1", "70.16", "0.72", "14.58", "3.45", "0.00", "0.81", "2.70", "4.12", "3.45", "0.00", "3.00", "-1.00" }, 
    { "X225CE_H2O_2_fO2_-1", "70.16", "0.72", "14.58", "3.45", "0.00", "0.81", "2.70", "4.12", "3.45", "0.00", "2.00", "-1.00" }, 
    { "X225CE_H2O_1_fO2_-1", "70.16", "0.72", "14.58", "3.45", "0.00", "0.81", "2.70", "4.12", "3.45", "0.00", "1.00", "-1.00" }, 
    { "X225CE_H2O_0.5_fO2_-1", "70.16", "0.72", "14.58", "3.45", "0.00", "0.81", "2.70", "4.12", "3.45", "0.00", "0.50", "-1.00" }, 
    { "X225CE_H2O_8_fO2_0", "70.16", "0.72", "14.58", "3.45", "0.00", "0.81", "2.70", "4.12", "3.45", "0.00", "8.00", "0.00" }, 
    { "X225CE_H2O_7_fO2_0", "70.16", "0.72", "14.58", "3.45", "0.00", "0.81", "2.70", "4.12", "3.45", "0.00", "7.00", "0.00" }, 
    { "X225CE_H2O_6_fO2_0", "70.16", "0.72", "14.58", "3.45", "0.00", "0.81", "2.70", "4.12", "3.45", "0.00", "6.00", "0.00" }, 
    { "X225CE_H2O_5_fO2_0", "70.16", "0.72", "14.58", "3.45", "0.00", "0.81", "2.70", "4.12", "3.45", "0.00", "5.00", "0.00" }, 
    { "X225CE_H2O_4_fO2_0", "70.16", "0.72", "14.58", "3.45", "0.00", "0.81", "2.70", "4.12", "3.45", "0.00", "4.00", "0.00" }, 
    { "X225CE_H2O_3_fO2_0", "70.16", "0.72", "14.58", "3.45", "0.00", "0.81", "2.70", "4.12", "3.45", "0.00", "3.00", "0.00" }, 
    { "X225CE_H2O_2_fO2_0", "70.16", "0.72", "14.58", "3.45", "0.00", "0.81", "2.70", "4.12", "3.45", "0.00", "2.00", "0.00" }, 
    { "X225CE_H2O_1_fO2_0", "70.16", "0.72", "14.58", "3.45", "0.00", "0.81", "2.70", "4.12", "3.45", "0.00", "1.00", "0.00" }, 
    { "X225CE_H2O_0.5_fO2_0", "70.16", "0.72", "14.58", "3.45", "0.00", "0.81", "2.70", "4.12", "3.45", "0.00", "0.50", "0.00" }, 
    { "X225CE_H2O_8_fO2_1", "70.16", "0.72", "14.58", "3.45", "0.00", "0.81", "2.70", "4.12", "3.45", "0.00", "8.00", "1.00" }, 
    { "X225CE_H2O_7_fO2_1", "70.16", "0.72", "14.58", "3.45", "0.00", "0.81", "2.70", "4.12", "3.45", "0.00", "7.00", "1.00" }, 
    { "X225CE_H2O_6_fO2_1", "70.16", "0.72", "14.58", "3.45", "0.00", "0.81", "2.70", "4.12", "3.45", "0.00", "6.00", "1.00" }, 
    { "X225CE_H2O_5_fO2_1", "70.16", "0.72", "14.58", "3.45", "0.00", "0.81", "2.70", "4.12", "3.45", "0.00", "5.00", "1.00" }, 
    { "X225CE_H2O_4_fO2_1", "70.16", "0.72", "14.58", "3.45", "0.00", "0.81", "2.70", "4.12", "3.45", "0.00", "4.00", "1.00" }, 
    { "X225CE_H2O_3_fO2_1", "70.16", "0.72", "14.58", "3.45", "0.00", "0.81", "2.70", "4.12", "3.45", "0.00", "3.00", "1.00" }, 
    { "X225CE_H2O_2_fO2_1", "70.16", "0.72", "14.58", "3.45", "0.00", "0.81", "2.70", "4.12", "3.45", "0.00", "2.00", "1.00" }, 
    { "X225CE_H2O_1_fO2_1", "70.16", "0.72", "14.58", "3.45", "0.00", "0.81", "2.70", "4.12", "3.45", "0.00", "1.00", "1.00" }, 
    { "X225CE_H2O_0.5_fO2_1", "70.16", "0.72", "14.58", "3.45", "0.00", "0.81", "2.70", "4.12", "3.45", "0.00", "0.50", "1.00" }, 
    { "X225CE_H2O_8_fO2_2", "70.16", "0.72", "14.58", "3.45", "0.00", "0.81", "2.70", "4.12", "3.45", "0.00", "8.00", "2.00" }, 
    { "X225CE_H2O_7_fO2_2", "70.16", "0.72", "14.58", "3.45", "0.00", "0.81", "2.70", "4.12", "3.45", "0.00", "7.00", "2.00" }, 
    { "X225CE_H2O_6_fO2_2", "70.16", "0.72", "14.58", "3.45", "0.00", "0.81", "2.70", "4.12", "3.45", "0.00", "6.00", "2.00" }, 
    { "X225CE_H2O_5_fO2_2", "70.16", "0.72", "14.58", "3.45", "0.00", "0.81", "2.70", "4.12", "3.45", "0.00", "5.00", "2.00" }, 
    { "X225CE_H2O_4_fO2_2", "70.16", "0.72", "14.58", "3.45", "0.00", "0.81", "2.70", "4.12", "3.45", "0.00", "4.00", "2.00" }, 
    { "X225CE_H2O_3_fO2_2", "70.16", "0.72", "14.58", "3.45", "0.00", "0.81", "2.70", "4.12", "3.45", "0.00", "3.00", "2.00" }, 
    { "X225CE_H2O_2_fO2_2", "70.16", "0.72", "14.58", "3.45", "0.00", "0.81", "2.70", "4.12", "3.45", "0.00", "2.00", "2.00" }, 
    { "X225CE_H2O_1_fO2_2", "70.16", "0.72", "14.58", "3.45", "0.00", "0.81", "2.70", "4.12", "3.45", "0.00", "1.00", "2.00" }, 
    { "X225CE_H2O_0.5_fO2_2", "70.16", "0.72", "14.58", "3.45", "0.00", "0.81", "2.70", "4.12", "3.45", "0.00", "0.50", "2.00" }, 
    { "X109AC-1_H2O_8_fo2_-2", "70.31", "0.76", "14.27", "3.78", "0.00", "0.84", "2.83", "3.58", "3.64", "0.00", "8.00", "-2.00" }, 
    { "X109AC-1_H2O_7_fo2_-2", "70.31", "0.76", "14.27", "3.78", "0.00", "0.84", "2.83", "3.58", "3.64", "0.00", "7.00", "-2.00" }, 
    { "X109AC-1_H2O_6_fo2_-2", "70.31", "0.76", "14.27", "3.78", "0.00", "0.84", "2.83", "3.58", "3.64", "0.00", "6.00", "-2.00" }, 
    { "X109AC-1_H2O_5_fo2_-2", "70.31", "0.76", "14.27", "3.78", "0.00", "0.84", "2.83", "3.58", "3.64", "0.00", "5.00", "-2.00" }, 
    { "X109AC-1_H2O_4_fo2_-2", "70.31", "0.76", "14.27", "3.78", "0.00", "0.84", "2.83", "3.58", "3.64", "0.00", "4.00", "-2.00" }, 
    { "X109AC-1_H2O_3_fo2_-2", "70.31", "0.76", "14.27", "3.78", "0.00", "0.84", "2.83", "3.58", "3.64", "0.00", "3.00", "-2.00" }, 
    { "X109AC-1_H2O_2_fo2_-2", "70.31", "0.76", "14.27", "3.78", "0.00", "0.84", "2.83", "3.58", "3.64", "0.00", "2.00", "-2.00" }, 
    { "X109AC-1_H2O_1_fo2_-2", "70.31", "0.76", "14.27", "3.78", "0.00", "0.84", "2.83", "3.58", "3.64", "0.00", "1.00", "-2.00" }, 
    { "X109AC-1_H2O_0.5_fo2_-2", "70.31", "0.76", "14.27", "3.78", "0.00", "0.84", "2.83", "3.58", "3.64", "0.00", "0.50", "-2.00" }, 
    { "X109AC-1_H2O_8_fo2_-1", "70.31", "0.76", "14.27", "3.78", "0.00", "0.84", "2.83", "3.58", "3.64", "0.00", "8.00", "-1.00" }, 
    { "X109AC-1_H2O_7_fo2_-1", "70.31", "0.76", "14.27", "3.78", "0.00", "0.84", "2.83", "3.58", "3.64", "0.00", "7.00", "-1.00" }, 
    { "X109AC-1_H2O_6_fo2_-1", "70.31", "0.76", "14.27", "3.78", "0.00", "0.84", "2.83", "3.58", "3.64", "0.00", "6.00", "-1.00" }, 
    { "X109AC-1_H2O_5_fo2_-1", "70.31", "0.76", "14.27", "3.78", "0.00", "0.84", "2.83", "3.58", "3.64", "0.00", "5.00", "-1.00" }, 
    { "X109AC-1_H2O_4_fo2_-1", "70.31", "0.76", "14.27", "3.78", "0.00", "0.84", "2.83", "3.58", "3.64", "0.00", "4.00", "-1.00" }, 
    { "X109AC-1_H2O_3_fo2_-1", "70.31", "0.76", "14.27", "3.78", "0.00", "0.84", "2.83", "3.58", "3.64", "0.00", "3.00", "-1.00" }, 
    { "X109AC-1_H2O_2_fo2_-1", "70.31", "0.76", "14.27", "3.78", "0.00", "0.84", "2.83", "3.58", "3.64", "0.00", "2.00", "-1.00" }, 
    { "X109AC-1_H2O_1_fo2_-1", "70.31", "0.76", "14.27", "3.78", "0.00", "0.84", "2.83", "3.58", "3.64", "0.00", "1.00", "-1.00" }, 
    { "X109AC-1_H2O_0.5_fo2_-1", "70.31", "0.76", "14.27", "3.78", "0.00", "0.84", "2.83", "3.58", "3.64", "0.00", "0.50", "-1.00" }, 
    { "X109AC-1_H2O_8_fo2_0", "70.31", "0.76", "14.27", "3.78", "0.00", "0.84", "2.83", "3.58", "3.64", "0.00", "8.00", "0.00" }, 
    { "X109AC-1_H2O_7_fo2_0", "70.31", "0.76", "14.27", "3.78", "0.00", "0.84", "2.83", "3.58", "3.64", "0.00", "7.00", "0.00" }, 
    { "X109AC-1_H2O_6_fo2_0", "70.31", "0.76", "14.27", "3.78", "0.00", "0.84", "2.83", "3.58", "3.64", "0.00", "6.00", "0.00" }, 
    { "X109AC-1_H2O_5_fo2_0", "70.31", "0.76", "14.27", "3.78", "0.00", "0.84", "2.83", "3.58", "3.64", "0.00", "5.00", "0.00" }, 
    { "X109AC-1_H2O_4_fo2_0", "70.31", "0.76", "14.27", "3.78", "0.00", "0.84", "2.83", "3.58", "3.64", "0.00", "4.00", "0.00" }, 
    { "X109AC-1_H2O_3_fo2_0", "70.31", "0.76", "14.27", "3.78", "0.00", "0.84", "2.83", "3.58", "3.64", "0.00", "3.00", "0.00" }, 
    { "X109AC-1_H2O_2_fo2_0", "70.31", "0.76", "14.27", "3.78", "0.00", "0.84", "2.83", "3.58", "3.64", "0.00", "2.00", "0.00" }, 
    { "X109AC-1_H2O_1_fo2_0", "70.31", "0.76", "14.27", "3.78", "0.00", "0.84", "2.83", "3.58", "3.64", "0.00", "1.00", "0.00" }, 
    { "X109AC-1_H2O_0.5_fo2_0", "70.31", "0.76", "14.27", "3.78", "0.00", "0.84", "2.83", "3.58", "3.64", "0.00", "0.50", "0.00" }, 
    { "X109AC-1_H2O_8_fo2_1", "70.31", "0.76", "14.27", "3.78", "0.00", "0.84", "2.83", "3.58", "3.64", "0.00", "8.00", "1.00" }, 
    { "X109AC-1_H2O_7_fo2_1", "70.31", "0.76", "14.27", "3.78", "0.00", "0.84", "2.83", "3.58", "3.64", "0.00", "7.00", "1.00" }, 
    { "X109AC-1_H2O_6_fo2_1", "70.31", "0.76", "14.27", "3.78", "0.00", "0.84", "2.83", "3.58", "3.64", "0.00", "6.00", "1.00" }, 
    { "X109AC-1_H2O_5_fo2_1", "70.31", "0.76", "14.27", "3.78", "0.00", "0.84", "2.83", "3.58", "3.64", "0.00", "5.00", "1.00" }, 
    { "X109AC-1_H2O_4_fo2_1", "70.31", "0.76", "14.27", "3.78", "0.00", "0.84", "2.83", "3.58", "3.64", "0.00", "4.00", "1.00" }, 
    { "X109AC-1_H2O_3_fo2_1", "70.31", "0.76", "14.27", "3.78", "0.00", "0.84", "2.83", "3.58", "3.64", "0.00", "3.00", "1.00" }, 
    { "X109AC-1_H2O_2_fo2_1", "70.31", "0.76", "14.27", "3.78", "0.00", "0.84", "2.83", "3.58", "3.64", "0.00", "2.00", "1.00" }, 
    { "X109AC-1_H2O_1_fo2_1", "70.31", "0.76", "14.27", "3.78", "0.00", "0.84", "2.83", "3.58", "3.64", "0.00", "1.00", "1.00" }, 
    { "X109AC-1_H2O_0.5_fo2_1", "70.31", "0.76", "14.27", "3.78", "0.00", "0.84", "2.83", "3.58", "3.64", "0.00", "0.50", "1.00" }, 
    { "X109AC-1_H2O_8_fo2_2", "70.31", "0.76", "14.27", "3.78", "0.00", "0.84", "2.83", "3.58", "3.64", "0.00", "8.00", "2.00" }, 
    { "X109AC-1_H2O_7_fo2_2", "70.31", "0.76", "14.27", "3.78", "0.00", "0.84", "2.83", "3.58", "3.64", "0.00", "7.00", "2.00" }, 
    { "X109AC-1_H2O_6_fo2_2", "70.31", "0.76", "14.27", "3.78", "0.00", "0.84", "2.83", "3.58", "3.64", "0.00", "6.00", "2.00" }, 
    { "X109AC-1_H2O_5_fo2_2", "70.31", "0.76", "14.27", "3.78", "0.00", "0.84", "2.83", "3.58", "3.64", "0.00", "5.00", "2.00" }, 
    { "X109AC-1_H2O_4_fo2_2", "70.31", "0.76", "14.27", "3.78", "0.00", "0.84", "2.83", "3.58", "3.64", "0.00", "4.00", "2.00" }, 
    { "X109AC-1_H2O_3_fo2_2", "70.31", "0.76", "14.27", "3.78", "0.00", "0.84", "2.83", "3.58", "3.64", "0.00", "3.00", "2.00" }, 
    { "X109AC-1_H2O_2_fo2_2", "70.31", "0.76", "14.27", "3.78", "0.00", "0.84", "2.83", "3.58", "3.64", "0.00", "2.00", "2.00" }, 
    { "X109AC-1_H2O_1_fo2_2", "70.31", "0.76", "14.27", "3.78", "0.00", "0.84", "2.83", "3.58", "3.64", "0.00", "1.00", "2.00" }, 
    { "X109AC-1_H2O_0.5_fo2_2", "70.31", "0.76", "14.27", "3.78", "0.00", "0.84", "2.83", "3.58", "3.64", "0.00", "0.50", "2.00" }, 
    { "X262AD_H2O_8_fO2_-2", "70.78", "0.74", "14.30", "3.33", "0.00", "0.73", "2.54", "3.96", "3.62", "0.00", "8.00", "-2.00" }, 
    { "X262AD_H2O_7_fO2_-2", "70.78", "0.74", "14.30", "3.33", "0.00", "0.73", "2.54", "3.96", "3.62", "0.00", "7.00", "-2.00" }, 
    { "X262AD_H2O_6_fO2_-2", "70.78", "0.74", "14.30", "3.33", "0.00", "0.73", "2.54", "3.96", "3.62", "0.00", "6.00", "-2.00" }, 
    { "X262AD_H2O_5_fO2_-2", "70.78", "0.74", "14.30", "3.33", "0.00", "0.73", "2.54", "3.96", "3.62", "0.00", "5.00", "-2.00" }, 
    { "X262AD_H2O_4_fO2_-2", "70.78", "0.74", "14.30", "3.33", "0.00", "0.73", "2.54", "3.96", "3.62", "0.00", "4.00", "-2.00" }, 
    { "X262AD_H2O_3_fO2_-2", "70.78", "0.74", "14.30", "3.33", "0.00", "0.73", "2.54", "3.96", "3.62", "0.00", "3.00", "-2.00" }, 
    { "X262AD_H2O_2_fO2_-2", "70.78", "0.74", "14.30", "3.33", "0.00", "0.73", "2.54", "3.96", "3.62", "0.00", "2.00", "-2.00" }, 
    { "X262AD_H2O_1_fO2_-2", "70.78", "0.74", "14.30", "3.33", "0.00", "0.73", "2.54", "3.96", "3.62", "0.00", "1.00", "-2.00" }, 
    { "X262AD_H2O_0.5_fO2_-2", "70.78", "0.74", "14.30", "3.33", "0.00", "0.73", "2.54", "3.96", "3.62", "0.00", "0.50", "-2.00" }, 
    { "X262AD_H2O_8_fO2_-1", "70.78", "0.74", "14.30", "3.33", "0.00", "0.73", "2.54", "3.96", "3.62", "0.00", "8.00", "-1.00" }, 
    { "X262AD_H2O_7_fO2_-1", "70.78", "0.74", "14.30", "3.33", "0.00", "0.73", "2.54", "3.96", "3.62", "0.00", "7.00", "-1.00" }, 
    { "X262AD_H2O_6_fO2_-1", "70.78", "0.74", "14.30", "3.33", "0.00", "0.73", "2.54", "3.96", "3.62", "0.00", "6.00", "-1.00" }, 
    { "X262AD_H2O_5_fO2_-1", "70.78", "0.74", "14.30", "3.33", "0.00", "0.73", "2.54", "3.96", "3.62", "0.00", "5.00", "-1.00" }, 
    { "X262AD_H2O_4_fO2_-1", "70.78", "0.74", "14.30", "3.33", "0.00", "0.73", "2.54", "3.96", "3.62", "0.00", "4.00", "-1.00" }, 
    { "X262AD_H2O_3_fO2_-1", "70.78", "0.74", "14.30", "3.33", "0.00", "0.73", "2.54", "3.96", "3.62", "0.00", "3.00", "-1.00" }, 
    { "X262AD_H2O_2_fO2_-1", "70.78", "0.74", "14.30", "3.33", "0.00", "0.73", "2.54", "3.96", "3.62", "0.00", "2.00", "-1.00" }, 
    { "X262AD_H2O_1_fO2_-1", "70.78", "0.74", "14.30", "3.33", "0.00", "0.73", "2.54", "3.96", "3.62", "0.00", "1.00", "-1.00" }, 
    { "X262AD_H2O_0.5_fO2_-1", "70.78", "0.74", "14.30", "3.33", "0.00", "0.73", "2.54", "3.96", "3.62", "0.00", "0.50", "-1.00" }, 
    { "X262AD_H2O_8_fO2_0", "70.78", "0.74", "14.30", "3.33", "0.00", "0.73", "2.54", "3.96", "3.62", "0.00", "8.00", "0.00" }, 
    { "X262AD_H2O_7_fO2_0", "70.78", "0.74", "14.30", "3.33", "0.00", "0.73", "2.54", "3.96", "3.62", "0.00", "7.00", "0.00" }, 
    { "X262AD_H2O_6_fO2_0", "70.78", "0.74", "14.30", "3.33", "0.00", "0.73", "2.54", "3.96", "3.62", "0.00", "6.00", "0.00" }, 
    { "X262AD_H2O_5_fO2_0", "70.78", "0.74", "14.30", "3.33", "0.00", "0.73", "2.54", "3.96", "3.62", "0.00", "5.00", "0.00" }, 
    { "X262AD_H2O_4_fO2_0", "70.78", "0.74", "14.30", "3.33", "0.00", "0.73", "2.54", "3.96", "3.62", "0.00", "4.00", "0.00" }, 
    { "X262AD_H2O_3_fO2_0", "70.78", "0.74", "14.30", "3.33", "0.00", "0.73", "2.54", "3.96", "3.62", "0.00", "3.00", "0.00" }, 
    { "X262AD_H2O_2_fO2_0", "70.78", "0.74", "14.30", "3.33", "0.00", "0.73", "2.54", "3.96", "3.62", "0.00", "2.00", "0.00" }, 
    { "X262AD_H2O_1_fO2_0", "70.78", "0.74", "14.30", "3.33", "0.00", "0.73", "2.54", "3.96", "3.62", "0.00", "1.00", "0.00" }, 
    { "X262AD_H2O_0.5_fO2_0", "70.78", "0.74", "14.30", "3.33", "0.00", "0.73", "2.54", "3.96", "3.62", "0.00", "0.50", "0.00" }, 
    { "X262AD_H2O_8_fO2_1", "70.78", "0.74", "14.30", "3.33", "0.00", "0.73", "2.54", "3.96", "3.62", "0.00", "8.00", "1.00" }, 
    { "X262AD_H2O_7_fO2_1", "70.78", "0.74", "14.30", "3.33", "0.00", "0.73", "2.54", "3.96", "3.62", "0.00", "7.00", "1.00" }, 
    { "X262AD_H2O_6_fO2_1", "70.78", "0.74", "14.30", "3.33", "0.00", "0.73", "2.54", "3.96", "3.62", "0.00", "6.00", "1.00" }, 
    { "X262AD_H2O_5_fO2_1", "70.78", "0.74", "14.30", "3.33", "0.00", "0.73", "2.54", "3.96", "3.62", "0.00", "5.00", "1.00" }, 
    { "X262AD_H2O_4_fO2_1", "70.78", "0.74", "14.30", "3.33", "0.00", "0.73", "2.54", "3.96", "3.62", "0.00", "4.00", "1.00" }, 
    { "X262AD_H2O_3_fO2_1", "70.78", "0.74", "14.30", "3.33", "0.00", "0.73", "2.54", "3.96", "3.62", "0.00", "3.00", "1.00" }, 
    { "X262AD_H2O_2_fO2_1", "70.78", "0.74", "14.30", "3.33", "0.00", "0.73", "2.54", "3.96", "3.62", "0.00", "2.00", "1.00" }, 
    { "X262AD_H2O_1_fO2_1", "70.78", "0.74", "14.30", "3.33", "0.00", "0.73", "2.54", "3.96", "3.62", "0.00", "1.00", "1.00" }, 
    { "X262AD_H2O_0.5_fO2_1", "70.78", "0.74", "14.30", "3.33", "0.00", "0.73", "2.54", "3.96", "3.62", "0.00", "0.50", "1.00" }, 
    { "X262AD_H2O_8_fO2_2", "70.78", "0.74", "14.30", "3.33", "0.00", "0.73", "2.54", "3.96", "3.62", "0.00", "8.00", "2.00" }, 
    { "X262AD_H2O_7_fO2_2", "70.78", "0.74", "14.30", "3.33", "0.00", "0.73", "2.54", "3.96", "3.62", "0.00", "7.00", "2.00" }, 
    { "X262AD_H2O_6_fO2_2", "70.78", "0.74", "14.30", "3.33", "0.00", "0.73", "2.54", "3.96", "3.62", "0.00", "6.00", "2.00" }, 
    { "X262AD_H2O_5_fO2_2", "70.78", "0.74", "14.30", "3.33", "0.00", "0.73", "2.54", "3.96", "3.62", "0.00", "5.00", "2.00" }, 
    { "X262AD_H2O_4_fO2_2", "70.78", "0.74", "14.30", "3.33", "0.00", "0.73", "2.54", "3.96", "3.62", "0.00", "4.00", "2.00" }, 
    { "X262AD_H2O_3_fO2_2", "70.78", "0.74", "14.30", "3.33", "0.00", "0.73", "2.54", "3.96", "3.62", "0.00", "3.00", "2.00" }, 
    { "X262AD_H2O_2_fO2_2", "70.78", "0.74", "14.30", "3.33", "0.00", "0.73", "2.54", "3.96", "3.62", "0.00", "2.00", "2.00" }, 
    { "X262AD_H2O_1_fO2_2", "70.78", "0.74", "14.30", "3.33", "0.00", "0.73", "2.54", "3.96", "3.62", "0.00", "1.00", "2.00" }, 
    { "X262AD_H2O_0.5_fO2_2", "70.78", "0.74", "14.30", "3.33", "0.00", "0.73", "2.54", "3.96", "3.62", "0.00", "0.50", "2.00" }
  };
  
  char *string = (char *) malloc(500*sizeof(char));
  int i;
  
  system("rm -rf GUIL-RUNS");
  system("mkdir GUIL-RUNS");
  
  for (i=0; i<135; i++) {
  
  strcpy(string, "cd GUIL-RUNS; mkdir ");
  strcat(string, data_guil[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_guil[i][0]);
  strcat(string, "; mkdir 500; cd 500; ulimit -t 15; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_guil[i][1]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_guil[i][2]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_guil[i][3]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_guil[i][4]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_guil[i][5]);  /* MnO   */
  strcat(string, " ");
  strcat(string, data_guil[i][6]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_guil[i][7]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_guil[i][8]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_guil[i][9]);  /* K2O   */
  strcat(string, " ");
  strcat(string, data_guil[i][10]); /* P2O5  */
  strcat(string, " ");
  strcat(string, data_guil[i][11]); /* H2O   */
  strcat(string, " 5000.0");
  strcat(string, " ");
  strcat(string, data_guil[i][12]);  /* delta NNO  */
  system(string);
  
  strcpy(string, "cd GUIL-RUNS; cd ");
  strcat(string, data_guil[i][0]);
  strcat(string, "; mkdir 475; cd 475; ulimit -t 15; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_guil[i][1]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_guil[i][2]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_guil[i][3]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_guil[i][4]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_guil[i][5]);  /* MnO   */
  strcat(string, " ");
  strcat(string, data_guil[i][6]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_guil[i][7]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_guil[i][8]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_guil[i][9]);  /* K2O   */
  strcat(string, " ");
  strcat(string, data_guil[i][10]); /* P2O5  */
  strcat(string, " ");
  strcat(string, data_guil[i][11]); /* H2O   */
  strcat(string, " 4750.0");
  strcat(string, " ");
  strcat(string, data_guil[i][12]);  /* delta NNO  */
  system(string);
  
  strcpy(string, "cd GUIL-RUNS; cd ");
  strcat(string, data_guil[i][0]);
  strcat(string, "; mkdir 450; cd 450; ulimit -t 15; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_guil[i][1]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_guil[i][2]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_guil[i][3]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_guil[i][4]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_guil[i][5]);  /* MnO   */
  strcat(string, " ");
  strcat(string, data_guil[i][6]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_guil[i][7]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_guil[i][8]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_guil[i][9]);  /* K2O   */
  strcat(string, " ");
  strcat(string, data_guil[i][10]); /* P2O5  */
  strcat(string, " ");
  strcat(string, data_guil[i][11]); /* H2O   */
  strcat(string, " 4500.0");
  strcat(string, " ");
  strcat(string, data_guil[i][12]);  /* delta NNO  */
  system(string);
  
  strcpy(string, "cd GUIL-RUNS; cd ");
  strcat(string, data_guil[i][0]);
  strcat(string, "; mkdir 425; cd 425; ulimit -t 15; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_guil[i][1]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_guil[i][2]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_guil[i][3]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_guil[i][4]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_guil[i][5]);  /* MnO   */
  strcat(string, " ");
  strcat(string, data_guil[i][6]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_guil[i][7]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_guil[i][8]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_guil[i][9]);  /* K2O   */
  strcat(string, " ");
  strcat(string, data_guil[i][10]); /* P2O5  */
  strcat(string, " ");
  strcat(string, data_guil[i][11]); /* H2O   */
  strcat(string, " 4250.0");
  strcat(string, " ");
  strcat(string, data_guil[i][12]);  /* delta NNO  */
  system(string);
  
  strcpy(string, "cd GUIL-RUNS; cd ");
  strcat(string, data_guil[i][0]);
  strcat(string, "; mkdir 400; cd 400; ulimit -t 15; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_guil[i][1]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_guil[i][2]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_guil[i][3]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_guil[i][4]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_guil[i][5]);  /* MnO   */
  strcat(string, " ");
  strcat(string, data_guil[i][6]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_guil[i][7]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_guil[i][8]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_guil[i][9]);  /* K2O   */
  strcat(string, " ");
  strcat(string, data_guil[i][10]); /* P2O5  */
  strcat(string, " ");
  strcat(string, data_guil[i][11]); /* H2O   */
  strcat(string, " 4000.0");
  strcat(string, " ");
  strcat(string, data_guil[i][12]);  /* delta NNO  */
  system(string);
  
  strcpy(string, "cd GUIL-RUNS; cd ");
  strcat(string, data_guil[i][0]);
  strcat(string, "; mkdir 375; cd 375; ulimit -t 15; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_guil[i][1]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_guil[i][2]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_guil[i][3]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_guil[i][4]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_guil[i][5]);  /* MnO   */
  strcat(string, " ");
  strcat(string, data_guil[i][6]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_guil[i][7]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_guil[i][8]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_guil[i][9]);  /* K2O   */
  strcat(string, " ");
  strcat(string, data_guil[i][10]); /* P2O5  */
  strcat(string, " ");
  strcat(string, data_guil[i][11]); /* H2O   */
  strcat(string, " 3750.0");
  strcat(string, " ");
  strcat(string, data_guil[i][12]);  /* delta NNO  */
  system(string);
  
  strcpy(string, "cd GUIL-RUNS; cd ");
  strcat(string, data_guil[i][0]);
  strcat(string, "; mkdir 350; cd 350; ulimit -t 15; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_guil[i][1]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_guil[i][2]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_guil[i][3]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_guil[i][4]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_guil[i][5]);  /* MnO   */
  strcat(string, " ");
  strcat(string, data_guil[i][6]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_guil[i][7]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_guil[i][8]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_guil[i][9]);  /* K2O   */
  strcat(string, " ");
  strcat(string, data_guil[i][10]); /* P2O5  */
  strcat(string, " ");
  strcat(string, data_guil[i][11]); /* H2O   */
  strcat(string, " 3500.0");
  strcat(string, " ");
  strcat(string, data_guil[i][12]);  /* delta NNO  */
  system(string);
  
  strcpy(string, "cd GUIL-RUNS; cd ");
  strcat(string, data_guil[i][0]);
  strcat(string, "; mkdir 325; cd 325; ulimit -t 15; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_guil[i][1]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_guil[i][2]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_guil[i][3]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_guil[i][4]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_guil[i][5]);  /* MnO   */
  strcat(string, " ");
  strcat(string, data_guil[i][6]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_guil[i][7]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_guil[i][8]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_guil[i][9]);  /* K2O   */
  strcat(string, " ");
  strcat(string, data_guil[i][10]); /* P2O5  */
  strcat(string, " ");
  strcat(string, data_guil[i][11]); /* H2O   */
  strcat(string, " 3250.0");
  strcat(string, " ");
  strcat(string, data_guil[i][12]);  /* delta NNO  */
  system(string);
  
  strcpy(string, "cd GUIL-RUNS; cd ");
  strcat(string, data_guil[i][0]);
  strcat(string, "; mkdir 300; cd 300; ulimit -t 15; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_guil[i][1]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_guil[i][2]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_guil[i][3]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_guil[i][4]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_guil[i][5]);  /* MnO   */
  strcat(string, " ");
  strcat(string, data_guil[i][6]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_guil[i][7]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_guil[i][8]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_guil[i][9]);  /* K2O   */
  strcat(string, " ");
  strcat(string, data_guil[i][10]); /* P2O5  */
  strcat(string, " ");
  strcat(string, data_guil[i][11]); /* H2O   */
  strcat(string, " 3000.0");
  strcat(string, " ");
  strcat(string, data_guil[i][12]);  /* delta NNO  */
  system(string);
  
  strcpy(string, "cd GUIL-RUNS; cd ");
  strcat(string, data_guil[i][0]);
  strcat(string, "; mkdir 275; cd 275; ulimit -t 15; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_guil[i][1]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_guil[i][2]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_guil[i][3]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_guil[i][4]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_guil[i][5]);  /* MnO   */
  strcat(string, " ");
  strcat(string, data_guil[i][6]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_guil[i][7]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_guil[i][8]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_guil[i][9]);  /* K2O   */
  strcat(string, " ");
  strcat(string, data_guil[i][10]); /* P2O5  */
  strcat(string, " ");
  strcat(string, data_guil[i][11]); /* H2O   */
  strcat(string, " 2750.0");
  strcat(string, " ");
  strcat(string, data_guil[i][12]);  /* delta NNO  */
  system(string);
  
  strcpy(string, "cd GUIL-RUNS; cd ");
  strcat(string, data_guil[i][0]);
  strcat(string, "; mkdir 250; cd 250; ulimit -t 15; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_guil[i][1]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_guil[i][2]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_guil[i][3]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_guil[i][4]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_guil[i][5]);  /* MnO   */
  strcat(string, " ");
  strcat(string, data_guil[i][6]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_guil[i][7]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_guil[i][8]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_guil[i][9]);  /* K2O   */
  strcat(string, " ");
  strcat(string, data_guil[i][10]); /* P2O5  */
  strcat(string, " ");
  strcat(string, data_guil[i][11]); /* H2O   */
  strcat(string, " 2500.0");
  strcat(string, " ");
  strcat(string, data_guil[i][12]);  /* delta NNO  */
  system(string);
  
  strcpy(string, "cd GUIL-RUNS; cd ");
  strcat(string, data_guil[i][0]);
  strcat(string, "; mkdir 225; cd 225; ulimit -t 15; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_guil[i][1]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_guil[i][2]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_guil[i][3]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_guil[i][4]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_guil[i][5]);  /* MnO   */
  strcat(string, " ");
  strcat(string, data_guil[i][6]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_guil[i][7]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_guil[i][8]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_guil[i][9]);  /* K2O   */
  strcat(string, " ");
  strcat(string, data_guil[i][10]); /* P2O5  */
  strcat(string, " ");
  strcat(string, data_guil[i][11]); /* H2O   */
  strcat(string, " 2250.0");
  strcat(string, " ");
  strcat(string, data_guil[i][12]);  /* delta NNO  */
  system(string);
  
  strcpy(string, "cd GUIL-RUNS; cd ");
  strcat(string, data_guil[i][0]);
  strcat(string, "; mkdir 200; cd 200; ulimit -t 15; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_guil[i][1]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_guil[i][2]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_guil[i][3]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_guil[i][4]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_guil[i][5]);  /* MnO   */
  strcat(string, " ");
  strcat(string, data_guil[i][6]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_guil[i][7]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_guil[i][8]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_guil[i][9]);  /* K2O   */
  strcat(string, " ");
  strcat(string, data_guil[i][10]); /* P2O5  */
  strcat(string, " ");
  strcat(string, data_guil[i][11]); /* H2O   */
  strcat(string, " 2000.0");
  strcat(string, " ");
  strcat(string, data_guil[i][12]);  /* delta NNO  */
  system(string);
  
  strcpy(string, "cd GUIL-RUNS; cd ");
  strcat(string, data_guil[i][0]);
  strcat(string, "; mkdir 175; cd 175; ulimit -t 15; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_guil[i][1]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_guil[i][2]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_guil[i][3]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_guil[i][4]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_guil[i][5]);  /* MnO   */
  strcat(string, " ");
  strcat(string, data_guil[i][6]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_guil[i][7]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_guil[i][8]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_guil[i][9]);  /* K2O   */
  strcat(string, " ");
  strcat(string, data_guil[i][10]); /* P2O5  */
  strcat(string, " ");
  strcat(string, data_guil[i][11]); /* H2O   */
  strcat(string, " 1750.0");
  strcat(string, " ");
  strcat(string, data_guil[i][12]);  /* delta NNO  */
  system(string);
  
  strcpy(string, "cd GUIL-RUNS; cd ");
  strcat(string, data_guil[i][0]);
  strcat(string, "; mkdir 150; cd 150; ulimit -t 15; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_guil[i][1]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_guil[i][2]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_guil[i][3]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_guil[i][4]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_guil[i][5]);  /* MnO   */
  strcat(string, " ");
  strcat(string, data_guil[i][6]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_guil[i][7]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_guil[i][8]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_guil[i][9]);  /* K2O   */
  strcat(string, " ");
  strcat(string, data_guil[i][10]); /* P2O5  */
  strcat(string, " ");
  strcat(string, data_guil[i][11]); /* H2O   */
  strcat(string, " 1500.0");
  strcat(string, " ");
  strcat(string, data_guil[i][12]);  /* delta NNO  */
  system(string);
  
  strcpy(string, "cd GUIL-RUNS; cd ");
  strcat(string, data_guil[i][0]);
  strcat(string, "; mkdir 125; cd 125; ulimit -t 15; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_guil[i][1]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_guil[i][2]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_guil[i][3]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_guil[i][4]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_guil[i][5]);  /* MnO   */
  strcat(string, " ");
  strcat(string, data_guil[i][6]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_guil[i][7]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_guil[i][8]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_guil[i][9]);  /* K2O   */
  strcat(string, " ");
  strcat(string, data_guil[i][10]); /* P2O5  */
  strcat(string, " ");
  strcat(string, data_guil[i][11]); /* H2O   */
  strcat(string, " 1250.0");
  strcat(string, " ");
  strcat(string, data_guil[i][12]);  /* delta NNO  */
  system(string);
  
  strcpy(string, "cd GUIL-RUNS; cd ");
  strcat(string, data_guil[i][0]);
  strcat(string, "; mkdir 100; cd 100; ulimit -t 15; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_guil[i][1]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_guil[i][2]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_guil[i][3]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_guil[i][4]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_guil[i][5]);  /* MnO   */
  strcat(string, " ");
  strcat(string, data_guil[i][6]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_guil[i][7]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_guil[i][8]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_guil[i][9]);  /* K2O   */
  strcat(string, " ");
  strcat(string, data_guil[i][10]); /* P2O5  */
  strcat(string, " ");
  strcat(string, data_guil[i][11]); /* H2O   */
  strcat(string, " 1000.0");
  strcat(string, " ");
  strcat(string, data_guil[i][12]);  /* delta NNO  */
  system(string);
  
  strcpy(string, "cd GUIL-RUNS; cd ");
  strcat(string, data_guil[i][0]);
  strcat(string, "; mkdir 75; cd 75; ulimit -t 15; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_guil[i][1]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_guil[i][2]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_guil[i][3]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_guil[i][4]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_guil[i][5]);  /* MnO   */
  strcat(string, " ");
  strcat(string, data_guil[i][6]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_guil[i][7]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_guil[i][8]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_guil[i][9]);  /* K2O   */
  strcat(string, " ");
  strcat(string, data_guil[i][10]); /* P2O5  */
  strcat(string, " ");
  strcat(string, data_guil[i][11]); /* H2O   */
  strcat(string, " 750.0");
  strcat(string, " ");
  strcat(string, data_guil[i][12]);  /* delta NNO  */
  system(string);
  
  strcpy(string, "cd GUIL-RUNS; cd ");
  strcat(string, data_guil[i][0]);
  strcat(string, "; mkdir 50; cd 50; ulimit -t 15; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_guil[i][1]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_guil[i][2]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_guil[i][3]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_guil[i][4]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_guil[i][5]);  /* MnO   */
  strcat(string, " ");
  strcat(string, data_guil[i][6]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_guil[i][7]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_guil[i][8]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_guil[i][9]);  /* K2O   */
  strcat(string, " ");
  strcat(string, data_guil[i][10]); /* P2O5  */
  strcat(string, " ");
  strcat(string, data_guil[i][11]); /* H2O   */
  strcat(string, " 500.0");
  strcat(string, " ");
  strcat(string, data_guil[i][12]);  /* delta NNO  */
  system(string);
  
  strcpy(string, "cd GUIL-RUNS; cd ");
  strcat(string, data_guil[i][0]);
  strcat(string, "; mkdir 25; cd 25; ulimit -t 15; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_guil[i][1]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_guil[i][2]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_guil[i][3]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_guil[i][4]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_guil[i][5]);  /* MnO   */
  strcat(string, " ");
  strcat(string, data_guil[i][6]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_guil[i][7]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_guil[i][8]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_guil[i][9]);  /* K2O   */
  strcat(string, " ");
  strcat(string, data_guil[i][10]); /* P2O5  */
  strcat(string, " ");
  strcat(string, data_guil[i][11]); /* H2O   */
  strcat(string, " 250.0");
  strcat(string, " ");
  strcat(string, data_guil[i][12]);  /* delta NNO  */
  system(string);
  
  }

}