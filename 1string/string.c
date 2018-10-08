

void strtoupper(char *str)
{
	while(*str)
	{
		if(*str >= 'a' && *str <= 'z')
			*str += 'A'-'a';
		++str;
	}
}

void strtolower(char *str)
{		
	while(*str)
	{
		if(*str >= 'A' && *str <= 'Z')
			*str += 'a'-'A';
		++str;
	}

}
