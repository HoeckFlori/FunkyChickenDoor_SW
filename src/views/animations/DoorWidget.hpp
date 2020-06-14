#pragma once

#include "WidgetBase.hpp"
#include "../../IDoorSteering.hpp"

/**
 * @brief The DoorWidget show the door with its different states
 */
class DoorWidget : public WidgetBase
{
public:
    DoorWidget(IModel *model, Adafruit_GFX *tft,
               uint16_t colorBackground,
               uint16_t colorFrames,
               uint16_t colorText,
               int16_t x0, int16_t y0);
    ~DoorWidget() = default;

    // IWidget
    void setup() override;
    int16_t getWidthOfWidget() override;
    int16_t getHeightOfWidget() override;
    void cycle() override;
    void passModelEventToWidget(IModelEventListener::Event event) override;

private:
    const int16_t m_outerWidth = 42;
    const int16_t m_outerHeight = 88;
    const int16_t m_outerFrameThickness = 2;
    const int16_t m_doorflapWidth = m_outerWidth - 2 * m_outerFrameThickness;
    const int16_t m_doorflapHeight = m_doorflapWidth; // we have a square flap

    const int16_t m_xCenter = m_x0 + m_outerWidth / 2;
    const int16_t m_yCenter = m_y0 + m_outerHeight / 2;

    /**
     * @brief Clear/Erase the inner part of the door assemlby. Means repaint it with the
     *        the default background color.
     */
    void drawClearInnerPartOfTheDoorAssembly();

    /**
     * @brief Draw the doorflap (the board which is moving up and down to seal the chicken coop)
     *        into the inner frame.
     * 
     * @param percentOpen The opening degree in percent. 0%(closed), 100%(open)
     */
    void drawDoorflap(uint8_t percentOpen);

    /**
     * @brief Draw the error screen of the widget. An exclamation mark in a warning sign
     *        in the middle of the widget.
     */
    void drawError();

    bool m_animationClosingActive;
    bool m_animationOpeningActive;
    bool m_animationInitialization;
    int16_t m_animationCounterRunner;
    const int16_t m_animationCounterMax = 8;
    const int16_t m_animationTimeStepsInMs = 200;
    unsigned long m_lastAnimationTimestamp;

    /**
     * @brief Activate the animation for the door opening.
     *        (The door is slowly animated upwards)
     */
    void startAnimationOpening();

    /**
     * @brief Activate the animation for the door closing.
     *        (The door is slowly animated downwards)
     */
    void startAnimationClosing();

    /**
     * @brief Activate the animation for the Initialization.
     */
    void startAnimationInitialization();

    /**
     * @brief Stop all (may running animations)
     */
    void stopAnimations();

    /**
     * @brief The "cycle method" for the door animations.
     */
    void doorAnimationCycle();

    /**
     * @brief The "cycle method" for the initialization;
     * 
     */
    void initializationCycle();

    /**
     * @brief Helper method to draw/delete a "Sector" from the Initialization animation
     * 
     * @param sector The sector to draw/delete (0-3)
     * @param clearSector If true, the sector gets deleted/overwritten with the default background color.
     */
    void drawInitializationSektorHelper(int sector, bool clearSector);
};