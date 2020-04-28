#pragma once

// forward declaration
class DateTime;

class IModel
{
public:
    virtual ~IModel() {}

    DateTime getCurrentTime();
};