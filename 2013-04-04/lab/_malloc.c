
#define NULL 0
struct str
{
	char *ch;
	int n;
	struct str *next;
};

struct str *s;

void cpynch(char *n)
{
	strcpy(n, "hello");
}
void init()
{
	s = (struct str*) malloc (sizeof(struct str));
	s->ch = (char *) malloc (12);
	s->ch = "hahaha wode";

	struct str *n;
	n = (struct str*) malloc (sizeof(struct str));
	n->ch = (char *) malloc (6);
	
//	n->ch = (char *)
	cpynch(n->ch);
	n->n = 5;
	
	
//	n->ch = (char *)malloc(12);
//	n->ch = "hello world, nihao\nfjdlsal jldfkjs l owripjrwperp e jrpewj rpegflskjfdslkfj dlkj ljeskl";
	n->next = NULL;
	s->next = n;
//	printf("%s\n", n.ch);
}

int main()
{
	init();
	printf("sizeof str: %d\n", sizeof(int) );
//	printf("%s\n", s->ch);
	printf("%s\n", s->next->ch);
	printf("%d\n", s->next->n);
}
