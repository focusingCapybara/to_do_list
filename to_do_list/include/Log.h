// Templates need to be in a header file due to the way templates are compiled

#pragma once

#define NOMINMAX // Otherwise it will interfere with std::max and std::min
#include <Windows.h> // For modifying the console
#include "../include/Log.h" // Declaration

#include <iostream> // For printing to the console

enum Colour {
    RED = 4,
    GREEN = 2,
    BLUE = 1
};

template<typename T>
void setMessageColour(Colour colourCode, const T& MESSAGE) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, colourCode);
    std::cout << MESSAGE;
    SetConsoleTextAttribute(hConsole, 7);
}

template<typename T>
void Log(const T& MESSAGE) {
    std::cout << MESSAGE;
}

template<typename T>
void pathLog(const T& MESSAGE) {
    setMessageColour(BLUE, MESSAGE);
}

template<typename T>
void successLog(const T& MESSAGE) {
    setMessageColour(GREEN, MESSAGE);
}

template<typename T>
void errorLog(const T& MESSAGE) {
    setMessageColour(RED, MESSAGE);
}