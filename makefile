all: main

main: main.cpp
	g++ -Wall -Wconversion -o main.exe main.cpp DataCenter\dataGenerator.cpp DataCenter\mesh.cpp DataCenter\parser.cpp DataCenter\pointCloud.cpp Display\display.cpp Display\screen.cpp Scheduler\scheduler.cpp Scheduler\threadBuffer.cpp Scheduler\worker.cpp -ld2d1 -lgdi32 -luser32 -lm