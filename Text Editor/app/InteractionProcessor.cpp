#include "InteractionProcessor.hpp"
#include "EditorException.hpp"
#include "Interaction.hpp"
#include "CommandStacks.hpp"



void InteractionProcessor::run()
{
    view.refresh();

    Stacks undoStack = Stacks();
    Stacks redoStack = Stacks();

    while (true)
    {
        Interaction interaction = interactionReader.nextInteraction();

        if (interaction.type() == InteractionType::quit)
        {
            break;
        }
        else if (interaction.type() == InteractionType::undo)
        {
            if (not undoStack.isEmpty())
            {
                Command* tempCommand = undoStack.pop();
                tempCommand->undo(model); // Calls top command's undo method by polymorphism

                redoStack.push(tempCommand);

                model.clearErrorMessage();
            }

            view.refresh();
        }
        else if (interaction.type() == InteractionType::redo)
        {
            if (not redoStack.isEmpty())
            {
                Command* tempCommand = redoStack.pop();
                tempCommand->execute(model);

                undoStack.push(tempCommand);
            }

            view.refresh();
        }
        else if (interaction.type() == InteractionType::command)
        {
            Command* command = interaction.command();

            try
            {

                command->execute(model);

                model.clearErrorMessage();

                undoStack.push(command); // Add new command to the top of the undo stack
                redoStack.clear(); // Since a new command was executed, there's nothing to redo anymore
            }
            catch (EditorException& e)
            {
                model.setErrorMessage(e.getReason());
                delete command;
            }

            view.refresh();
        }
    }
}

