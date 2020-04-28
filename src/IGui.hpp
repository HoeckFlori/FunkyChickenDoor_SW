#pragma once

class IGui
{
public:
    virtual ~IGui() = default;

    virtual void turnOnDisplay() = 0;
    virtual void turnOffDisplay() = 0;
    virtual void showScreen(int screen) = 0;
    virtual void writeNumber(int number) = 0;
    virtual void writeTime(int hour, int minute, int second) = 0;

    // may for a derived interface

    // virtual void printTime() = 0;
    // virtual void printErrorScreen(String errorMessage) = 0;
    // virtual void printClosingTime() = 0;
    // virtual void printOpeningTime() = 0;
};