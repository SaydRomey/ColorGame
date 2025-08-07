
#include "ColorGame.hpp"

ColorGame::ColorGame(void) : _msg("Default Message") {}

ColorGame::ColorGame(std::string msg) : _msg(msg) {}

ColorGame::~ColorGame(void) {}

ColorGame::ColorGame(const ColorGame &other) : _msg(other._msg)
{
	*this = other;
}

ColorGame&	ColorGame::operator=(const ColorGame &other)
{
	if (this != &other)
	{
		_msg = other._msg;
	}
	return (*this);
}

std::string	ColorGame::getMsg(void) const { return (_msg); }

void	ColorGame::printMsg(void) const
{
	std::cout << _msg << std::endl;
}

void	ColorGame::changeMsg(std::string newMsg="")
{
	_msg = newMsg;
}
