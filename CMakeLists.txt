cmake_minimum_required(VERSION 2.8)
project(MultiFocusFusionAndDepth)
set(CMAKE_CXX_STANDARD 17)


find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable(MultiFocusFusionAndDepth src/main.cpp
                                        src/FocusMeasurer/FocusMeasurer.hpp
                                        src/FocusMeasurer/FocusContext.hpp
                                        src/FocusMeasurer/FocusContext.cpp
                                        src/FocusMeasurer/Variance.hpp
                                        src/FocusMeasurer/Variance.cpp
                                        src/FocusMeasurer/SML.cpp
                                        src/FocusMeasurer/SML.hpp
                                        src/ImageWrapping/ImageFunctions.hpp
                                        src/FocusMeasurer/VarianceOfLaplacians.hpp
                                        src/FocusMeasurer/VarianceOfLaplacians.cpp src/ImageWrapping/ImageFunctions.cpp src/DepthMeasurer/DepthMeasurer.hpp src/DepthMeasurer/DepthMeasurer.cpp)
target_link_libraries( MultiFocusFusionAndDepth ${OpenCV_LIBS} )
