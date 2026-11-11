# -----------------------------------------------------------------------------
# Define Include Directories

set(INC
	# Internal Include Directories
	PUBLIC .
	
	# External Include Directories
	
)

# -----------------------------------------------------------------------------
# Define System Include Directories

set(INC_SYS
	# External System Include Directories
	${GLFW_INCLUDE_DIRS}
	${VULKAN_INCLUDE_DIRS}
	
)

# -----------------------------------------------------------------------------
# Define Source Files

set(SRC
	main.cpp
	
)

# -----------------------------------------------------------------------------
# Define Library Dependencies

set(LIB
	# Internal Library Dependencies

	# External Library Dependencies
	${GLFW_LIBRARIES}
	${VULKAN_LIBRARIES}
	
)

# -----------------------------------------------------------------------------
# Declare Executable

add_executable(revlab "${SRC}")

revlab_target_link_libraries(revlab "${LIB}")
revlab_target_include_dirs(revlab "${INC}")
revlab_target_include_dirs(revlab SYSTEM "${INC_SYS}")
