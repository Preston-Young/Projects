#ifndef CURSORRIGHT_HPP
#define CURSORRIGHT_HPP

#include "Command.hpp"



class CursorRight : public Command
{
public:
	void execute(EditorModel & model) override;
	void undo(EditorModel & model) override;

private:
	int curr_x;
	int curr_y;

};



#endif