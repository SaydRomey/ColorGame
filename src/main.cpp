
#include "ColorGame.hpp"
#include <iostream>

int	main(void)
{
	ColorGame	cg("Color Game");

	cg.printMsg();
	cg.changeMsg("(W.I.P.)");

	std::cout << cg.getMsg() << std::endl;

	return (0);
}
