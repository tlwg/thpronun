TESTS = \
	test-parser	\
	$(NULL)

check_PROGRAMS = \
	test-parser	\
	$(NULL)

AM_CPPFLAGS = -I$(top_srcdir)

test_parser_SOURCES = \
	test-parser.cxx	\
	$(NULL)
test_parser_LDADD = \
	$(top_builddir)/parser/libparser.la	\
	$(top_builddir)/output/liboutput.la	\
	$(NULL)

