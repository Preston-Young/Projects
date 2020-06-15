#ifndef NEWLINE_HPP
#define NEWLINE_HPP

#include "Command.hpp"
#include <string>


class newLine: public Command
{
public:
	void execute(EditorModel& model) override;
	void undo(EditorModel& model) override;

private:
	int curr_x;
	int curr_y;
	std::string curr_data;
};



#endif