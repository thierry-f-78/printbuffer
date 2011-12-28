#include "printbuffer.h"

struct printbuffer *printbuffer_mem_new(char **buffer, int block,
                                        void *(*pf_malloc)(size_t size),
                                        void (*pf_free)(void *ptr),
                                        void *(*pf_realloc)(void *ptr, size_t size))
{
	return _printbuffer_mem_new(buffer, block, pf_malloc, pf_free, pf_realloc);
}

struct printbuffer *printbuffer_bloc_new(char **buffer, int block)
{
	return _printbuffer_bloc_new(buffer, block);
}

struct printbuffer *printbuffer_new(char **buffer)
{
	return printbuffer_new(buffer);
}

void print_buffer_augment(struct printbuffer *pf, int nbytes)
{
	_print_buffer_augment(pf, nbytes);
}

int printbuffer_vprintf(struct printbuffer *pf, const char *format, va_list ap)
{
	return _printbuffer_vprintf(pf, format, ap);
}

int printbuffer_printf(struct printbuffer *pf, const char *format, ...)
{
	va_list ap;
	int ret;

	va_start(ap, format);
	ret = _printbuffer_vprintf(pf, format, ap);
	va_end(ap);

	return ret;
}

void printbuffer_cat_len(struct printbuffer *pf, const char *str, int len)
{
	_printbuffer_cat_len(pf, str, len);
}

void printbuffer_char(struct printbuffer *pf, char c)
{
	_printbuffer_char(pf, c);
}

void printbuffer_cat(struct printbuffer *pf, const char *str)
{
	_printbuffer_cat(pf, str);
}

void printbuffer_del_char(struct printbuffer *pf, int nchar)
{
	_printbuffer_del_char(pf, nchar);
}
