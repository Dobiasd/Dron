#include "Dron/DronGame.h"

int main()
{
	if (!Dron::DronGame::Instance().Run())
		return 1;
}
