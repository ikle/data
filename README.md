# Common data manipulation structures and functions

## Build dependencies

*  C99;
*  GNU make.

## String Set Example

Let's give a small example of using sets:

```c
#include <data/set.h>
#include <data/string.h>

SET_DECLARE (string)

static const char *strings[] = {
	"test string #1",
	"Lorem ipsum dolor sit amet",
	"consectetur adipiscing elit",
	"sed do eiusmod tempor incididunt",
	"ut labore et dolore magna aliqua",
	"test string #2",
	NULL,
};

void f (void)
{
	const struct string **list = (void *) strings;
	struct string_set A;
	size_t i;
	const char *entry;

	string_set_init (&A);

	for (i = 0; list[i] != NULL; ++i)
		string_set_add (&A, list[i]);

	string_set_del (&A, list[3]);

	set_foreach (i, entry, &A)
		printf ("%2zu: %s\n", i, entry);

	string_set_fini (&A);
}
```

Note: error checks have been omitted for simplicity, see
[set-test.c](set-test.c) for a complete example.
