// A derived class of EditorView, which visualizes the current state of
// the text editor using a library called "ncurses".

#ifndef NCURSESEDITORVIEW_HPP
#define NCURSESEDITORVIEW_HPP

#include "EditorModel.hpp"
#include "EditorView.hpp"



class NcursesEditorView : public EditorView
{
public:
    explicit NcursesEditorView(EditorModel& model);

    void start() override;
    void stop() override;
    void refresh() override;

private:
    EditorModel& model;

    int topVisibleLine;
    int leftVisibleColumn;
};



#endif // NCURSESEDITORVIEW_HPP

