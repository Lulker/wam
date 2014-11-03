g++ --std=c++1y -Ofast -Iinc/ src/*.cpp server.cpp -o server.exe -lws2_32
g++ --std=c++1y -Ofast -Iinc/ src/*.cpp client.cpp -o client.exe -lws2_32
pause
