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

)

# -----------------------------------------------------------------------------
# Define Source Files

set(SRC
	test_main.cc
)

# -----------------------------------------------------------------------------
# Define Library Dependencies

set(LIB
	# Internal Library Dependencies
	
	# External Library Dependencies
	PUBLIC revlab::extern::gtest
	
)

# -----------------------------------------------------------------------------
# Declare Library

revlab_add_lib(testing "${SRC}" "${INC}" "${INC_SYS}" "${LIB}")
add_library(revlab::intern::testing ALIAS testing)
