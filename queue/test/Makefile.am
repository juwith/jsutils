bin_PROGRAMS = hello_queue

hello_queue_SOURCES = main.c

hello_queue_CFLAGS = \
	-I$(top_srcdir)/src

hello_queue_LDADD = \
	$(top_builddir)/src/libqueue.la \
	-lpthread
