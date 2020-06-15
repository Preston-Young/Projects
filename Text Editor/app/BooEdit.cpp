#include "BooEdit.hpp"
#include "InteractionProcessor.hpp"


void BooEdit::run()
{
    view.start();

    InteractionProcessor processor{model, view, interactionReader};
    processor.run();
}


BooEdit::~BooEdit()
{
    view.stop();
}

