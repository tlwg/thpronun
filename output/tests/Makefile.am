TESTS = \
	test-sylstring	\
	test-list	\
	$(NULL)

check_PROGRAMS = \
	test-sylstring	\
	test-list	\
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

