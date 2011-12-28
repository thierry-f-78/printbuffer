#include "printbuffer.h"

struct printbuffer *printbuffer_mem_new(int block,
                                        void *(*pf_malloc)(size_t size),
                                        void (*pf_free)(void *ptr),
                                        void *(*pf_realloc)(void *ptr, size_t size))
{
	return _printbuffer_mem_new(block, pf_malloc, pf_free, pf_realloc);
}

struct printbuffer *printbuffer_bloc_new(int block)
{
	return _printbuffer_bloc_new(block);
}

struct printbuffer *printbuffer_new()
{
	return printbuffer_new();
}

char *printbuffer_get_buffer(struct printbuffer *pf)
{
	return _printbuffer_get_buffer(pf);
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

void printbuffer_cat_static(struct printbuffer *pf, const char *str)
{
	_printbuffer_cat_static(pf, str);
}

void printbuffer_del_char(struct printbuffer *pf, int nchar)
{
	_printbuffer_del_char(pf, nchar);
}

#ifdef TU

extern char **environ;

int main(void)
{
	int i;
	char *buffer;
	struct printbuffer *pf;

	pf = printbuffer_bloc_new(10);

	for (i=0; environ[i] != NULL; i++)
		_printbuffer_printf(pf, "env[%d]: %s\n", i, environ[i]);

	_printbuffer_cat(pf, "c'est fini\n");
	_printbuffer_cat_len(pf, "c'est fini...", strlen("c'est fini..."));
	_printbuffer_del_char(pf, 3);
	_printbuffer_cat_static(pf, "\n");

	printf("%s", _printbuffer_get_buffer(pf));
}
#endif
