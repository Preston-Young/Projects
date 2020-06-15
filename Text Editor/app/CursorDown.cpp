#include "CursorDown.hpp"
#include "EditorException.hpp"


void CursorDown::execute(EditorModel& model)
{
	curr_x = model.cursorColumn();
	curr_y = model.cursorLine();

	if (curr_y != model.lineCount())
	{
		std::string next_line = model.line(curr_y + 1); // Need to peek at the next line

		if (curr_x > next_line.length()) // Check to see if moving the cursor down will put it at the end of next line
		{
			model.setCursorColumn(next_line.length() + 1);
		}

		model.setCursorLine(curr_y + 1);
	}
	else
	{
		throw EditorException{"Already at bottom"};
	}
}


void CursorDown::undo(EditorModel& model)
{
	model.setCursorColumn(curr_x);
	model.setCursorLine(curr_y);
}