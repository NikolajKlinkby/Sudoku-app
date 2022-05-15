cmake_minimum_required(VERSION 3.16)

project(Cpp_GUI_fun)

set(CMAKE_CXX_STANDARD 17)

# Dear ImGui
set(IMGUI_DIR ${PROJECT_SOURCE_DIR}/imgui)
set(IMGUI_BACK_DIR ${IMGUI_DIR}/backends)

set(sources ${PROJECT_SOURCE_DIR}/src/main.cpp ${IMGUI_DIR}/imgui.cpp ${IMGUI_DIR}/imgui_demo.cpp ${IMGUI_DIR}/imgui_draw.cpp ${IMGUI_DIR}/imgui_tables.cpp ${IMGUI_DIR}/imgui_widgets.cpp src/SudokuLogic.cpp)
set(backends ${IMGUI_BACK_DIR}/imgui_impl_sdl.cpp ${IMGUI_BACK_DIR}/imgui_impl_opengl3.cpp)

add_executable(SudokuApp ${sources} ${backends})

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})

#OpenGL
find_package(OpenGL REQUIRED)
target_include_directories(SudokuApp PUBLIC ${OPENGL_INCLUDE_DIR})

#SDL2
find_package(SDL2 REQUIRED)
target_include_directories(SudokuApp PUBLIC ${SDL2_INCLUDE_DIRS})

target_include_directories(SudokuApp PRIVATE ${IMGUI_DIR} ${IMGUI_BACK_DIR} )

target_link_libraries(SudokuApp PUBLIC ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES} ${CMAKE_DL_LIBS})

add_custom_command(TARGET SudokuApp POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:SudokuApp> ${PROJECT_BINARY_DIR})