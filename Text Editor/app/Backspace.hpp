#ifndef BACKSPACE_HPP
#define BACKSPACE_HPP

#include "Command.hpp"


class Backspace: public Command
{
public:
	void execute(EditorModel& model) override;

	void undo(EditorModel& model) override;

private:
	int curr_x;
	int curr_y;
	std::string curr_data;
	std::string prev_data;
};



#endif