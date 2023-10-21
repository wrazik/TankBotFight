### OpenGL in SFML

As you know, one of the most important features of OpenGL is portability. But OpenGL alone won't be enough to create complete programs: you need a window, a rendering context, user input, etc. You would have no choice but to write OS-specific code to handle this stuff on your own. That's where the sfml-window module comes into play. Let's see how it allows you to play with OpenGL. 

# Including and linking OpenGL

OpenGL headers are not the same on every OS. Therefore, SFML provides an "abstract" header that takes care of including the right file for you.

`#include <SFML/OpenGL.hpp>`

This header includes OpenGL functions, and nothing else. People sometimes think that SFML automatically includes OpenGL extension headers because SFML loads extensions itself, but it's an implementation detail. From the user's point of view, OpenGL extension loading must be handled like any other external library.

You will then need to link your program to the OpenGL library. Unlike what it does with the headers, SFML can't provide a unified way of linking OpenGL. Therefore, you need to know which library to link to according to what operating system you're using ("opengl32" on Windows, "GL" on Linux, etc.).

OpenGL functions start with the "gl" prefix. Remember this when you get linker errors, it will help you find which library you forgot to link. 

## Creating an OpenGL window

Since SFML is based on OpenGL, its windows are ready for OpenGL calls without any extra effort.

sf::Window window(sf::VideoMode(800, 600), "OpenGL");

// it works out of the box
glEnable(GL_TEXTURE_2D);
...


## A typical OpenGL-with-SFML program

 Here is what a complete OpenGL program would look like with SFML:

#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

int main()
{
    // create the window
    sf::Window window(sf::VideoMode(800, 600), "OpenGL", sf::Style::Default, sf::ContextSettings(32));
    window.setVerticalSyncEnabled(true);

    // activate the window
    window.setActive(true);

    // load resources, initialize the OpenGL states, ...

    // run the main loop
    bool running = true;
    while (running)
    {
        // handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                // end the program
                running = false;
            }
            else if (event.type == sf::Event::Resized)
            {
                // adjust the viewport when the window is resized
                glViewport(0, 0, event.size.width, event.size.height);
            }
        }

        // clear the buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // draw...

        // end the current frame (internally swaps the front and back buffers)
        window.display();
    }

    // release resources...

    return 0;
}

Here we don't use window.isOpen() as the condition of the main loop, because we need the window to remain open until the program ends, so that we still have a valid OpenGL context for the last iteration of the loop and the cleanup code.

Don't hesitate to have a look at the "OpenGL" and "Window" examples in the SFML SDK if you have further problems, they are more complete and most likely contain solutions to your problems. 