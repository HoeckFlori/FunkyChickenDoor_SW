// #include "xmem.h"
#include "Arduino.h"

extern uint16_t __heap_start, __heap_end;
extern uint16_t __bss_start, __bss_end;
extern uint16_t __data_start, __data_end;

extern void *__brkval;

void print4hex(uint16_t adr)
{
    Serial.print(F("0x"));
    if (adr < 0x1000)
    {
        Serial.print(F("0"));
    };
    if (adr < 0x0100)
    {
        Serial.print(F("0"));
    };
    if (adr < 0x0010)
    {
        Serial.print(F("0"));
    };
    Serial.print(adr, HEX);
};

void GetMemoryInformation()
{
    Serial.println(F("\nMemory Information:\n-------------------"));

    Serial.println(F("General:"));

    print4hex(RAMSTART);
    Serial.println(F(" RAM start"));
    print4hex(RAMEND);
    Serial.println(F(" RAM end"));

    Serial.println(F("\nDetails:"));

    print4hex((uint16_t)&__data_start);
    Serial.println(F(" __data_start"));

    print4hex((uint16_t)&__data_end);
    Serial.println(F(" __data_end"));

    print4hex((uint16_t)&__bss_start);
    Serial.println(F(" __bss_start"));

    print4hex((uint16_t)&__bss_end);
    Serial.println(F(" __bss_end"));

    print4hex((uint16_t)&__heap_start);
    Serial.println(F(" __heap_start"));

    print4hex((uint16_t)&__heap_end);
    Serial.println(F(" __heap_end"));

    print4hex((uint16_t)__malloc_heap_start);
    Serial.println(F(" __malloc_heap_start"));

    print4hex((uint16_t)__malloc_heap_end);
    Serial.println(F(" __malloc_heap_end"));

    Serial.println(F("\nInternals:"));

    print4hex((uint16_t)&__brkval);
    Serial.println(F(" __brkval"));

    print4hex((uint16_t)__brkval);
    Serial.println(F(" __brkval - content"));

    print4hex((uint16_t)SP);
    Serial.println(F(" SP (call stack pointer)"));
};

void GetFreeMemory(bool withExploitation)
{
    Serial.println(F("\nRAM usage:\n----------"));

    uint8_t variableToPlaceInStack;
    uint16_t freeMemory = (((uint16_t)&variableToPlaceInStack) - ((uint16_t)__brkval));
    Serial.print(F("\nFree Memory:  "));
    Serial.print(freeMemory);
    Serial.print(F(" dec ("));
    print4hex(freeMemory);
    Serial.println(F(")"));

    if (withExploitation)
    {
        uint16_t completeRam = RAMEND - RAMSTART;
        Serial.print(F("Complete RAM: "));
        Serial.print(completeRam);
        Serial.print(F(" dec ("));
        print4hex(completeRam);
        Serial.println(F(")"));

        uint16_t freeInPercent = (uint32_t)freeMemory * 100 / (uint32_t)completeRam;
        Serial.print(F("Used: "));
        Serial.print(100 - freeInPercent);
        Serial.println(F(" %"));
    }
};