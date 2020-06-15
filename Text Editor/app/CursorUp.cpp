#include "CursorUp.hpp"
#include "EditorException.hpp"


void CursorUp::execute(EditorModel& model)
{
	curr_x = model.cursorColumn();
	curr_y = model.cursorLine();
	

	if (curr_y != 1)
	{
		std::string prev_line = model.line(curr_y - 1); // Need to peek at the previous line

		if (curr_x > prev_line.length()) // Check to see if moving the cursor up will put it at the end of the prev line
		{
			model.setCursorColumn(prev_line.length() + 1);
		}
		
		model.setCursorLine(curr_y - 1);
	}
	else
	{
		throw EditorException{"Already at top"};
	}
}


void CursorUp::undo(EditorModel& model)
{
	model.setCursorColumn(curr_x);
	model.setCursorLine(curr_y);
}