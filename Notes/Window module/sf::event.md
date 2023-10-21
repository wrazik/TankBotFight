### sf::Event

# typical usage of sf::Event

sf::Event event;

// while there are pending events...
while (window.pollEvent(event))
{
    // check the type of the event...
    switch (event.type)
    {
        // window closed
        case sf::Event::Closed:
            window.close();
            break;

        // key pressed
        case sf::Event::KeyPressed:
            ...
            break;

        // we don't process other types of events
        default:
            break;
    }
}

# The Closed event
The sf::Event::Closed event is triggered when the user wants to close the window, through any of the possible methods.
The event only represent a close request, the window is not closed yet when the event is received.

We can save current state of game and close window.

# The Resized event
The sf::Event::Resized event is triggered when the window is resized (by user or e.g. calling window.setSize).

# The LostFocus and GainedFocus events
The sf::Event::LostFocus and sf::Event::GainedFocus events are triggered when the window loses/gains focus, which happens when the user switches the currently active window.
When the window is out of focus, it doesn't receive keyboard events.

 There's no member associated with these events in the sf::Event union.

if (event.type == sf::Event::LostFocus)
    myGame.pause();

if (event.type == sf::Event::GainedFocus)
    myGame.resume();

# Other event such as keyboard or mouse input.
https://www.sfml-dev.org/tutorials/2.6/window-events.php


## Keyboard input tips
 Sometimes, people try to react to KeyPressed events directly to implement smooth movement. Doing so will not produce the expected effect, because when you hold a key you only get a few events (remember, the repeat delay). To achieve smooth movement with events, you must use a boolean that you set on KeyPressed and clear on KeyReleased; you can then move (independently of events) as long as the boolean is set.
The other (easier) solution to produce smooth movement is to use real-time keyboard input with sf::Keyboard (see the dedicated tutorial). 

 Scancodes are unique values for each physical key on a keyboard, regardless of the language or layout, whereas key codes represent keys based on the user's chosen layout. For instance, the Z key is in the bottom row to the left of the X key on a US layout. Referring to the scancode for Z would identify this physical key location on any keyboard. However, on a German layout, the same physical key is labeled Y. Thus, using the key code for Y can lead to different physical key locations, depending on the chosen layout.

It is strongly recommended to use scancodes over key codes if the physical location of the keys is more important than the key values that depend on the keyboard layout, such as using WASD keys for movement. 