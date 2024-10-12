all:
	  gcc toralize.c -o toralize.so -fPIC -shared -ldl -D_GNU_SOURCE
		# Compile toralize.c into a shared library (toralize.so) with position-independent code (PIC).
		# -o toralize.so: Output file name.
		# -fPIC: Generate position-independent code for shared library.
		# -shared: Create a shared library.
		# -ldl: Link with the dynamic linking library (libdl) for dlsym and dlopen functions.
		# -D_GNU_SOURCE: Enable GNU-specific extensions.
