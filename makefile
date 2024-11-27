default:
	g++ main.cpp src/*.cpp -O3 -ID:\wxWidgets-3.2.6-headers\include
linux:
	g++ main.cpp src/*.cpp -o myapp -g `wx-config --cxxflags --libs`