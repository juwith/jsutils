bin_PROGRAMS = hello_queue

hello_queue_SOURCES = main.c

hello_queue_CFLAGS = \
	-I$(top_srcdir)/src \
	$(QUEUE_CFLAGS)

hello_queue_LDADD = \
	$(top_builddir)/src/libmessage.la

hello_LDFLAGS = \
	-lpthread
