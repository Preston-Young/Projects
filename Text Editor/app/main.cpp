// This was my final academic project for my intro to C++ class. My
// professor, Alex Thornton, gave us about a third of the modules. It
// was my job to understand what he had written already, inherit
// from whatever classes I needed to, and build new code to create the
// full text editor. It still took an incredible amount of hours to work
// perfectly, and with no memory leaks, but I'm extremely happy with how
// it turned out. I left this comment that professor Thornton wrote here,
// and a few others so it would help tie a few of these files together and
// even give him a bit of credit for the code he wrote himself.
//
// This is the main() function that launches the text editor, along with some
// additional things that are fairly hairy-looking.  The goal here is
// to be sure that the program, whenever possible, crashes in a way that
// leaves the Linux shell window available and fully operative afterward.
// For example, I'm calling into functions from the C Standard Library
// that set up "signal handlers" that are called just before the program
// crashes due to problems like segmentation faults, so I can shut down
// the "ncurses" library used to handle things like cursor manipulation,
// and return the Linux shell to a usable state.

#include <csignal>
#include <sstream>
#include "BooEdit.hpp"
#include "BooEditLog.hpp"
#include "EditorModel.hpp"
#include "KeypressInteractionReader.hpp"
#include "NcursesEditorView.hpp"
#include "NcursesKeypressReader.hpp"



namespace
{
    BooEdit* booEdit = nullptr;
    EditorModel model;
    NcursesEditorView view{model};
    NcursesKeypressReader keypressReader;
    KeypressInteractionReader interactionReader{keypressReader};


    void logStarted(const std::string& programName)
    {
        std::ostringstream oss;
        oss << "Started " << programName;
        
        booEditLog(oss.str());
    }


    void logStopped(const std::string& programName)
    {
        std::ostringstream oss;
        oss << "Stopped " << programName;

        booEditLog(oss.str());
    }


    void startBooEdit()
    {
        booEdit = new BooEdit{model, view, interactionReader};
        booEdit->run();
    }


    void stopBooEdit()
    {
        if (booEdit != nullptr)
        {
            delete booEdit;
            booEdit = nullptr;
        }
    }


    int signals[6] { SIGTERM, SIGSEGV, SIGILL, SIGINT, SIGABRT, SIGFPE };


    void unregisterSignalHandlers()
    {
        for (int signal : signals)
        {
            std::signal(signal, SIG_DFL);
        }
    }


    void signalHandler(int signum)
    {
        unregisterSignalHandlers();
        stopBooEdit();
    }


    void registerSignalHandlers()
    {
        for (int signal : signals)
        {
            std::signal(signal, signalHandler);
        }
    }
}



int main(int argc, char** argv)
{
    std::string programName{argv[0]};

    try
    {
        logStarted(programName);

        registerSignalHandlers();
        startBooEdit();

        unregisterSignalHandlers();
        stopBooEdit();

        logStopped(programName);
    }
    catch (...)
    {
        unregisterSignalHandlers();
        stopBooEdit();

        logStopped(programName);

        throw;
    }

    return 0;
}

