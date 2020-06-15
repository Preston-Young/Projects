// The job of an InteractionProcessor is to wait for interactions (e.g., the
// user pressing keys on the keyboard) and then to make the appropriate changes
// on the EditorModel and EditorView as a result.


#ifndef INTERACTIONPROCESSOR_HPP
#define INTERACTIONPROCESSOR_HPP

#include "EditorModel.hpp"
#include "EditorView.hpp"
#include "InteractionReader.hpp"



class InteractionProcessor
{
public:
    InteractionProcessor(
        EditorModel& model, EditorView& view,
        InteractionReader& interactionReader)
        : model{model}, view{view}, interactionReader{interactionReader}
    {
    }

    void run();

private:
    EditorModel& model;
    EditorView& view;
    InteractionReader& interactionReader;
};



#endif // INTERACTIONPROCESSOR_HPP

