#include "KeypressInteractionReader.hpp"
#include "CursorRight.hpp"
#include "CursorLeft.hpp"
#include "InsertChar.hpp"
#include "newLine.hpp"
#include "CursorUp.hpp"
#include "CursorDown.hpp"
#include "CursorHome.hpp"
#include "CursorEnd.hpp"
#include "deleteLine.hpp"
#include "Backspace.hpp"

Interaction KeypressInteractionReader::nextInteraction()
{
    while (true)
    {
        Keypress keypress = keypressReader.nextKeypress();

        Command* new_command = nullptr;

        if (keypress.ctrl())
        {
            // The user pressed a Ctrl key (e.g., Ctrl+X); react accordingly

            switch (keypress.code())
            {
            case 'Q':
                return Interaction::quit();

            case 'L':
                new_command = new CursorRight();
                return Interaction::command(new_command);

            case 'J':
                new_command = new CursorLeft();
                return Interaction::command(new_command);

            case 'I':
                new_command = new CursorUp();
                return Interaction::command(new_command);

            case 'K':
                new_command = new CursorDown();
                return Interaction::command(new_command);

            case 'Z':
                return Interaction::undo();

            case 'Y':
                return Interaction::redo();

            case 'N':
                new_command = new newLine();
                return Interaction::command(new_command);

            case 'H':
                new_command = new CursorHome();
                return Interaction::command(new_command);

            case 'U':
                new_command = new CursorEnd();
                return Interaction::command(new_command);

            case 'B':
                new_command = new deleteLine();
                return Interaction::command(new_command);

            case 'O':
                new_command = new Backspace();
                return Interaction::command(new_command);

            }
        }
        else
        {
            // The user pressed a normal key (e.g., 'h') without holding
            // down Ctrl; react accordingly
            new_command = new InsertChar(keypress.code());
            return Interaction::command(new_command);
        }
    }
}

