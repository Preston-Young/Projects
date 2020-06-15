#ifndef DELETELINE_HPP
#define DELETELINE_HPP

#include "Command.hpp"


class deleteLine: public Command
{
public:
	void execute(EditorModel& model) override;

	void undo(EditorModel& model) override;

private:
	int curr_x;
	int curr_y;
	std::string curr_data;
	int curr_line_count;
};



#endif