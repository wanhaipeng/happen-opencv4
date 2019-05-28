message(STATUS "using FindOpenCV.cmake find OpenCV4")
set(OpenCV_PATH "/Users/wanhaipeng/Work/FrameWork/OpenCV/opencv-4.1.0/build/opencv4.1")
set(PACKAGE_FIND_VERSION_MAJOR 4)
set(OpenCV_INCLUDE_DIRS ${OpenCV_PATH}/include/opencv4)

set(OpenCV_COMPONENTS opencv_calib3d
                      opencv_core
                      opencv_dnn
                      opencv_features2d
                      opencv_flann
                      opencv_gapi
                      opencv_highgui
                      opencv_imgcodecs
                      opencv_imgproc
                      opencv_ml
                      opencv_objdetect
                      opencv_photo
                      opencv_stitching
                      opencv_video
                      opencv_videoio)
foreach(ITEM ${OpenCV_COMPONENTS})
    list(APPEND OpenCV_LIBRARIES ${OpenCV_PATH}/lib/lib${ITEM}.dylib)
endforeach()
if(OpenCV_INCLUDE_DIRS AND OpenCV_LIBRARIES)
    set(OpenCV_FOUND TRUE)
    message(STATUS "OpenCV4 found")
else()
    message(FATAL_ERROR "OpenCV4 not found!")
endif()