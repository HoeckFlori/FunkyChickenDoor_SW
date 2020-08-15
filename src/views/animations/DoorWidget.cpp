#include "DoorWidget.hpp"
#include "../../IDoorSteering.hpp"

DoorWidget::DoorWidget(IModel *model, Adafruit_GFX *tft,
                       uint16_t colorBackground,
                       uint16_t colorFrames,
                       uint16_t colorText,
                       int16_t x0, int16_t y0)
    : WidgetBase(model, tft,
                 colorBackground,
                 colorFrames,
                 colorText,
                 x0, y0),
      m_doorflapPreviousPercentOpen(-1),
      m_animationClosingActive(false),
      m_animationOpeningActive(false),
      m_animationInitialization(false),
      m_animationCounterRunner(0),
      m_lastAnimationTimestamp(0)
{
}

void DoorWidget::setup()
{
    // draw the frame of the complete 'door arrangement'
    m_tft->fillRoundRect(m_x0, m_y0, m_outerWidth, m_outerHeight, /*radius*/ 0, m_defaultColorFrames);
    drawClearInnerPartOfTheDoorAssembly();
}

int16_t DoorWidget::getWidthOfWidget()
{
    return m_outerWidth;
}

int16_t DoorWidget::getHeightOfWidget()
{
    return m_outerHeight;
}

void DoorWidget::cycle()
{
    doorAnimationCycle();
    initializationCycle();
}

void DoorWidget::passModelEventToWidget(IModelEventListener::Event event)
{
    switch (event)
    {
    case IModelEventListener::Event::DOOR_STATE_CHANGED:
        // todo, here we work
        if (m_model)
        {
            auto doorState = m_model->getDoorState();
            switch (doorState)
            {
            case IDoorSteering::DoorState::UNDEFINED:
                stopAnimations();
                //drawError(); // may change this to an '?' state
                break;
            case IDoorSteering::DoorState::INITIALIZING:
                startAnimationInitialization();
                break;
            case IDoorSteering::DoorState::OPEN:
                stopAnimations();
                drawDoorflap(100 /* percentOpen */);
                break;
            case IDoorSteering::DoorState::CLOSED:
                stopAnimations();
                drawDoorflap(0 /* percentOpen */);
                break;
            case IDoorSteering::DoorState::OPENING:
                startAnimationOpening();
                break;
            case IDoorSteering::DoorState::CLOSING:
                startAnimationClosing();
                break;
            case IDoorSteering::DoorState::ERROR:
                stopAnimations();
                drawError();
                break;
            }
        }
        break;
    default:
        break;
    }
}

void DoorWidget::drawClearInnerPartOfTheDoorAssembly()
{
    m_tft->fillRoundRect(m_x0 + m_outerFrameThickness,
                         m_y0 + m_outerFrameThickness,
                         m_outerWidth - 2 * m_outerFrameThickness,
                         m_outerHeight - 2 * m_outerFrameThickness,
                         /*radius*/ 1,
                         m_defaultColorBackground);
}

void DoorWidget::drawDoorflap(uint8_t percentOpen)
{
    // check and correct upper limit if needed
    percentOpen = percentOpen > 100 ? 100 : percentOpen;

    auto yOffset = m_doorflapYRange * (100 - percentOpen) / 100;


    if (m_doorflapPreviousPercentOpen < 0)
    { // draw complete door
        drawClearInnerPartOfTheDoorAssembly();
        m_tft->fillRoundRect(m_doorflapX0,
                             m_doorflapY0 + yOffset, // !
                             m_doorflapWidth,
                             m_doorflapHeight,
                             /*radius*/ 0,
                             m_doorflapColor);
    }
    else
    {
        // calculate previous offset
        auto yOffsetPrevious = m_doorflapYRange * (100 - m_doorflapPreviousPercentOpen) / 100;
        
        // draw new additional part of the door
        if (yOffset < yOffsetPrevious)
        { // new part above
            m_tft->fillRoundRect(m_doorflapX0,
                                 m_doorflapY0 + yOffset, // !
                                 m_doorflapWidth,
                                 yOffsetPrevious - yOffset,
                                 /*radius*/ 0,
                                 m_doorflapColor);
        }
        else
        { // new part below
            m_tft->fillRoundRect(m_doorflapX0,
                                 m_doorflapY0 + yOffsetPrevious + m_doorflapHeight, // !
                                 m_doorflapWidth,
                                 yOffset - yOffsetPrevious,
                                 /*radius*/ 0,
                                 m_doorflapColor);
        }

        // delete now not longer need part of the door
        if (yOffset < yOffsetPrevious)
        { // new part above -> delete the part below
            m_tft->fillRoundRect(m_doorflapX0,
                                 m_doorflapY0 + yOffset + m_doorflapHeight, // !
                                 m_doorflapWidth,
                                 yOffsetPrevious - yOffset,
                                 /*radius*/ 0,
                                 m_defaultColorBackground);
        }
        else
        { // new part below -> delete the part above
            m_tft->fillRoundRect(m_doorflapX0,
                                 m_doorflapY0 + yOffsetPrevious, // !
                                 m_doorflapWidth,
                                 yOffset - yOffsetPrevious,
                                 /*radius*/ 0,
                                 m_defaultColorBackground);
        }
    }

    // save opening state for next frame to speed up the animation time
    m_doorflapPreviousPercentOpen = percentOpen;
}

void DoorWidget::drawError()
{
    drawClearInnerPartOfTheDoorAssembly();

    auto xCenter = m_x0 + m_outerWidth / 2;
    auto yCenter = m_y0 + m_outerHeight / 2;

    // Warning sign
    m_tft->fillTriangle(xCenter, yCenter - 20,      // top
                        xCenter - 17, yCenter + 10, // left
                        xCenter + 17, yCenter + 10, // right
                        ST7735_RED);
    m_tft->fillTriangle(xCenter, yCenter - 17,     // top
                        xCenter - 14, yCenter + 8, // left
                        xCenter + 14, yCenter + 8, // right
                        ST7735_YELLOW);

    // Exclamation mark
    m_tft->fillRect(xCenter - 1, yCenter - 10, 3, 12, ST7735_RED);
    m_tft->fillRect(xCenter - 1, yCenter + 4, 3, 3, ST7735_RED);
}

void DoorWidget::startAnimationOpening()
{
    m_animationOpeningActive = true; // (!)
    m_animationClosingActive = false;
    m_animationInitialization = false;
    m_doorflapPreviousPercentOpen = -1;
    drawClearInnerPartOfTheDoorAssembly();
    m_lastAnimationTimestamp = millis();
}

void DoorWidget::startAnimationClosing()
{
    m_animationOpeningActive = false;
    m_animationClosingActive = true; // (!)
    m_animationInitialization = false;
    m_doorflapPreviousPercentOpen = -1;
    drawClearInnerPartOfTheDoorAssembly();
    m_lastAnimationTimestamp = millis();
}

void DoorWidget::startAnimationInitialization()
{
    m_animationOpeningActive = false;
    m_animationClosingActive = false;
    m_animationInitialization = true; // (!)
    drawClearInnerPartOfTheDoorAssembly();
    m_lastAnimationTimestamp = millis();
    m_tft->setCursor(m_x0 + 9, m_y0 + (4 * m_outerHeight / 5));
    m_tft->setTextSize(1);
    m_tft->setTextColor(m_defaultColorText);
    m_tft->print(F("init"));
}

void DoorWidget::stopAnimations()
{
    m_animationClosingActive = false;
    m_animationOpeningActive = false;
    m_animationInitialization = false;
    m_doorflapPreviousPercentOpen = -1;
    m_animationCounterRunner = 0;
}

void DoorWidget::doorAnimationCycle()
{
    // check if animation work is to do
    if (m_animationOpeningActive || m_animationClosingActive)
    {
        auto currentTime = millis();
        if (currentTime >= m_lastAnimationTimestamp + m_animationTimeStepsInMs)
        { // time for a new animation step
            m_lastAnimationTimestamp = currentTime;

            // draw new door position
            if (m_animationOpeningActive)
            { // 'moving up' animation
                drawDoorflap((m_animationCounterRunner * 100) / m_animationCounterMax);
            }
            else
            { // 'moving down' animation
                drawDoorflap(100 - ((m_animationCounterRunner * 100) / m_animationCounterMax));
            }

            // update position
            m_animationCounterRunner++;
            if (m_animationCounterRunner > m_animationCounterMax)
            {
                m_animationCounterRunner = 0;
            }
        }
    }
    // Hint: I know that the animation can get into struggle, when the tickcoutner has an overflow.
    //       But this happens approximately each 50 days and the animation has to run during that.
    //       The coincidence of the two events is unlikely and would only disturb the animation, but
    //       nothing else.
}

void DoorWidget::initializationCycle()
{
    if (m_animationInitialization)
    {
        auto currentTime = millis();
        if (currentTime >= m_lastAnimationTimestamp + m_animationTimeStepsInMs)
        { // time for a new animation step
            m_lastAnimationTimestamp = currentTime;

            // clear previous sector
            auto sector = m_animationCounterRunner % 4; // we work with 4 sectors (0-3)
            drawInitializationSektorHelper(sector, /*clear sector*/ true);

            // draw new sector
            m_animationCounterRunner++;
            sector = m_animationCounterRunner % 4; // we work with 4 sectors (0-3)
            drawInitializationSektorHelper(sector, /*clear sector*/ false);
        }
    }
}

void DoorWidget::drawInitializationSektorHelper(int sector, bool clearSector)
{
    auto const xdiff = 6;
    auto const ydiff = 6;

    int xCenterSector(0);
    int yCenterSector(0);

    switch (sector)
    {
    case 0:
        // left, down
        xCenterSector = m_xCenter - xdiff;
        yCenterSector = m_yCenter + ydiff;
        break;
    case 1:
        // left, up
        xCenterSector = m_xCenter - xdiff;
        yCenterSector = m_yCenter - ydiff;
        break;
    case 2:
        // right, up
        xCenterSector = m_xCenter + xdiff;
        yCenterSector = m_yCenter - ydiff;
        break;
    case 3:
        // right, down
        xCenterSector = m_xCenter + xdiff;
        yCenterSector = m_yCenter + ydiff;
        break;
    default:
        break;
    }

    if (clearSector)
        m_tft->fillCircle(xCenterSector, yCenterSector, 8, m_defaultColorBackground);
    else
        m_tft->fillCircle(xCenterSector, yCenterSector, 8, m_defaultColorFrames);
}