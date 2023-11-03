set(OpenCV_DIR /home/csl/Software/opencv-4.x/build)
find_package(OpenCV REQUIRED)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src SRC_FILES)

add_library(${CMAKE_PROJECT_NAME}_lib STATIC ${SRC_FILES})

target_include_directories(
        ${CMAKE_PROJECT_NAME}_lib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${OpenCV_INCLUDE_DIRS}
)

target_link_libraries(
        ${CMAKE_PROJECT_NAME}_lib PUBLIC
        ${OpenCV_LIBS}
)

add_executable(${CMAKE_PROJECT_NAME}_prog ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)

target_link_libraries(
        ${CMAKE_PROJECT_NAME}_prog PRIVATE
        ${CMAKE_PROJECT_NAME}_lib
)