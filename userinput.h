/**
 * @file camera3D.h
 * @author Trent Reed, Carlo Sarli
 * @date 30 August 2019
 * @brief This class provides Camera functionalty for  the canvas.
 *
 * Detailed description goes here.
 */

#ifndef USERINPUT_H
#define USERINPUT_H

#include <Qt>
#include <QPoint>
#include <QCursor>
#include <vector>
#include <algorithm>

class UserInput
{
public:

    // Possible key states
    enum InputState
    {
        InputInvalid,
        InputRegistered,
        InputUnregistered,
        InputTriggered,
        InputPressed,
        InputReleased
    };

    // State checking
    static InputState keyState(Qt::Key key);
    static bool keyTriggered(Qt::Key key);
    static bool keyPressed(Qt::Key key);
    static bool keyReleased(Qt::Key key);
    static InputState buttonState(Qt::MouseButton button);
    static bool buttonTriggered(Qt::MouseButton button);
    static bool buttonPressed(Qt::MouseButton button);
    static bool buttonReleased(Qt::MouseButton button);
    static QPoint mousePosition();
    static QPoint mouseDelta();

private:

    // State updating
    static void update();
    static void registerKeyPress(int key);
    static void registerKeyRelease(int key);
    static void registerMousePress(Qt::MouseButton button);
    static void registerMouseRelease(Qt::MouseButton button);
    static void reset();
    friend class Canvas;
};

inline bool UserInput::keyTriggered(Qt::Key key)
{
    return keyState(key) == InputTriggered;
}

inline bool UserInput::keyPressed(Qt::Key key)
{
    return keyState(key) == InputPressed;
}

inline bool UserInput::keyReleased(Qt::Key key)
{
    return keyState(key) == InputReleased;
}

inline bool UserInput::buttonTriggered(Qt::MouseButton button)
{
    return buttonState(button) == InputTriggered;
}

inline bool UserInput::buttonPressed(Qt::MouseButton button)
{
    return buttonState(button) == InputPressed;
}

inline bool UserInput::buttonReleased(Qt::MouseButton button)
{
    return buttonState(button) == InputReleased;
}

#endif // QINPUT_H
