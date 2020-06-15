#ifndef CURSORHOME_HPP
#define CURSORHOME_HPP

#include "Command.hpp"

static constexpr int HOME = 1;


class CursorHome: public Command
{
public:
	void execute(EditorModel& model) override;

	void undo(EditorModel& model) override;

private:
	int curr_x;
};



#endif