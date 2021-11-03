#include "../pch.h"
#include "tests/UnitTests.h"

String getVersion()
{
    return String (ProjectInfo::projectName) + " - " + ProjectInfo::versionString;
}

String getHelp()
{
    return "SimplePlugin Headless Interface:";
}

int main (int argc, char* argv[])
{
    std::cout << "Running SimplePlugin in headless mode..." << std::endl;

#if JUCE_MAC
    Process::setDockIconVisible (false); // hide dock icon
#endif
    ScopedJuceInitialiser_GUI scopedJuce; // creates MessageManager

    ConsoleApplication app;
    app.addVersionCommand ("--version", getVersion());
    app.addHelpCommand ("--help|-h", getHelp(), true);

    UnitTests unitTests;
    app.addCommand (unitTests);

    return app.findAndRunCommand (argc, argv);
}
