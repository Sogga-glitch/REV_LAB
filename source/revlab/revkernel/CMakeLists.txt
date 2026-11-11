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
	KER_crankshaft.hh

	intern/crankshaft.cc
	
)

# -----------------------------------------------------------------------------
# Define Library Dependencies

set(LIB
	# Internal Library Dependencies
	PUBLIC revlab::source::revlib

	# External Library Dependencies
	
)

# -----------------------------------------------------------------------------
# Declare Library

revlab_add_lib(revkernel "${SRC}" "${INC}" "${INC_SYS}" "${LIB}")
add_library(revlab::source::revkernel ALIAS revkernel)

# -----------------------------------------------------------------------------
# Define Include Directories (Test)

set(INC
	# Internal Include Directories
	PUBLIC .
	
	# External Include Directories
	
)

# -----------------------------------------------------------------------------
# Define System Include Directories (Test)

set(INC_SYS
	# External System Include Directories
	
)

# -----------------------------------------------------------------------------
# Define Source Files (Test)

set(TEST
	tests/crankshaft.cc

)

# -----------------------------------------------------------------------------
# Define Library Dependencies (Test)

set(LIB
	# Internal Library Dependencies
	revlab::source::revkernel
	
	# External Library Dependencies
	
)

# -----------------------------------------------------------------------------
# Declare Test

revlab_add_test_executable(revkernel "${TEST}" "${INC}" "${INC_SYS}" "${LIB}")
