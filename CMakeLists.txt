 cmake_minimum_required(VERSION 3.12)
 
 project(MyProject)
 
 set(CMAKE_CXX_STANDARD 17) 
 
 set(SOURSE main.cpp shape.cpp Button.cpp Factory.cpp Scene.cpp ButtonManager.cpp toolsMode.cpp)

 set(HEADER shape.h Factory.h Button.h Scene.h creationTags.h ModeManager.h ButtonManager.h toolsMode.h)

 find_package(SFML 2.5 COMPONENTS system window graphics network ) 
 
 add_executable(MyProject ${SOURSE} ${HEADER})
 
 target_link_libraries(MyProject sfml-system sfml-window sfml-graphics sfml-network sfml-audio)

