
#ifndef COLORGAME_HPP
# define COLORGAME_HPP

# include <iostream>

class ColorGame
{
	public:
		ColorGame(void);
		ColorGame(std::string msg);
		ColorGame(const ColorGame &other);
		ColorGame&	operator=(const ColorGame &other);
		~ColorGame(void);

		std::string	getMsg(void) const;
		void		printMsg(void) const;
		void		changeMsg(std::string newMsg);
	
	private:
		std::string	_msg;

};

#endif // COLORGAME_HPP
