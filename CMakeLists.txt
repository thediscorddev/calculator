set(CMAKE_C_COMPILER x86_64-w64-mingw32-gcc)
set(CMAKE_CXX_COMPILER x86_64-w64-mingw32-g++)
set(WXWIDGETS_ROOT_DIR "path_to_your_mingw_wxwidgets")

find_package(wxWidgets REQUIRED)

add_executable(myapp main.cpp src/*.cpp)
target_link_libraries(myapp ${wxWidgets_LIBRARIES})
