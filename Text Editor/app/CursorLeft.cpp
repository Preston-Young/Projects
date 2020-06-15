#include "CursorLeft.hpp"
#include "EditorModel.hpp"
#include "EditorException.hpp"



void CursorLeft::execute(EditorModel & model)
{
	curr_x = model.cursorColumn();
	curr_y = model.cursorLine();

	if (curr_x == 1 && curr_y == 1)
	{
		throw(EditorException{"Already at beginning."});
	}

	else
	{
		if (curr_x == 1)
		{
			model.setCursorLine(curr_y - 1);
			model.setCursorColumn(model.line(curr_y-1).length() + 1);
		}

		else
		{
			model.setCursorColumn(curr_x - 1);
		}

	}

}


void CursorLeft::undo(EditorModel & model)
{
	model.setCursorColumn(curr_x);
	model.setCursorLine(curr_y);
}