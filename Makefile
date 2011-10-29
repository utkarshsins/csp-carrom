inc=includes
src=src

flags=-std=c++0x -lGLU -lglut -lGL
libs=-I$(inc) -IThirdPartyLibs
a.out: Main.o AI.o Carrom.o Coin.o Mouse.o Physics.o BMPLoader.o MenuButton.o MenuMouse.o MenuRender.o NetworkStatus.o DebugMenu.o ThemeMenu.o Client.o
	g++ -o a.out Main.o AI.o Carrom.o Coin.o Mouse.o Physics.o BMPLoader.o MenuButton.o MenuMouse.o MenuRender.o NetworkStatus.o DebugMenu.o ThemeMenu.o Client.o $(flags)

Server:	Server.o CoinServer.o PhysicsServer.o Players.o
	g++ -o Server.out CoinServer.o PhysicsServer.o Server.o Players.o $(flags)
	
Main.o: $(src)/Main.cpp $(inc)/Main.h
	g++ $(libs) -c $(src)/Main.cpp	$(flags)

AI.o: $(src)/AI.cpp $(inc)/AI.h
	g++ $(libs) -c $(src)/AI.cpp $(flags)

Carrom.o: $(src)/Carrom.cpp $(inc)/Carrom.h
	g++ $(libs) -c $(src)/Carrom.cpp $(flags)

Coin.o:		$(src)/Coin.cpp $(inc)/Coin.h
	g++ $(libs) -c $(src)/Coin.cpp $(flags)

Mouse.o:	$(src)/Mouse.cpp $(inc)/Mouse.h
	g++ $(libs) -c $(src)/Mouse.cpp		$(flags)

Physics.o:	$(src)/Physics.cpp $(inc)/Physics.h
	g++ $(libs) -c $(src)/Physics.cpp	$(flags)

BMPLoader.o:	ThirdPartyLibs/BMPLoader.cpp	ThirdPartyLibs/BMPLoader.h
	g++ $(libs) -c ThirdPartyLibs/BMPLoader.cpp $(flags)
	
ServerClient.o:	$(src)/ServerClient.cpp
	g++ $(libs) -c $(src)/ServerClient.cpp $(flags)
	
MenuButton.o:	$(src)/Menu/Button.cpp
	g++ $(libs) -o $@ -c $(src)/Menu/Button.cpp $(flags)
	
MenuMouse.o:	$(src)/Menu/MenuMouse.cpp
	g++ $(libs) -o $@ -c $(src)/Menu/MenuMouse.cpp $(flags)
	
MenuRender.o:	$(src)/Menu/Render.cpp
	g++ $(libs) -o $@ -c $(src)/Menu/Render.cpp $(flags)

NetworkStatus.o:	$(src)/Network/Status.cpp
	g++  $(libs) -o $@ -c $(src)/Network/Status.cpp $(flags)

DebugMenu.o:	$(src)/Menu/DebugMenu.cpp
	g++ $(libs) -o $@ -c $(src)/Menu/DebugMenu.cpp $(flags)

ThemeMenu.o:	$(src)/Menu/Theme.cpp
	g++ $(libs) -o $@ -c $(src)/Menu/Theme.cpp $(flags)

Client.o:	$(src)/Client.cpp
	g++ $(libs) -o $@ -c $(src)/Client.cpp $(flags)

Server.o:	$(src)/Server.cpp
	g++ $(libs) -o $@ -c $(src)/Server.cpp $(flags)

Players.o:	$(src)/Players.cpp
	g++ $(libs) -o $@ -c $(src)/Players.cpp $(flags)

PhysicsServer.o:	$(src)/PhysicsServer.cpp
	g++ $(libs) -o $@ -c $(src)/PhysicsServer.cpp $(flags)

CoinServer.o:	$(src)/CoinServer.cpp
	g++ $(libs) -o $@ -c $(src)/CoinServer.cpp $(flags)

clean:
	rm *.o *.out
