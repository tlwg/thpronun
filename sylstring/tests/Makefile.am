TESTS = \
	test-sylcomp	\
	test-sylstring	\
	$(NULL)

check_PROGRAMS = \
	test-sylcomp	\
	test-sylstring	\
	$(NULL)

AM_CPPFLAGS = -I$(top_srcdir)

test_sylcomp_SOURCES = \
	test-sylcomp.cxx	\
	$(NULL)
test_sylcomp_LDADD = $(top_builddir)/sylstring/libsylstring.la

test_sylstring_SOURCES = \
	test-sylstring.cxx	\
	$(NULL)
test_sylstring_LDADD = $(top_builddir)/sylstring/libsylstring.la

