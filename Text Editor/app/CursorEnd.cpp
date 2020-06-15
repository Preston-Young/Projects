#include "CursorEnd.hpp"


void CursorEnd::execute(EditorModel& model)
{
	curr_x = model.cursorColumn();
	curr_y = model.cursorLine();
	model.setCursorColumn(model.line(curr_y).length() + 1);
}


void CursorEnd::undo(EditorModel& model)
{
	model.setCursorColumn(curr_x);
}