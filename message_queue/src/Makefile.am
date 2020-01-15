lib_LTLIBRARIES = libmessage.la

libmessage_la_SOURCES = \
	message.c

include_HEADERS = \
	message.h

libmessage_la_CFLAGS = \
	$(QUEUE_CFLAGS) \
	-lpthread

libmessage_la_LDFLAGS = \
	$(QUEUE_LIBS) \
	-lpthread