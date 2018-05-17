TESTS = \
	test-syl	\
	test-sylstring	\
	$(NULL)

check_PROGRAMS = \
	test-syl	\
	test-sylstring	\
	$(NULL)

AM_CPPFLAGS = -I$(top_srcdir)

test_syl_SOURCES = \
	test-syl.cxx	\
	$(NULL)
test_syl_LDADD = \
	$(top_builddir)/sylstring/libsylstring.la	\
	$(NULL)

test_sylstring_SOURCES = \
	test-sylstring.cxx	\
	$(NULL)
test_sylstring_LDADD = \
	$(top_builddir)/sylstring/libsylstring.la	\
	$(NULL)

