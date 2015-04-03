#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main (int argc, char *argv[]) {

  char *data_guil[144][11] = { 
/* these are Guil's new TVZ data: SiO2, TiO2, Al2O3, FeO, MnO, MgO, CaO, Na2O, K2O, P2O5 */
    { "Ma56-10", "78.28", "0.09", "12.35", "1.08", "0.00", "0.04", "0.55", "3.49", "4.13", "0.00" }, 
    { "Ma56-11", "78.36", "0.09", "12.35", "1.04", "0.00", "0.05", "0.53", "3.45", "4.13", "0.00" }, 
    { "Ma56-9", "78.27", "0.10", "12.37", "1.09", "0.00", "0.04", "0.55", "3.41", "4.16", "0.00" }, 
    { "Ma54-6", "78.34", "0.08", "12.28", "1.03", "0.00", "0.02", "0.54", "3.52", "4.20", "0.00" }, 
    { "Ma54-7", "78.34", "0.12", "12.28", "1.00", "0.00", "0.04", "0.52", "3.54", "4.16", "0.00" }, 
    { "Ma54-8", "78.31", "0.05", "12.33", "1.03", "0.00", "0.04", "0.53", "3.55", "4.16", "0.00" }, 
    { "Ma55-1", "78.25", "0.08", "12.39", "1.04", "0.00", "0.05", "0.53", "3.52", "4.15", "0.00" }, 
    { "Ma55-2", "78.22", "0.09", "12.37", "1.05", "0.00", "0.04", "0.54", "3.55", "4.13", "0.00" }, 
    { "Ma55-3", "78.29", "0.06", "12.35", "1.04", "0.00", "0.00", "0.51", "3.55", "4.19", "0.00" }, 
    { "Ma23-12", "78.35", "0.11", "12.34", "1.22", "0.00", "0.06", "0.68", "3.52", "3.72", "0.00" }, 
    { "Ma23-13", "78.37", "0.09", "12.23", "1.23", "0.00", "0.09", "0.69", "3.55", "3.75", "0.00" }, 
    { "Ma23-14", "78.37", "0.09", "12.23", "1.23", "0.00", "0.09", "0.69", "3.55", "3.75", "0.00" }, 
    { "Ma57-18", "78.29", "0.09", "12.27", "1.02", "0.00", "0.05", "0.54", "3.57", "4.16", "0.00" }, 
    { "Ma57-19", "78.25", "0.07", "12.32", "1.07", "0.00", "0.07", "0.53", "3.52", "4.16", "0.00" }, 
    { "Ma57-22", "78.32", "0.11", "12.31", "1.02", "0.00", "0.04", "0.52", "3.55", "4.13", "0.00" }, 
    { "Oh_3_D160a", "77.69", "0.15", "12.40", "1.28", "0.00", "0.07", "0.71", "3.61", "4.10", "0.00" }, 
    { "8_FB11_Oh2", "78.35", "0.17", "12.51", "1.24", "0.00", "0.10", "0.70", "2.68", "4.25", "0.00" }, 
    { "9_FB11_Oh3", "77.78", "0.16", "12.46", "1.26", "0.00", "0.10", "0.69", "3.46", "4.07", "0.00" }, 
    { "12_FB11_Oh6", "77.70", "0.17", "12.28", "1.25", "0.00", "0.07", "0.70", "3.84", "3.99", "0.00" }, 
    { "16_FB11_Ma10", "77.71", "0.16", "12.34", "1.17", "0.00", "0.06", "0.69", "4.08", "3.78", "0.00" }, 
    { "19_FB11_Ma13", "77.68", "0.14", "12.34", "1.22", "0.00", "0.08", "0.69", "4.15", "3.71", "0.00" }, 
    { "20_FB11_Ma14", "77.80", "0.13", "12.29", "1.18", "0.00", "0.08", "0.70", "4.10", "3.73", "0.00" }, 
    { "23_FB11_Ma17", "77.45", "0.16", "12.62", "1.17", "0.00", "0.10", "0.73", "4.00", "3.77", "0.00" }, 
    { "25_FB11_Ma19", "77.92", "0.15", "12.30", "1.09", "0.00", "0.09", "0.68", "4.12", "3.64", "0.00" }, 
    { "Ma24-4", "77.49", "0.19", "13.22", "1.48", "0.00", "0.14", "0.99", "3.10", "3.39", "0.00" }, 
    { "Ma24-3", "76.84", "0.22", "13.28", "1.52", "0.00", "0.16", "1.01", "3.69", "3.28", "0.00" }, 
    { "Ma24-2", "76.82", "0.20", "13.34", "1.52", "0.00", "0.14", "0.99", "3.68", "3.31", "0.00" }, 
    { "Ma25-8", "78.26", "0.17", "12.28", "1.21", "0.00", "0.06", "0.69", "3.66", "3.67", "0.00" }, 
    { "Ma25-7", "78.26", "0.15", "12.23", "1.27", "0.00", "0.07", "0.69", "3.62", "3.71", "0.00" }, 
    { "Ma25-5", "78.33", "0.13", "12.20", "1.23", "0.00", "0.10", "0.71", "3.60", "3.70", "0.00" }, 
    { "Ma26-11", "78.22", "0.08", "12.36", "1.05", "0.00", "0.04", "0.55", "3.55", "4.15", "0.00" }, 
    { "Ma26-13", "78.34", "0.08", "12.27", "0.99", "0.00", "0.06", "0.54", "3.60", "4.12", "0.00" }, 
    { "Ma26-15", "78.31", "0.09", "12.30", "1.03", "0.00", "0.07", "0.54", "3.50", "4.16", "0.00" }, 
    { "Ma21-18", "78.26", "0.11", "12.32", "1.01", "0.00", "0.04", "0.54", "3.56", "4.16", "0.00" }, 
    { "Ma21-20", "78.22", "0.08", "12.41", "1.00", "0.00", "0.04", "0.54", "3.55", "4.15", "0.00" }, 
    { "Ma21-21", "78.27", "0.10", "12.30", "1.03", "0.00", "0.04", "0.54", "3.56", "4.16", "0.00" }, 
    { "Ma22-24", "78.21", "0.16", "12.28", "1.24", "0.00", "0.08", "0.68", "3.64", "3.71", "0.00" }, 
    { "Ma22-25", "78.32", "0.15", "12.20", "1.21", "0.00", "0.09", "0.70", "3.60", "3.73", "0.00" }, 
    { "Ma22-27", "78.27", "0.16", "12.30", "1.23", "0.00", "0.09", "0.69", "3.60", "3.66", "0.00" }, 
    { "Oh52-3", "78.11", "0.13", "12.60", "1.06", "0.00", "0.02", "0.53", "3.31", "4.24", "0.00" }, 
    { "Oh52-4", "78.26", "0.07", "12.48", "1.11", "0.00", "0.05", "0.55", "3.22", "4.26", "0.00" }, 
    { "Oh52-5", "78.31", "0.07", "12.40", "1.05", "0.00", "0.02", "0.55", "3.38", "4.22", "0.00" }, 
    { "Oh51-6", "78.15", "0.07", "12.39", "1.10", "0.00", "0.06", "0.58", "3.42", "4.23", "0.00" }, 
    { "Oh51-8", "78.16", "0.14", "12.44", "1.10", "0.00", "0.03", "0.55", "3.28", "4.30", "0.00" }, 
    { "Oh51-9", "78.10", "0.12", "12.39", "1.07", "0.00", "0.05", "0.57", "3.49", "4.21", "0.00" }, 
    { "Oh49-11", "78.32", "0.06", "12.30", "1.07", "0.00", "0.02", "0.55", "3.42", "4.26", "0.00" }, 
    { "Oh49-13", "78.42", "0.07", "12.31", "1.01", "0.00", "0.04", "0.55", "3.38", "4.22", "0.00" }, 
    { "Oh49-16", "78.26", "0.10", "12.30", "1.06", "0.00", "0.05", "0.55", "3.46", "4.22", "0.00" }, 
    { "Oh48-18", "78.33", "0.18", "12.38", "1.03", "0.00", "0.03", "0.55", "3.27", "4.23", "0.00" }, 
    { "Oh48-21", "78.35", "0.06", "12.34", "1.05", "0.00", "0.05", "0.54", "3.35", "4.26", "0.00" }, 
    { "Oh48-22", "78.28", "0.12", "12.39", "1.04", "0.00", "0.04", "0.55", "3.34", "4.24", "0.00" }, 
    { "Oh50-27", "78.34", "0.09", "12.40", "1.05", "0.00", "0.04", "0.54", "3.21", "4.33", "0.00" }, 
    { "Oh50-28", "78.32", "0.08", "12.30", "1.04", "0.00", "0.04", "0.56", "3.43", "4.23", "0.00" }, 
    { "Oh50-29", "78.32", "0.08", "12.33", "1.11", "0.00", "0.05", "0.54", "3.20", "4.36", "0.00" }, 
    { "OhD3-1", "78.80", "0.16", "12.32", "1.21", "0.00", "0.08", "0.69", "2.71", "4.02", "0.00" }, 
    { "OhD3-4", "78.14", "0.15", "12.59", "1.37", "0.00", "0.09", "0.80", "2.91", "3.95", "0.00" }, 
    { "OhD3-6", "78.12", "0.14", "12.58", "1.39", "0.00", "0.10", "0.80", "2.91", "3.96", "0.00" }, 
    { "CHP108C-1", "76.37", "0.23", "12.98", "1.35", "0.00", "0.22", "1.29", "4.02", "3.55", "0.00" }, 
    { "CHP108C-2", "76.60", "0.24", "12.90", "1.29", "0.00", "0.21", "1.21", "3.92", "3.63", "0.00" }, 
    { "CHP108C-5", "76.05", "0.20", "13.05", "1.61", "0.00", "0.17", "1.14", "4.18", "3.59", "0.00" }, 
    { "CHP108A-7", "76.38", "0.26", "12.95", "1.34", "0.00", "0.22", "1.26", "4.04", "3.55", "0.00" }, 
    { "CHP108A-9", "76.48", "0.21", "12.91", "1.35", "0.00", "0.21", "1.24", "4.06", "3.54", "0.00" }, 
    { "CHP108A-10", "76.74", "0.21", "12.83", "1.28", "0.00", "0.18", "1.16", "4.02", "3.58", "0.00" }, 
    { "CHP108G-12", "77.18", "0.15", "12.64", "1.24", "0.00", "0.13", "1.02", "3.96", "3.68", "0.00" }, 
    { "CHP108G-13", "77.18", "0.18", "12.62", "1.18", "0.00", "0.15", "1.01", "4.00", "3.68", "0.00" }, 
    { "CHP108G-14", "77.60", "0.18", "12.40", "1.12", "0.00", "0.12", "0.89", "3.95", "3.74", "0.00" }, 
    { "CHP108J-17", "76.32", "0.22", "12.95", "1.36", "0.00", "0.24", "1.28", "4.09", "3.54", "0.00" }, 
    { "CHP108J-18", "76.49", "0.23", "12.90", "1.32", "0.00", "0.22", "1.25", "4.07", "3.52", "0.00" }, 
    { "POK112B-1", "77.68", "0.14", "12.72", "0.77", "0.00", "0.00", "0.83", "4.02", "3.84", "0.00" }, 
    { "POK112B-2", "77.55", "0.17", "12.66", "0.89", "0.00", "0.01", "0.84", "4.11", "3.77", "0.00" }, 
    { "POK112B-4", "77.59", "0.15", "12.62", "0.86", "0.00", "0.02", "0.86", "4.15", "3.75", "0.00" }, 
    { "POK105A-7", "78.16", "0.12", "12.29", "0.66", "0.00", "0.02", "0.46", "3.70", "4.59", "0.00" }, 
    { "POK105A-8", "78.31", "0.05", "12.29", "0.63", "0.00", "0.01", "0.46", "3.72", "4.52", "0.00" }, 
    { "POK105A-10", "78.13", "0.11", "12.27", "0.67", "0.00", "0.01", "0.47", "3.80", "4.54", "0.00" }, 
    { "POK112A_A-14", "78.16", "0.14", "12.22", "1.24", "0.00", "0.09", "0.63", "3.87", "3.64", "0.00" }, 
    { "POK112A_A-13", "78.18", "0.11", "12.27", "1.18", "0.00", "0.06", "0.61", "3.85", "3.74", "0.00" }, 
    { "POK112A_A-12", "78.28", "0.13", "12.23", "1.17", "0.00", "0.07", "0.63", "3.87", "3.62", "0.00" }, 
    { "Mata28-1", "77.82", "0.09", "12.43", "1.05", "0.00", "0.09", "0.82", "3.99", "3.71", "0.00" }, 
    { "Mata28-3", "77.84", "0.13", "12.35", "1.06", "0.00", "0.09", "0.84", "3.97", "3.71", "0.00" }, 
    { "Mata28-4", "77.90", "0.07", "12.37", "1.06", "0.00", "0.10", "0.83", "3.91", "3.75", "0.00" }, 
    { "Mata43-6", "77.89", "0.14", "12.47", "1.21", "0.00", "0.14", "1.18", "3.81", "3.17", "0.00" }, 
    { "Mata43-7", "77.91", "0.13", "12.46", "1.23", "0.00", "0.14", "1.18", "3.73", "3.22", "0.00" }, 
    { "Mata43-8", "77.85", "0.14", "12.43", "1.24", "0.00", "0.12", "1.15", "3.86", "3.21", "0.00" }, 
    { "Mata45-10", "77.69", "0.11", "12.45", "1.08", "0.00", "0.09", "0.88", "3.94", "3.75", "0.00" }, 
    { "Mata45-11", "77.68", "0.11", "12.49", "1.07", "0.00", "0.10", "0.86", "3.92", "3.76", "0.00" }, 
    { "Mata45-13", "77.58", "0.14", "12.45", "1.06", "0.00", "0.11", "0.87", "4.02", "3.77", "0.00" }, 
    { "Mata47-17", "77.73", "0.09", "12.42", "1.14", "0.00", "0.09", "0.96", "4.06", "3.50", "0.00" }, 
    { "Mata47-19", "77.63", "0.12", "12.41", "1.24", "0.00", "0.13", "1.13", "4.11", "3.23", "0.00" }, 
    { "Mata47-20", "77.66", "0.13", "12.45", "1.13", "0.00", "0.10", "0.99", "4.09", "3.45", "0.00" }, 
    { "WHA108C-2", "77.73", "0.02", "12.56", "0.80", "0.00", "0.02", "0.51", "3.38", "4.98", "0.00" }, 
    { "WHA108C-3", "77.66", "0.03", "12.52", "0.82", "0.00", "0.02", "0.53", "3.44", "4.98", "0.00" }, 
    { "WHA108C-4", "77.68", "0.03", "12.55", "0.79", "0.00", "0.03", "0.53", "3.39", "5.00", "0.00" }, 
    { "WHA109D-16", "77.61", "0.04", "12.66", "0.66", "0.00", "0.00", "0.48", "3.09", "5.46", "0.00" }, 
    { "WHA109D-15", "77.76", "0.01", "12.57", "0.69", "0.00", "0.04", "0.51", "3.28", "5.13", "0.00" }, 
    { "WHA109D-13", "77.71", "0.06", "12.51", "0.74", "0.00", "0.02", "0.49", "3.26", "5.21", "0.00" }, 
    { "WHA114C-18", "77.76", "0.05", "12.52", "0.61", "0.00", "0.03", "0.59", "3.44", "5.00", "0.00" }, 
    { "WHA114C-19", "77.88", "0.01", "12.54", "0.51", "0.00", "0.01", "0.57", "3.41", "5.07", "0.00" }, 
    { "WHA114C-20", "78.00", "0.01", "12.53", "0.41", "0.00", "0.01", "0.58", "3.33", "5.13", "0.00" }, 
    { "POK105B-2-1", "77.48", "0.15", "12.42", "1.17", "0.00", "0.11", "0.81", "4.13", "3.73", "0.00" }, 
    { "POK105B-2-2", "77.52", "0.17", "12.44", "1.10", "0.00", "0.09", "0.79", "4.15", "3.74", "0.00" }, 
    { "POK105B-3-1", "77.57", "0.14", "12.41", "1.14", "0.00", "0.12", "0.79", "4.22", "3.61", "0.00" }, 
    { "POK105B-3-2", "77.27", "0.18", "12.50", "1.17", "0.00", "0.12", "0.85", "4.24", "3.67", "0.00" }, 
    { "POK105B-1-1", "77.26", "0.15", "12.52", "1.17", "0.00", "0.12", "0.87", "4.23", "3.68", "0.00" }, 
    { "POK105B-1-2", "77.29", "0.16", "12.55", "1.13", "0.00", "0.11", "0.84", "4.21", "3.71", "0.00" }, 
    { "Ma21-15-1-GI", "77.96", "0.07", "12.16", "0.98", "0.00", "0.03", "0.61", "3.94", "4.24", "0.00" }, 
    { "Ma21-15-2-GI", "77.84", "0.09", "12.22", "1.05", "0.00", "0.01", "0.58", "3.94", "4.27", "0.00" }, 
    { "Ma21-17-GI", "78.00", "0.07", "12.19", "1.06", "0.00", "0.04", "0.56", "3.94", "4.14", "0.00" }, 
    { "Ma25-41-GI", "77.87", "0.06", "12.23", "1.02", "0.00", "0.07", "0.63", "3.99", "4.12", "0.00" }, 
    { "Ma25-42-GI", "78.05", "0.16", "12.04", "1.16", "0.00", "0.08", "0.67", "4.22", "3.62", "0.00" }, 
    { "Ma26-27-GI", "77.78", "0.16", "12.21", "1.08", "0.00", "0.02", "0.58", "4.06", "4.11", "0.00" }, 
    { "Ma55-21-1-GI", "78.09", "0.10", "12.13", "1.04", "0.00", "0.05", "0.62", "3.91", "4.06", "0.00" }, 
    { "Ma55-21-2-GI", "78.41", "0.06", "11.95", "1.01", "0.00", "0.04", "0.59", "3.86", "4.08", "0.00" }, 
    { "Ma55-23-1-GI", "78.00", "0.06", "12.16", "1.04", "0.00", "0.07", "0.52", "3.98", "4.17", "0.00" }, 
    { "Ma55-23-2-GI", "78.12", "0.09", "12.04", "1.12", "0.00", "0.06", "0.65", "3.85", "4.07", "0.00" }, 
    { "Ma56-38-1-GI", "78.07", "0.03", "11.96", "0.98", "0.00", "0.06", "0.54", "4.24", "4.12", "0.00" }, 
    { "Ma56-38-2-GI", "78.83", "0.13", "11.83", "0.97", "0.00", "0.07", "0.52", "3.62", "4.03", "0.00" }, 
    { "Ma57-34-GI", "79.11", "0.03", "11.66", "0.97", "0.00", "0.02", "0.48", "3.73", "3.99", "0.00" }, 
    { "Oh2-11-GI", "78.09", "0.19", "12.02", "1.16", "0.00", "0.07", "0.67", "4.17", "3.63", "0.00" }, 
    { "Oh2-15-GI", "77.96", "0.15", "12.09", "1.15", "0.00", "0.09", "0.69", "4.21", "3.66", "0.00" }, 
    { "Oh2-16-1-GI", "78.70", "0.16", "11.81", "1.01", "0.00", "0.02", "0.61", "4.08", "3.61", "0.00" }, 
    { "Oh2-16-2-GI", "78.79", "0.14", "11.78", "1.00", "0.00", "0.02", "0.55", "4.03", "3.68", "0.00" }, 
    { "Oh2-17-1-GI", "78.04", "0.18", "12.07", "1.11", "0.00", "0.08", "0.68", "4.15", "3.68", "0.00" }, 
    { "Oh2-17-2-GI", "78.22", "0.15", "12.00", "1.14", "0.00", "0.08", "0.69", "4.12", "3.59", "0.00" }, 
    { "Oh3-20-GI", "79.33", "0.00", "11.53", "0.98", "0.00", "0.04", "0.64", "3.91", "3.57", "0.00" }, 
    { "Oh6-35-1-GI", "78.34", "0.13", "11.90", "1.16", "0.00", "0.09", "0.63", "4.04", "3.70", "0.00" }, 
    { "Oh6-35-2-GI", "78.74", "0.05", "11.85", "0.92", "0.00", "0.03", "0.54", "3.81", "4.06", "0.00" }, 
    { "Ma13-48-1-GI", "78.11", "0.13", "12.06", "1.12", "0.00", "0.10", "0.65", "4.16", "3.67", "0.00" }, 
    { "Ma13-48-2-GI", "78.10", "0.08", "12.04", "1.19", "0.00", "0.08", "0.59", "4.26", "3.65", "0.00" }, 
    { "Ma14-42-GI", "77.97", "0.03", "12.25", "1.01", "0.00", "0.00", "0.37", "4.34", "4.03", "0.00" }, 
    { "Ma17-61-GI", "77.56", "0.07", "12.20", "1.18", "0.00", "0.07", "0.58", "4.45", "3.89", "0.00" }, 
    { "Ma21-7-GI", "78.22", "0.14", "11.97", "1.09", "0.00", "0.09", "0.66", "4.12", "3.70", "0.00" }, 
    { "Ma21-12-1-GI", "77.94", "0.12", "12.06", "1.06", "0.00", "0.05", "0.71", "4.25", "3.81", "0.00" }, 
    { "Ma21-12-2-GI", "77.65", "0.08", "12.10", "1.14", "0.00", "0.13", "0.73", "4.33", "3.84", "0.00" }, 
    { "Ma22-1-GI", "78.00", "0.07", "12.21", "0.94", "0.00", "0.05", "0.54", "4.06", "4.13", "0.00" }, 
    { "Ma23-41-GI", "77.83", "0.14", "12.06", "1.06", "0.00", "0.09", "0.71", "4.38", "3.72", "0.00" }, 
    { "Ma23-44-GI", "77.13", "0.17", "11.93", "1.11", "0.00", "0.11", "0.76", "4.64", "4.15", "0.00" }, 
    { "Ma26-17-GI", "77.65", "0.06", "12.38", "1.08", "0.00", "0.06", "0.63", "4.04", "4.10", "0.00" }, 
    { "Ma54-33-GI", "78.16", "0.14", "12.14", "0.94", "0.00", "0.04", "0.53", "3.88", "4.17", "0.00" }, 
    { "Ma54-34-GI", "77.57", "0.12", "12.21", "0.94", "0.00", "0.07", "0.57", "4.19", "4.32", "0.00" }, 
    { "Ma54-35-GI", "77.89", "0.15", "12.16", "0.91", "0.00", "0.04", "0.55", "4.18", "4.12", "0.00" }, 
    { "Ma57-28-GI", "78.09", "0.00", "12.20", "0.92", "0.00", "0.02", "0.52", "4.10", "4.15", "0.00" }, 
    { "Ma57-30-GI", "77.87", "0.10", "12.22", "1.09", "0.00", "0.02", "0.64", "4.01", "4.04", "0.00" }, 
    { "Ma57-32-GI", "77.93", "0.07", "12.15", "0.99", "0.00", "0.03", "0.56", "4.26", "4.01", "0.00" }, 
    { "Oh160a-6-GI", "78.40", "0.11", "12.03", "1.06", "0.00", "0.02", "0.65", "4.10", "3.62", "0.00" }  
  };
  
  char *string = (char *) malloc(500*sizeof(char));
  int i;
  
  system("rm -rf GUIL-RUNS");
  system("mkdir GUIL-RUNS");
  
  for (i=0; i<144; i++) {
  
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
  strcat(string, "12.0");            /* H2O   */
  strcat(string, " 5000.0");
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
  strcat(string, "12.0");            /* H2O   */
  strcat(string, " 4750.0");
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
  strcat(string, "12.0");            /* H2O   */
  strcat(string, " 4500.0");
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
  strcat(string, "12.0");            /* H2O   */
  strcat(string, " 4250.0");
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
  strcat(string, "12.0");            /* H2O   */
  strcat(string, " 4000.0");
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
  strcat(string, "12.0");            /* H2O   */
  strcat(string, " 3750.0");
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
  strcat(string, "12.0");            /* H2O   */
  strcat(string, " 3500.0");
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
  strcat(string, "12.0");            /* H2O   */
  strcat(string, " 3250.0");
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
  strcat(string, "12.0");            /* H2O   */
  strcat(string, " 3000.0");
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
  strcat(string, "12.0");            /* H2O   */
  strcat(string, " 2750.0");
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
  strcat(string, "12.0");            /* H2O   */
  strcat(string, " 2500.0");
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
  strcat(string, "12.0");            /* H2O   */
  strcat(string, " 2250.0");
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
  strcat(string, "12.0");            /* H2O   */
  strcat(string, " 2000.0");
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
  strcat(string, "12.0");            /* H2O   */
  strcat(string, " 1750.0");
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
  strcat(string, "12.0");            /* H2O   */
  strcat(string, " 1500.0");
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
  strcat(string, "12.0");            /* H2O   */
  strcat(string, " 1250.0");
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
  strcat(string, "12.0");            /* H2O   */
  strcat(string, " 1000.0");
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
  strcat(string, "12.0");            /* H2O   */
  strcat(string, " 750.0");
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
  strcat(string, "12.0");            /* H2O   */
  strcat(string, " 500.0");
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
  strcat(string, "12.0");            /* H2O   */
  strcat(string, " 250.0");
  system(string);
  
  }

}