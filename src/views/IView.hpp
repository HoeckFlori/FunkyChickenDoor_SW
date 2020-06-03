#pragma once

/**
 * @brief The base interface for all views of the here used MVC pattern. The Controller
 *        just knowns this interface.
 */
class IView
{
public:
    virtual ~IView() = default;

    /**
     * @brief The cycle method that must be called regulary from the 'main-cycle'
     */
    virtual void cycle() = 0;
};