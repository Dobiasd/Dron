LD_FLAGS := -lsfml-audio -lsfml-graphics -lsfml-system -lsfml-window
CC_FLAGS := -Wall -Wextra -pedantic -std=c++11 -Werror

Dron:
	rm -f -R ./obj
	mkdir -p ./obj/MenuItems
	mkdir -p ./obj/Dron
	mkdir -p ./obj/Dron/PlayerControllers
	mkdir -p ./obj/Dron/Items
	mkdir -p ./obj/Dron/GameStates
	mkdir -p ./obj/Dron/GameStates/PlayLogicControllers
	mkdir -p ./obj/Dron/Animations
	g++ $(CC_FLAGS) -c ./src/main.cpp -o ./obj/main.o
	g++ $(CC_FLAGS) -c ./src/Synthesizer.cpp -o ./obj/Synthesizer.o
	g++ $(CC_FLAGS) -c ./src/Menu.cpp -o ./obj/Menu.o
	g++ $(CC_FLAGS) -c ./src/BlurPostEffect.cpp -o ./obj/BlurPostEffect.o
	g++ $(CC_FLAGS) -c ./src/Game.cpp -o ./obj/Game.o
	g++ $(CC_FLAGS) -c ./src/Plasma.cpp -o ./obj/Plasma.o
	g++ $(CC_FLAGS) -c ./src/Dron/Item.cpp -o ./obj/Dron/Item.o
	g++ $(CC_FLAGS) -c ./src/Dron/World.cpp -o ./obj/Dron/World.o
	g++ $(CC_FLAGS) -c ./src/Dron/PlayerController.cpp -o ./obj/Dron/PlayerController.o
	g++ $(CC_FLAGS) -c ./src/Dron/PlayerControllers/AIController.cpp -o ./obj/Dron/PlayerControllers/AIController.o
	g++ $(CC_FLAGS) -c ./src/Dron/PlayerControllers/JoyController.cpp -o ./obj/Dron/PlayerControllers/JoyController.o
	g++ $(CC_FLAGS) -c ./src/Dron/PlayerControllers/KeyController.cpp -o ./obj/Dron/PlayerControllers/KeyController.o
	g++ $(CC_FLAGS) -c ./src/Dron/Items/RandomItemFactory.cpp -o ./obj/Dron/Items/RandomItemFactory.o
	g++ $(CC_FLAGS) -c ./src/Dron/Items/Abridger.cpp -o ./obj/Dron/Items/Abridger.o
	g++ $(CC_FLAGS) -c ./src/Dron/Items/BatteringRam.cpp -o ./obj/Dron/Items/BatteringRam.o
	g++ $(CC_FLAGS) -c ./src/Dron/Items/Fragmenter.cpp -o ./obj/Dron/Items/Fragmenter.o
	g++ $(CC_FLAGS) -c ./src/Dron/Player.cpp -o ./obj/Dron/Player.o
	g++ $(CC_FLAGS) -c ./src/Dron/GameStates/SplashScreen.cpp -o ./obj/Dron/GameStates/SplashScreen.o
	g++ $(CC_FLAGS) -c ./src/Dron/GameStates/ShowTextAndWait.cpp -o ./obj/Dron/GameStates/ShowTextAndWait.o
	g++ $(CC_FLAGS) -c ./src/Dron/GameStates/PlayView.cpp -o ./obj/Dron/GameStates/PlayView.o
	g++ $(CC_FLAGS) -c ./src/Dron/GameStates/MainMenu.cpp -o ./obj/Dron/GameStates/MainMenu.o
	g++ $(CC_FLAGS) -c ./src/Dron/GameStates/Quit.cpp -o ./obj/Dron/GameStates/Quit.o
	g++ $(CC_FLAGS) -c ./src/Dron/GameStates/PlayLogicControllers/ItemDacayer.cpp -o ./obj/Dron/GameStates/PlayLogicControllers/ItemDacayer.o
	g++ $(CC_FLAGS) -c ./src/Dron/GameStates/PlayLogicControllers/PlayerMover.cpp -o ./obj/Dron/GameStates/PlayLogicControllers/PlayerMover.o
	g++ $(CC_FLAGS) -c ./src/Dron/GameStates/PlayLogicControllers/NewItemPlacer.cpp -o ./obj/Dron/GameStates/PlayLogicControllers/NewItemPlacer.o
	g++ $(CC_FLAGS) -c ./src/Dron/GameStates/PlayLogicControllers/PlayersCollisionChecker.cpp -o ./obj/Dron/GameStates/PlayLogicControllers/PlayersCollisionChecker.o
	g++ $(CC_FLAGS) -c ./src/Dron/GameStates/PlayLogicControllers/GameOverChecker.cpp -o ./obj/Dron/GameStates/PlayLogicControllers/GameOverChecker.o
	g++ $(CC_FLAGS) -c ./src/Dron/GameStates/PlayLogicControllers/ItemCollectionChecker.cpp -o ./obj/Dron/GameStates/PlayLogicControllers/ItemCollectionChecker.o
	g++ $(CC_FLAGS) -c ./src/Dron/GameStates/PlayLogicControllers/PlayersNextPositionsCalculator.cpp -o ./obj/Dron/GameStates/PlayLogicControllers/PlayersNextPositionsCalculator.o
	g++ $(CC_FLAGS) -c ./src/Dron/GameStates/Play.cpp -o ./obj/Dron/GameStates/Play.o
	g++ $(CC_FLAGS) -c ./src/Dron/GameStates/PlayInputController.cpp -o ./obj/Dron/GameStates/PlayInputController.o
	g++ $(CC_FLAGS) -c ./src/Dron/GameStates/PlayModel.cpp -o ./obj/Dron/GameStates/PlayModel.o
	g++ $(CC_FLAGS) -c ./src/Dron/DronGame.cpp -o ./obj/Dron/DronGame.o
	g++ $(CC_FLAGS) -c ./src/Dron/Animations/BatteringRamAnimation.cpp -o ./obj/Dron/Animations/BatteringRamAnimation.o
	g++ $(CC_FLAGS) -c ./src/Dron/Animations/CollectAnimation.cpp -o ./obj/Dron/Animations/CollectAnimation.o
	g++ $(CC_FLAGS) -c ./src/MenuItems/EnterItem.cpp -o ./obj/MenuItems/EnterItem.o

	g++ $(LD_FLAGS) -o Dron ./obj/main.o ./obj/Synthesizer.o ./obj/Menu.o ./obj/BlurPostEffect.o ./obj/Game.o ./obj/Plasma.o ./obj/Dron/Item.o ./obj/Dron/World.o ./obj/Dron/PlayerController.o ./obj/Dron/PlayerControllers/AIController.o ./obj/Dron/PlayerControllers/JoyController.o ./obj/Dron/PlayerControllers/KeyController.o ./obj/Dron/Items/RandomItemFactory.o ./obj/Dron/Items/Abridger.o ./obj/Dron/Items/BatteringRam.o ./obj/Dron/Items/Fragmenter.o ./obj/Dron/Player.o ./obj/Dron/GameStates/SplashScreen.o ./obj/Dron/GameStates/ShowTextAndWait.o ./obj/Dron/GameStates/PlayView.o ./obj/Dron/GameStates/MainMenu.o ./obj/Dron/GameStates/Quit.o ./obj/Dron/GameStates/PlayLogicControllers/ItemDacayer.o ./obj/Dron/GameStates/PlayLogicControllers/PlayerMover.o ./obj/Dron/GameStates/PlayLogicControllers/NewItemPlacer.o ./obj/Dron/GameStates/PlayLogicControllers/PlayersCollisionChecker.o ./obj/Dron/GameStates/PlayLogicControllers/GameOverChecker.o ./obj/Dron/GameStates/PlayLogicControllers/ItemCollectionChecker.o ./obj/Dron/GameStates/PlayLogicControllers/PlayersNextPositionsCalculator.o ./obj/Dron/GameStates/Play.o ./obj/Dron/GameStates/PlayInputController.o ./obj/Dron/GameStates/PlayModel.o ./obj/Dron/DronGame.o ./obj/Dron/Animations/BatteringRamAnimation.o ./obj/Dron/Animations/CollectAnimation.o ./obj/MenuItems/EnterItem.o