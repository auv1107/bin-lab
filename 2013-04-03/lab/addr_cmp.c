
int main()
{
	char ch[2];
	if(ch > &ch[1])
		printf("1\n");
	if(&ch[1] > ch)
		printf("2\n");
}
