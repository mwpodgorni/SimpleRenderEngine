# Game Only

file(GLOB_RECURSE Exercise6-src "*.h" "*.cpp")


add_executable(Exercise6 ${Exercise6-src})

target_include_directories(Exercise6 PUBLIC ${MYENGINE_INCLUDE_DIR})

target_link_libraries(Exercise6 MyEngineExercise6 ${all_libs})

# Copy project data to output path
file(COPY data DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug)
file(COPY data DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Release)
file(COPY data DESTINATION ${CMAKE_CURRENT_BINARY_DIR})


IF (WIN32)
	## Copy dll's to output path
	file(COPY ${DLLFileList} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug)
	file(COPY ${DLLFileList} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Release)
ENDIF(WIN32)
