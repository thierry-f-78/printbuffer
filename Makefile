OBJS = printbuffer.o

libprintbuffer.so: libprintbuffer-static.a
	$(LD) -o libprintbuffer.so -shared -soname libprintbuffer.so.0.0 libprintbuffer-static.a

libprintbuffer-static.a: $(OBJS)
	$(AR) -rvc libprintbuffer-static.a $(OBJS)

clean:
	rm -f $(OBJS) libprintbuffer.so libprintbuffer-static.a
