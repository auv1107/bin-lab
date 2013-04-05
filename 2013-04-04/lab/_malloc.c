
#define NULL 0
struct str
{
	char *ch;
	struct str *next;
};


void init(struct str *s)
{
	s->ch = (char *) malloc (20);
	s->ch = "hahaha wode";

	struct str *n;
	n = (struct str*) malloc (20);
	n->ch = "hello world";
	n->next = NULL;
	s->next = n;
}

int main()
{
struct str s;
	init(&s);
	printf("%s\n", s.next->ch);
}
