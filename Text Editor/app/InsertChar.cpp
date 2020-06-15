#include "InsertChar.hpp"
#include "EditorModel.hpp"
#include "EditorException.hpp"
#include <string>


InsertChar::InsertChar(char key)
	: _key{std::string(1, key)}
{
}


void InsertChar::execute(EditorModel& model)
{
	curr_x = model.cursorColumn();
	curr_y = model.cursorLine();
	curr_data = model.line(curr_y);

	std::string new_data = curr_data;
	new_data.insert(curr_x - 1, _key); // Add the character right before the current position of the cursor
	model.setLine(new_data, curr_y);
	model.setCursorColumn(curr_x + 1); // Move the cursor to the right

}


void InsertChar::undo(EditorModel& model)
{
	model.setLine(curr_data, curr_y);
	model.setCursorColumn(curr_x);
}