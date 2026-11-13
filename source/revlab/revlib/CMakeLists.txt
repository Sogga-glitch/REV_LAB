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
	LIB_math_matrix_types.hh
	LIB_math_matrix.hh
	LIB_math_vector_types.hh
	LIB_math_vector.hh
	LIB_math.hh
	LIB_units.hh
	LIB_utildefines.hh
	LIB_utility_mixins.hh

	intern/math_matrix.cc
	intern/math_vector.cc
	intern/units_inline.cc

)

# -----------------------------------------------------------------------------
# Define Library Dependencies

set(LIB
	# Internal Library Dependencies
	
	# External Library Dependencies
	
)

# -----------------------------------------------------------------------------
# Declare Library

revlab_add_lib(revlib "${SRC}" "${INC}" "${INC_SYS}" "${LIB}")
add_library(revlab::source::revlib ALIAS revlib)

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
	tests/math_matrix_types.cc
	tests/math_vector_types.cc
	tests/units.cc

)

# -----------------------------------------------------------------------------
# Define Library Dependencies (Test)

set(LIB
	# Internal Library Dependencies
	revlab::source::revlib
	
	# External Library Dependencies
	
)

# -----------------------------------------------------------------------------
# Declare Test

revlab_add_test_executable(revlib "${TEST}" "${INC}" "${INC_SYS}" "${LIB}")
