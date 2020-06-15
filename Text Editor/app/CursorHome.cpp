#include "CursorHome.hpp"


void CursorHome::execute(EditorModel& model)
{
	curr_x = model.cursorColumn();
	model.setCursorColumn(HOME);
}


void CursorHome::undo(EditorModel& model)
{
	model.setCursorColumn(curr_x);
}