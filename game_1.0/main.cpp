#include "headers.hpp"

int main()
{
	try
	{
		Game game;
		game.run();
	}
	catch (std::exception& e)
	{
		MessageBox(NULL,e.what(),"ERROR",MB_OK);
	}
	catch (double result)
	{
		std::string report("You lose LOL\n\n\nResult:  ");
		report += std::to_string(result);
		MessageBox(NULL, report.c_str(), "GAME OVER", MB_OK);
	}
	catch (...)
	{
		MessageBox(NULL, "Unexpected problem", "ERROR",	MB_OK);
	}
}