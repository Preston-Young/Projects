// The EditorModel class implements the "model" of the text editor.  In other words, its
// job is to maintain the underlying data -- the current lines of text, where
// the cursor is supposed to be, etc. -- and provide operations that allow the
// EditorView to access that data, along with basic operations that allow the
// various Command objects to make the necessary changes when they're executed
// or undone.
//
// The member functions already declared in the EditorModel class are absolutely
// necessary for EditorView to work, so they cannot be removed or have their
// declarations changed (though you may need to implement them; see
// EditorModel.cpp).
//
// Note: Remember that "line number" and "column number" here is one-based,
// not zero-based, which means that the top left corner of the file is line 1
// column 1.

#ifndef EDITORMODEL_HPP
#define EDITORMODEL_HPP

#include <string>
#include <vector>



class EditorModel
{
public:
    // Initializes the editor model.  Initially, the cursor is on
    // line 1 column 1 and there should be one empty line of text
    // in the editor.
    EditorModel();

    // Returns the line number where the cursor currently should reside.
    int cursorLine() const;

    // Returns the column number where the cursor currently should reside.
    int cursorColumn() const;

    // Returns the number of lines of text currently in the editor.
    int lineCount() const;

    // Returns the text on the given line number.
    const std::string& line(int ln) const;

    // Returns the error message that should be displayed currently.
    const std::string& currentErrorMessage() const;

    // Sets the error message that should be displayed currently.
    void setErrorMessage(const std::string& errorMessage);

    // Clears the error message that should be displayed currently.
    void clearErrorMessage();

    // Adds a character to the current line and column.
    void add_char(const std::string& character);

    // Sets the entire line to something else.
    void setLine(std::string data, int ln);

    // Insert an entire line at a given index.
    void insertLine(std::string data, int ln);

    // Delete an entire line at a given index.
    void delLine(int ln);

    // Sets the current line of the cursor to something else.
    void setCursorLine(int index);

    // Sets the current column of the cursor to something else.
    void setCursorColumn(int index);

private:
    int curr_line;
    int curr_coln;
    int line_totals;
    std::vector<std::string> lines;
    std::string curr_error_message;

};



#endif // EDITORMODEL_HPP

