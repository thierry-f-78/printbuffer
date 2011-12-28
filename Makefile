CFLAGS = -g

all: libprintbuffer.so printbuffer

libprintbuffer.so: libprintbuffer-static.a
	$(LD) -o libprintbuffer.so -shared -soname libprintbuffer.so.0.0 libprintbuffer-static.a

libprintbuffer-static.a: printbuffer.o
	$(AR) -rvc libprintbuffer-static.a printbuffer.o

printbuffer: printbuffer_tu.o
	$(CC) $(LDFLAGS) -o printbuffer printbuffer_tu.o

printbuffer_tu.o: printbuffer.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -DTU=1 -c -o $@ $<

clean:
	rm -f printbuffer printbuffer.o printbuffer_tu.o libprintbuffer.so libprintbuffer-static.a
