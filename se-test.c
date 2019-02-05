#include <err.h>
#include <stdio.h>

#include <data/se.h>

static const char *strings[] = {
	"test string #1",
	"Lorem ipsum dolor sit amet",
	"consectetur adipiscing elit",
	"sed do eiusmod tempor incididunt",
	"ut labore et dolore magna aliqua",
	"test string #2",
	NULL,
};

static void test_atom (struct se_scope *scope, const char *name)
{
	struct se *o;

	if ((o = se_atom (scope, name)) == NULL)
		err (1, "cannot allocate atom");

	printf ("%p: %s\n", o, se_atom_name (o));
}

static void test_atoms (void)
{
	struct se_scope *scope;
	const char **p;

	if ((scope = se_scope_alloc (0)) == NULL)
		err (1, "cannot allocate scope");

	for (p = strings; *p != NULL; ++p)
		test_atom (scope, *p);

	test_atom (scope, strings[1]);
	test_atom (scope, strings[3]);

	se_scope_free (scope);
}

static void test_pairs (void)
{
	struct se_scope *s;
	struct se *o = NULL;

	if ((s = se_scope_alloc (0)) == NULL)
		err (1, "cannot allocate scope");

	o = se_list (
		se_atom (s, "add"), se_atom (s, "13"), se_atom (s, "72"),
		se_list (
			se_atom (s, "mul"), se_atom (s, "x yz"),
			se_atom (s, "\003"),
			se_atom (s, "5"), se_atom (s, "m"), NULL
		),
		se_atom (s, "string \"in quotes\" with \\-func"),
		NULL
	);

	se_show (o, stdout);
	printf ("\n");

	o = se_pair (o, se_atom (s, "non-nil"));
	se_show (o, stdout);
	printf ("\n");

	se_free (o);
	se_scope_free (s);
}

int main (int argc, char *argv[])
{
	printf ("test atom table:\n\n");
	test_atoms ();
	printf ("\ntest se pairs and lists:\n\n");
	test_pairs ();
	return 0;
}
