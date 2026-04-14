all: main

main: main.cpp
	g++ -Wall -Wconversion -o main.exe main.cpp DataCenter\Objects\mesh.cpp DataCenter\Objects\point.cpp DataCenter\Objects\pointCloud.cpp DataCenter\Objects\triangle.cpp DataCenter\Objects\voxel.cpp DataCenter\dataCenter.cpp DataCenter\dataGenerator.cpp DataCenter\meshGenerator.cpp DataCenter\parser.cpp Display\display.cpp Display\screen.cpp Scheduler\scheduler.cpp Scheduler\threadBuffer.cpp Scheduler\worker.cpp Utilities\mathUtilities.cpp -ld2d1 -lgdi32 -luser32 -lm