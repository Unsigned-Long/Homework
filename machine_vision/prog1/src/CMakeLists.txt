
find_package(OpenCV REQUIRED)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src SRC_FILES)

add_library(extractor_lib STATIC ${SRC_FILES})

target_include_directories(
        extractor_lib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${OpenCV_INCLUDE_DIRS}
)

target_link_libraries(
        extractor_lib PUBLIC
        ${OpenCV_LIBS}
)

add_executable(${CMAKE_PROJECT_NAME}_prog ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)

target_link_libraries(
        ${CMAKE_PROJECT_NAME}_prog PRIVATE
        extractor_lib
)