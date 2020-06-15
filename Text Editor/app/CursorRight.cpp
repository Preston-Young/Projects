#include "CursorRight.hpp"
#include "EditorModel.hpp"
#include "EditorException.hpp"



void CursorRight::execute(EditorModel & model)
{
	curr_x = model.cursorColumn();
	curr_y = model.cursorLine();
	int end = model.line(curr_y).length() + 1;

	if (curr_x == end && curr_y == model.lineCount())
	{
		throw(EditorException{"Already at end"});
	}

	else
	{
		if (curr_x == end)
		{
			model.setCursorLine(curr_y + 1);
			model.setCursorColumn(1);
		}

		else
		{
			model.setCursorColumn(curr_x + 1);
		}

	}

}


void CursorRight::undo(EditorModel & model)
{
	model.setCursorColumn(curr_x);
	model.setCursorLine(curr_y);
}