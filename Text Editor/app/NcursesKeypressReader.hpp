// This is a derived class of KeypressReader, which reads keypresses from
// the keyboard using a library called "ncurses".

#ifndef NCURSESKEYPRESSREADER_HPP
#define NCURSESKEYPRESSREADER_HPP

#include "KeypressReader.hpp"



class NcursesKeypressReader : public KeypressReader
{
public:
    Keypress nextKeypress() override;
};



#endif // NCURSESKEYPRESSREADER_HPP

