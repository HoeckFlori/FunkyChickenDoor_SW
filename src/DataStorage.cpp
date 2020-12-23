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
        formatMemory();
        // write 0xAA on position 0 of the EEPROM to shows that it is formatted
        EEPROM.write(_formatInfo, 0xAA);
        Serial.println(F("... done!"));
    }
}

void DataStorage::formatMemory()
{
    for (uint16_t i(0); i < EEPROM.length(); i++)
    {
        EEPROM.write(i, 0x00);
    }
}

void DataStorage::setDayLightSavingSetting(bool daylightsaving)
{
    EEPROM.write(_daylightSaving, uint8_t(daylightsaving));
}

bool DataStorage::getDayLightSavingSetting() const
{
    return bool(EEPROM.read(_daylightSaving));
}

void DataStorage::setPosition(const IDataStorage::positionOption &position)
{
    EEPROM.put(_position, position);
}

IDataStorage::positionOption DataStorage::getPosition() const
{
    IDataStorage::positionOption retVal;
    retVal = EEPROM.get(_position, retVal);
    return retVal;
}

void DataStorage::setOperationMode(int opMode)
{
    EEPROM.put(_operationMode, opMode);
}

int DataStorage::getOperationMode() const
{
    int retVal(0);
    retVal = EEPROM.get(_operationMode, retVal);
    return retVal;
}

void DataStorage::setDoNotOpenBeforeOption(const IDataStorage::doNotOpenBeforeOption &setting)
{
    EEPROM.put(_doNotOpenBeforeOption, setting);
}

IDataStorage::doNotOpenBeforeOption DataStorage::getDoNotOpenBeforeOption()
{
    IDataStorage::doNotOpenBeforeOption retVal;
    retVal = EEPROM.get(_doNotOpenBeforeOption, retVal);
    return retVal;
}

void DataStorage::setClosingDelayOption(const IDataStorage::closingDelayOption &setting)
{
    EEPROM.put(_closingDelayOption, setting);
}

IDataStorage::closingDelayOption DataStorage::getClosingDelayOption()
{
    IDataStorage::closingDelayOption retVal;
    retVal = EEPROM.get(_closingDelayOption, retVal);
    return retVal;
}

void DataStorage::setArtificialMorningLightOption(const IDataStorage::artificialMorningLightOption &setting)
{
    EEPROM.put(_artificialMorningLightOption, setting);
}

IDataStorage::artificialMorningLightOption DataStorage::getArtificialMorningLightOption()
{
    IDataStorage::artificialMorningLightOption retVal;
    retVal = EEPROM.get(_artificialMorningLightOption, retVal);
    return retVal;
}

void DataStorage::setDoorMovingTimeout(uint16_t timeoutSec)
{
    EEPROM.put(_doorMovingTimeout, timeoutSec);
}

uint16_t DataStorage::getDoorMovingTimeout()
{
    uint16_t retVal(0);
    retVal = EEPROM.get(_doorMovingTimeout, retVal);
    return retVal;
}
