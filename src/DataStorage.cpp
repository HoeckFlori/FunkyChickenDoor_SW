#include "DataStorage.hpp"
#include <Arduino.h>
#include <EEPROM.h> // EEPROM: 1024 bytes on the ATmega328P

// https://www.arduino.cc/en/Reference/EEPROM

DataStorage::DataStorage()
{
    // check if EEPROM is "formated", else do so (important for first run)
    if (EEPROM.read(_formatInfo) != 0xAA)
    {
        Serial.println(F("EEPROM is not formated! Formating ..."));

        // write 0xAA on position 0 of the EEPROM to shows that it is formatted
        EEPROM.write(_formatInfo, 0xAA);

        // clear rest of the EEPROM (set all memory cells to 0x00)
        for (uint16_t i(_formatInfo + 1); i < EEPROM.length(); i++)
        {
            EEPROM.write(i, 0x00);
        }

        Serial.println(F("... done!"));
    }
}

bool DataStorage::getDayLightSavingSetting() const
{
    return bool(EEPROM.read(_daylightSaving));
}

void DataStorage::setDayLightSavingSetting(bool daylightsaving)
{
    EEPROM.write(_daylightSaving, uint8_t(daylightsaving));
}

void DataStorage::setPosition(float latitude, float longitude, float timezone)
{
    EEPROM.put(_latitude, latitude);
    EEPROM.put(_longitude, longitude);
    EEPROM.put(_timeZone, timezone);
}

float DataStorage::getPositionLatitude() const
{
    float retVal(0.00f);
    retVal = EEPROM.get(_latitude, retVal);
    return retVal;
}

float DataStorage::getPositionLongitude() const
{
    float retVal(0.00f);
    retVal = EEPROM.get(_longitude, retVal);
    return retVal;
}

float DataStorage::getTimeZone() const
{
    float retVal(0.00f);
    retVal = EEPROM.get(_timeZone, retVal);
    return retVal;
}