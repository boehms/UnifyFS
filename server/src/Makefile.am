noinst_LIBRARIES = libunifyfsd.a

libunifyfsd_a_SOURCES = \
    arraylist.c \
    arraylist.h \
    margo_server.c \
    margo_server.h \
    unifyfs_cmd_handler.c \
    unifyfs_global.h \
    unifyfs_metadata.c \
    unifyfs_metadata.h \
    unifyfs_request_manager.c \
    unifyfs_request_manager.h \
    unifyfs_service_manager.c \
    unifyfs_service_manager.h \
    unifyfs_sock.c \
    unifyfs_sock.h

bin_PROGRAMS = unifyfsd

unifyfsd_SOURCES = unifyfs_init.c

unifyfsd_LDFLAGS = -static \
  $(LEVELDB_LDFLAGS) \
  $(MARGO_LDFLAGS) \
  $(FLATCC_LDFLAGS)

unifyfsd_LDADD = \
    libunifyfsd.a \
    $(top_builddir)/common/src/libunifyfs_common.la \
    $(top_builddir)/meta/src/libmdhim.a \
    $(LEVELDB_LIBS) \
    $(MPI_CLDFLAGS) \
    $(MARGO_LIBS) \
    $(FLATCC_LIBS) \
    -lpthread -lm -lstdc++ -lrt

AM_CPPFLAGS = \
  -I$(top_srcdir)/common/src \
  -I$(top_srcdir)/client/src \
  -I$(top_srcdir)/meta/src \
  -I$(top_srcdir)/meta/src/uthash \
  -I$(top_srcdir)/meta/src/Mlog2

AM_CFLAGS = -Wall \
  $(LEVELDB_CFLAGS) \
  $(MPI_CFLAGS) \
  $(MERCURY_CFLAGS) \
  $(ARGOBOTS_CFLAGS) \
  $(MARGO_CFLAGS) \
  $(FLATCC_CFLAGS)

CLEANFILES = $(bin_PROGRAMS)
