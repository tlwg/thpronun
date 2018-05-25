TESTS = \
	test-dict.sh	\
	$(NULL)

check_SCRIPTS = \
	test-dict.sh	\
	$(NULL)

check_PROGRAMS = \
	test-dict	\
	$(NULL)

EXTRA_DIST = \
	test-dict.sh	\
	test.lst	\
	$(NULL)

CLEANFILES = \
	test.dic	\
	$(NULL)

AM_CPPFLAGS = -I$(top_srcdir)

test_dict_SOURCES = \
	test-dict.cxx	\
	$(NULL)
test_dict_LDADD = \
	$(top_builddir)/dict/libdict.la	\
	$(NULL)

