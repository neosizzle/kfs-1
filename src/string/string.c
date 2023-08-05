int strlen(const char* str) 
{
	int len = 0;
	while (str[len])
		len++;
	return len;
}

void reverse(char s[])
{
    int i, j;
    char c;

    for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

void itoa(int n, char s[])
{
    int i, sign;

    if ((sign = n) < 0)  /* record sign */
        n = -n;          /* make n positive */
    i = 0;
    do {       /* generate digits in reverse order */
        s[i++] = n % 10 + '0';   /* get next digit */
    } while ((n /= 10) > 0);     /* delete it */
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}

int	strncmp(const char *s1, const char *s2, int n)
{
	if (!n)
		return (0);
	while ((*s1) && (*s1 == *s2) && --n)
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

int	strcmp(const char *s1, const char *s2)
{
	if (strlen(s1) > strlen(s2))
		return strncmp(s1, s2, strlen(s1));
	return strncmp(s1, s2, strlen(s2));
}