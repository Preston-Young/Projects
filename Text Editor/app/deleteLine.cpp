#include "deleteLine.hpp"
#include "EditorException.hpp"


void deleteLine::execute(EditorModel& model)
{
	curr_x = model.cursorColumn();
	curr_y = model.cursorLine();
	curr_data = model.line(curr_y);
	curr_line_count = model.lineCount();

	if (model.lineCount() == 1) // If the text editor only has one line of text, delete its contents
	{
		if (curr_x == 1 and curr_data == "")
		{
			throw EditorException{"Already empty"};
		}

		else
		{
			model.setLine("", 1);
			model.setCursorColumn(1);
			model.setCursorLine(1);
		}

	}

	else if (curr_y == model.lineCount()) // If cursor is at the last line of text, move the cursor up for deletion
	{
		std::string prev_line = model.line(curr_y - 1); // Need to peek at previous line

		if (curr_x > prev_line.length())
		{
			model.setCursorColumn(prev_line.length() + 1);
		}

		model.setCursorLine(curr_y - 1);
		model.delLine(curr_y);
	}

	else // If there's lines below the cursor, cursor should stay on same line after deletion
	{
		std::string next_line = model.line(curr_y + 1); // Need to peek at next line

		if (curr_x > next_line.length())
		{
			model.setCursorColumn(next_line.length() + 1);
		}

		model.delLine(curr_y);
	}

}


void deleteLine::undo(EditorModel& model)
{
	if (curr_line_count == 1)
	{
		model.setLine(curr_data, curr_y);
	}

	else
	{
		model.insertLine(curr_data, curr_y);
	}
	
	model.setCursorColumn(curr_x);
	model.setCursorLine(curr_y);
}