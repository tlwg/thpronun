TESTS = \
	test-sylstring	\
	test-list	\
	test-lattice	\
	$(NULL)

check_PROGRAMS = \
	test-sylstring	\
	test-list	\
	test-lattice	\
	$(NULL)

AM_CPPFLAGS = -I$(top_srcdir)

test_sylstring_SOURCES = \
	test-sylstring.cxx	\
	$(NULL)
test_sylstring_LDADD = $(top_builddir)/output/liboutput.la

test_list_SOURCES = \
	test-list.cxx	\
	$(NULL)
test_list_LDADD = $(top_builddir)/output/liboutput.la

test_lattice_SOURCES = \
	test-lattice.cxx	\
	$(NULL)
test_lattice_LDADD = \
	$(top_builddir)/lattice/liblattice.la	\
	$(top_builddir)/output/liboutput.la	\
	$(NULL)

