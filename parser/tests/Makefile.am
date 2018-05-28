TESTS = \
	test-parser	\
	$(NULL)

check_PROGRAMS = \
	test-parser	\
	$(NULL)

check_DATA = \
	except.dic	\
	$(NULL)

EXTRA_DIST = \
	except.lst	\
	$(NULL)

CLEANFILES = \
	except.dic	\
	$(NULL)

AM_CPPFLAGS = -I$(top_srcdir)

test_parser_SOURCES = \
	test-parser.cxx	\
	$(NULL)
test_parser_LDADD = \
	$(top_builddir)/parser/libparser.la	\
	$(top_builddir)/output/liboutput.la	\
	$(NULL)

except.dic: except.lst
	$(top_builddir)/dict/gen-lookup-dict $< $@
