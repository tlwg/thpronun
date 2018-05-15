AM_CPPFLAGS = -I. -I$(top_srcdir)

noinst_LTLIBRARIES = liblattice.la

liblattice_la_SOURCES = \
	lattice.h	\
	lattice.inl	\
	lattice.cxx	\
	$(NULL)

liblattice_la_LIBADD = \
	$(top_builddir)/sylstring/libsylstring.la	\
	$(NULL)

