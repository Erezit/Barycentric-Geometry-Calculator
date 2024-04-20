 cmake_minimum_required(VERSION 3.12)
 
 project(MyProject)
  
 set(CMAKE_CXX_STANDARD 17)
 set(CMAKE_CXX_COMPILER clang++)

 find_package(Python COMPONENTS Interpreter REQUIRED)
 find_package(GTest)


 include_directories(${CMAKE_SOURCE_DIR}/include)

 add_subdirectory(${CMAKE_SOURCE_DIR}/source)

 
 set(SOURCE ${CMAKE_SOURCE_DIR}/source/main.cpp
            ${CMAKE_SOURCE_DIR}/source/shape.cpp
            ${CMAKE_SOURCE_DIR}/source/Button.cpp
            ${CMAKE_SOURCE_DIR}/source/Scene.cpp
            ${CMAKE_SOURCE_DIR}/source/ButtonManager.cpp
            ${CMAKE_SOURCE_DIR}/source/toolsMode.cpp
            ${CMAKE_SOURCE_DIR}/source/NameBox.cpp
            ${CMAKE_SOURCE_DIR}/source/BarycentricCoordinate.cpp)
 
 include_directories(${CMAKE_SOURCE_DIR})

 set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
 add_compile_options(-O2)
  

 add_custom_target(Copy
     COMMAND Python::Interpreter ${CMAKE_SOURCE_DIR}/copy.py ${CMAKE_SOURCE_DIR}/Textures ${CMAKE_BINARY_DIR}
     COMMENT "The folder with textures has been successfully copied "             
                  )
 

 find_package(SFML 2.5 COMPONENTS system window graphics network) 
 find_library(GINAC_LIBRARIES ginac)
  
 if(NOT GINAC_LIBRARIES)
     message(FATAL_ERROR "GiNac library not found")
 else()
     message(STATUS "GiNac library found")
 endif()


 add_executable(Test ${CMAKE_SOURCE_DIR}/tests/mainTest.cpp ${CMAKE_SOURCE_DIR}/tests/WonderfulTrianglePoints.cpp)
 add_executable(MyProject ${SOURCE})
 
 target_link_libraries(MyProject sfml-system sfml-window sfml-graphics sfml-network sfml-audio)
 target_link_libraries(MyProject ${GINAC_LIBRARIES})
 
 target_link_libraries(Test ${GTEST_LIBRARIES} ${GINAC_LIBRARIES} sfml-system sfml-window sfml-graphics sfml-network sfml-audio lib)
 

 add_dependencies(Test Copy)
 add_dependencies(MyProject Copy)

