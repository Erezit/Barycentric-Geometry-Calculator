 cmake_minimum_required(VERSION 3.12)
 
 project(MyProject)
 
 set(CMAKE_CXX_STANDARD 17) 
 
 include_directories(${CMAKE_SOURCE_DIR}/include)

 set(SOURSE ${CMAKE_SOURCE_DIR}/sourse/main.cpp 
            ${CMAKE_SOURCE_DIR}/sourse/shape.cpp
            ${CMAKE_SOURCE_DIR}/sourse/Button.cpp
            ${CMAKE_SOURCE_DIR}/sourse/Factory.cpp 
            ${CMAKE_SOURCE_DIR}/sourse/Scene.cpp 
            ${CMAKE_SOURCE_DIR}/sourse/ButtonManager.cpp 
            ${CMAKE_SOURCE_DIR}/sourse/toolsMode.cpp)

 set(HEADER ${CMAKE_SOURCE_DIR}/include/shape.h
            ${CMAKE_SOURCE_DIR}/include/Factory.h
            ${CMAKE_SOURCE_DIR}/include/Button.h
            ${CMAKE_SOURCE_DIR}/include/Scene.h
            ${CMAKE_SOURCE_DIR}/include/creationTags.h 
            ${CMAKE_SOURCE_DIR}/include/ModeManager.h
            ${CMAKE_SOURCE_DIR}/include/ButtonManager.h
            ${CMAKE_SOURCE_DIR}/include/toolsMode.h)
 
 find_package(SFML 2.5 COMPONENTS system window graphics network ) 
 #find_library(PARI_LIBRARY pari)

 add_executable(MyProject ${SOURSE} ${HEADER} "${CMAKE_SOURCE_DIR}")
 
 target_link_libraries(MyProject sfml-system sfml-window sfml-graphics sfml-network sfml-audio)
 #target_link_libraries(MyProject ${PARI_LIBRARY})
