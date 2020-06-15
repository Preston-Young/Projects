#include "EditorModel.hpp"
#include "EditorException.hpp"
#include <vector>
#include <string>


EditorModel::EditorModel()
	: curr_line{1}, curr_coln{1}, line_totals{1},
		lines{""}, curr_error_message{""}
{
}


// Returns row-coordinate of cursor
int EditorModel::cursorLine() const
{
    return curr_line;
}


// Returns column-coordinate of cursor
int EditorModel::cursorColumn() const
{
    return curr_coln;
}


// Returns how many lines are allocated in the textbox
int EditorModel::lineCount() const
{
    return line_totals;
}


// Returns the string of text at a given row
const std::string& EditorModel::line(int ln) const
{
    return lines.at(ln-1);
}


// Returns the current error message
const std::string& EditorModel::currentErrorMessage() const
{
    return curr_error_message;
}


// Sets the current error message to the given string
void EditorModel::setErrorMessage(const std::string& errorMessage)
{
	curr_error_message = errorMessage;
}


// Clears the current error message
void EditorModel::clearErrorMessage()
{
	curr_error_message = "";
}


// Adds a character where the cursor is
void EditorModel::add_char(const std::string& character)
{
	lines.at(curr_line - 1).insert(curr_coln - 1, character);
}


// Sets an entire line at a given row with a given string
void EditorModel::setLine(std::string data, int ln)
{
	ln--;
	lines.at(ln) = data;
}


// Inserts an entire line after a given row with an entire string
void EditorModel::insertLine(std::string data, int ln)
{
	ln--;

	if (ln > line_totals)
	{
		lines.push_back(""); // Initialize an empty line if the cursor was at the end of the line
	}

	lines.insert(lines.begin() + ln, data);
	
	line_totals++;
}


// Deletes an entire line at a given row
void EditorModel::delLine(int ln)
{
	ln--;
	
	if (line_totals != 0)
	{
		line_totals--;
	}

	lines.erase(lines.begin() + ln);
}


// Sets the cursor row-coordinate to the given integer
void EditorModel::setCursorLine(int index)
{
	curr_line = index;
}


// Sets the cursor column-coordinate to the given integer
void EditorModel::setCursorColumn(int index)
{
	curr_coln = index;
}

