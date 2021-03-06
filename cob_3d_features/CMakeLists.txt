cmake_minimum_required(VERSION 2.8.3)
project(cob_3d_features)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  cob_3d_mapping_common
#  cob_3d_mapping_tools
  cob_3d_visualization
  pcl_ros
)

find_package(OpenCV REQUIRED)
find_package(VTK REQUIRED COMPONENTS vtkCommon vtkFiltering vtkRendering)
find_package(Boost REQUIRED COMPONENTS program_options)
find_package(PCL REQUIRED)

find_package( OpenMP REQUIRED)
if(OPENMP_FOUND)
message("OPENMP FOUND")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if you package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
  INCLUDE_DIRS
    common/include
  LIBRARIES
    cob_3d_features
    cob_3d_features_omp
  CATKIN_DEPENDS
    cob_3d_mapping_common
    pcl_ros
  DEPENDS
    OpenCV
    #VTK
    Boost
    PCL
)



###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
# include_directories(include ${catkin_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS})
include_directories(
  common/include
  ${catkin_INCLUDE_DIRS}
  ${Boost_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}
  ${PCL_INCLUDE_DIRS}
  ${VTK_INCLUDE_DIRS}
)

## Declare a cpp library
add_library(cob_3d_features
  common/src/fast_edge_estimation_3d.cpp
  common/src/edge_estimation_2d.cpp
  common/src/knn_classifier.cpp
  common/src/most_discriminating_data_points.cpp
  common/src/organized_curvature_estimation.cpp
  common/src/organized_normal_estimation.cpp)

add_library(cob_3d_features_omp
  common/src/organized_curvature_estimation_omp.cpp
  common/src/organized_normal_estimation_omp.cpp
  common/src/fast_edge_estimation_3d_omp.cpp)

add_library(s2kit common/src/ShapeSPH/cospmls.cpp common/src/ShapeSPH/FST_semi_memo_fftw.cpp common/src/ShapeSPH/cospmls.cpp common/src/ShapeSPH/fft_grids.cpp common/src/ShapeSPH/FST_semi_memo.cpp common/src/ShapeSPH/FST_semi_memo_fftw.cpp common/src/ShapeSPH/naive_synthesis.cpp common/src/ShapeSPH/newFCT.cpp common/src/ShapeSPH/primitive.cpp common/src/ShapeSPH/primitive_FST.cpp common/src/ShapeSPH/seminaive.cpp common/src/ShapeSPH/seminaive_fftw.cpp common/src/ShapeSPH/FFTcode.cpp common/src/ShapeSPH/csecond.cpp common/src/ShapeSPH/weights.cpp common/src/ShapeSPH/OURperms.cpp common/src/ShapeSPH/oddweights.cpp common/src/ShapeSPH/OURmods.cpp common/src/ShapeSPH/indextables.cpp)

## Declare a cpp executable
add_executable(test_organized_curvature_estimation common/test/test_organized_curvature_estimation.cpp)
add_executable(test_surface_class_estimation common/test/test_surface_class_estimation.cpp)
add_executable(test_edge_sharpening common/test/test_edge_sharpening.cpp)
add_executable(profile_oce common/test/profile_oce.cpp)
add_executable(profile_fee_omp common/test/profile_fee_omp.cpp)
add_executable(profile_fee common/test/profile_fee.cpp)
add_executable(profile_ne common/test/profile_ne.cpp)
add_executable(eval_invariant_feature common/test/evaluate_invariant_feature.cpp)
add_executable(invariant_feature_node ros/src/invariant_feature_node.cpp)

# extracts pc from organized cloud and saves as ppm:
add_executable(extract_organized_curvatures common/test/extract_organized_curvatures.cpp)
target_link_libraries(cob_3d_features
  ${catkin_LIBRARIES}
  ${OpenCV_LIBS}
  ${PCL_LIBRARIES}
)

target_link_libraries(eval_invariant_feature
  s2kit
  fftw3
  fftw3f
  ${catkin_LIBRARIES}
  ${PCL_LIBRARIES}
)

target_link_libraries(invariant_feature_node
  s2kit
  fftw3
  fftw3f
  ${catkin_LIBRARIES}
  ${PCL_LIBRARIES}
)

target_link_libraries(cob_3d_features_omp
  ${catkin_LIBRARIES}
  ${PCL_LIBRARIES}
)

target_link_libraries(test_organized_curvature_estimation
  cob_3d_features
  cob_3d_features_omp
  ${catkin_LIBRARIES}
  ${VTK_LIBRARIES}
  ${OpenCV_LIBS}
  ${Boost_LIBRARIES}
)

target_link_libraries(test_surface_class_estimation
  cob_3d_features
  cob_3d_features_omp
  ${catkin_LIBRARIES}
  ${VTK_LIBRARIES}
  ${OpenCV_LIBS}
  ${Boost_LIBRARIES}
)

target_link_libraries(test_edge_sharpening
  cob_3d_features
  cob_3d_features_omp
  ${catkin_LIBRARIES}
  ${VTK_LIBRARIES}
  ${OpenCV_LIBS}
  ${Boost_LIBRARIES}
)

target_link_libraries(profile_oce
  cob_3d_features
  cob_3d_features_omp
  ${catkin_LIBRARIES}
  ${VTK_LIBRARIES}
  ${OpenCV_LIBS}
)

target_link_libraries(profile_fee_omp
  cob_3d_features
  cob_3d_features_omp
  ${catkin_LIBRARIES}
  ${VTK_LIBRARIES}
  ${OpenCV_LIBS}
)

target_link_libraries(profile_fee
  cob_3d_features
  cob_3d_features_omp
  ${catkin_LIBRARIES}
  ${VTK_LIBRARIES}
  ${OpenCV_LIBS}
)

target_link_libraries(profile_ne
  cob_3d_features
  cob_3d_features_omp
  ${catkin_LIBRARIES}
)

target_link_libraries(extract_organized_curvatures
  cob_3d_features
  ${catkin_LIBRARIES}
  ${Boost_LIBRARIES}
)

#set_target_properties(cob_3d_features_omp PROPERTIES COMPILE_FLAGS "-fopenmp"
#  LINK_FLAGS "-fopenmp"
#)


