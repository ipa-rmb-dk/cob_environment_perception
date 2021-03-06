cmake_minimum_required(VERSION 2.8.3)
project(cob_3d_evaluation_features)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  cob_3d_features
  cob_3d_mapping_common
  cob_3d_mapping_tools
  sensor_msgs
)

find_package(Boost REQUIRED COMPONENTS filesystem program_options signals system)
find_package(OpenCV REQUIRED)
find_package(PCL REQUIRED)
find_package(VTK REQUIRED COMPONENTS vtkCommon vtkFiltering vtkRendering)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
# include_directories(include ${catkin_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS})
include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ${VTK_INCLUDE_DIRS}
  ${Boost_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}
  ${PCL_INCLUDE_DIRS}
)

# extracts fpfh, pc and rsd feature values from a scene into separated pcd files:
add_executable(extract_feature_values src/extract_feature_values.cpp)
# some tools for fpfh training:
add_executable(merge_knn_training_data src/merge_knn_training_data.cpp)
add_executable(merge_fpfh_training_data src/merge_fpfh_training_data.cpp)
add_executable(reduce_fpfh_training_data src/reduce_fpfh_training_data.cpp)
add_executable(fpfh_primitives src/fpfh_primitives.cpp)
# some tools to generate fpfh, pc and rsd test data and evaluate various parameters
add_executable(evaluate_test_data src/evaluate_test_data.cpp)
add_executable(generate_test_data src/generate_test_data.cpp)
#add_executable(evaluation_features src/evaluation_features.cpp) #deactivated because rsd was removed from PCL
add_executable(evaluation_features_fpfh src/evaluation_features_fpfh.cpp)
add_executable(evaluation_fpfh_svm_trainer src/evaluation_fpfh_svm_trainer.cpp)


target_link_libraries(extract_feature_values
  ${catkin_LIBRARIES}
  ${Boost_LIBRARIES}
)

target_link_libraries(merge_knn_training_data
  ${catkin_LIBRARIES}
  ${Boost_LIBRARIES}
)

target_link_libraries(merge_fpfh_training_data
  ${catkin_LIBRARIES}
  ${Boost_LIBRARIES}
)

target_link_libraries(reduce_fpfh_training_data
  ${catkin_LIBRARIES}
  ${Boost_LIBRARIES}
)

target_link_libraries(fpfh_primitives
  cob_3d_mapping_tools
  ${catkin_LIBRARIES}
  ${Boost_LIBRARIES}
  ${VTK_LIBRARIES}
)

target_link_libraries(evaluate_test_data
  ${catkin_LIBRARIES}
  ${Boost_LIBRARIES}
)

target_link_libraries(generate_test_data
  ${catkin_LIBRARIES}
  ${Boost_LIBRARIES}
)

#target_link_libraries(evaluation_features
#  ${catkin_LIBRARIES}
#  ${Boost_LIBRARIES}
#  ${OpenCV_LIBRARIES}
#  ${VTK_LIBRARIES}
#)

target_link_libraries(evaluation_features_fpfh
  ${catkin_LIBRARIES}
)

target_link_libraries(evaluation_fpfh_svm_trainer
  ${catkin_LIBRARIES}
)

set_target_properties(evaluate_test_data PROPERTIES COMPILE_FLAGS -DEIGEN_YES_I_KNOW_SPARSE_MODULE_IS_NOT_STABLE_YET)
set_target_properties(generate_test_data PROPERTIES COMPILE_FLAGS -DEIGEN_YES_I_KNOW_SPARSE_MODULE_IS_NOT_STABLE_YET)
#set_target_properties(evaluation_features PROPERTIES COMPILE_FLAGS -DEIGEN_YES_I_KNOW_SPARSE_MODULE_IS_NOT_STABLE_YET)
