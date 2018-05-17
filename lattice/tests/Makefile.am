TESTS = \
	test-dag	\
	test-prondag	\
	$(NULL)

check_PROGRAMS = \
	test-dag	\
	test-prondag	\
	$(NULL)

AM_CPPFLAGS = -I$(top_srcdir)

test_dag_SOURCES = \
	test-dag.cxx	\
	$(NULL)

test_prondag_SOURCES = \
	test-prondag.cxx	\
	$(NULL)
test_prondag_LDADD = \
	$(top_builddir)/lattice/liblattice.la	\
	$(NULL)

