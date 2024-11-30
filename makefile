windows:
	g++ main.cpp src/*.cpp -o myapp -g \
	-I"D:/Game_Project_Privated-main/packages" \
	-I"C:/wxWidgets-3.2.6/include" \
	-I"C:/wxWidgets-3.2.6/lib/gcc_lib/mswu" \
	-luxtheme -lgdi32 -loleacc -loleaut32 -lshlwapi -luser32 -lkernel32



linux:
	g++ main.cpp src/*.cpp -o myapp -g `wx-config --cxxflags --libs`