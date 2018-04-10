
int my_strlen(const char* dest)
{
	if(NULL == dest)
		return -1;
	int count = 0;
	while(*dest++ != '\0')
		count++;
	return count;
}

char* my_strcpy(char* dest,const char* src)
{
	if(NULL == dest || NULL == src)
		return NULL;
	char* tmp = dest;
	while(*src != '\0')
		*dest++ = *src++;
	
	*dest = '\0';
	return tmp;
}

//考虑重叠的strcpy
char* my_strcpy1(char* dest,const char* src)
{
	if(NULL == dest || NULL == src)
		return NULL;
	
	char* tmp_dest = dest;
	const char* tmp_src = src;
	int len = 0;
	while(*tmp_src++)
		len++;
	len++;
	
	if(src <= dest && dest <= src+len)
	{
		dest = dest + len;
		src = src + len;
		while(len--)
			*dest-- = *src--;
	}
	else
	{
		while(len--)
			*dest++ = *src++;
	}
	return tmp_dest;
}

 

//不考虑重叠
char* my_strncpy(char* dest,const char* src,size_t n)
{
	if(dest == NULL || src == NULL)
		return NULL;
	
	
	char* tmp = dest;

	while(n != 0)
	{
		*dest++ = *src++;
		--n;
	}
	
	if(n)// 
		while(--n)
			*dest = '\0';

	return tmp;
}

//考虑重叠的情况
char* my_strncpy1(char* dest,const char* src,int n)
{
	if(NULL == dest || NULL == src)
		return NULL;
	char* tmp = dest;

	if(dest >= src && dest <= src+n-1)
	{
		dest = dest + n -1;
		src = src+ n - 1;
		while(n!=0)
		{
			*dest-- = *src--;
			--n;
		}
	}
	else
	{
		while(n!=0)
		{
			*dest++ = *src++;
			--n;
		}
	}
	if(n)
		while(--n)
			*dest = '\0';
	return tmp;
}

char* my_strcat(char* dest,const char* src)
{
	if(NULL == dest || NULL == src)
		return NULL;
	char* tmp = dest;
	while(*dest)
		dest++;
	
	while((*dest++ = *src++) != '\0')
		;
	return tmp;
}

char* my_strncat(char* dest,const char* src,size_t n)
{
	if(NULL == dest || NULL == src)
		return NULL;
	char* tmp = dest;
	while(*dest)
		dest++;
	while(n--)
		if((*dest++ = *src++) == '\0')
			return tmp;
	*dest = '\0';
	return tmp;
}

int my_strcmp(const char* str1,const char* str2)
{
	if(NULL == str1 || NULL == str2)
		return 0;
	while(*str1++ == *str2++ && *str1 && *str2)
		;
	return (*str1-*str2);
}

int my_strncmp(const char* str1,const char* str2,size_t n)
{
	if(NULL == str1 || NULL == str2 || n==0)
		return 0;
	while(--n)
	{
		if(*str1 == *str2 && *str1 && *str2)
			str1++,str2++;
	}
	return (*str1-*str2);
}

void* my_memcpy(void* dest,const void* src,size_t n)
{
	if(NULL == dest || NULL == src)
		return NULL;
	void* tmp = dest;
	while(n--)
	{
		*(char*)dest = *(char*)src;
		dest = (char*)dest+1;
		src = (char*)src+1;
	}
	return tmp;
}

int my_memcmp(const void* str1,const void* str2,size_t n)
{
	if(NULL == str1 || NULL == str2)
		return 0;
	if(0 == n)
		return 0;
	while(--n)
	{
		if(*(char*)str1 == *(char*)str2 && *(char*)str1 && *(char*)str2)
		{
			str1 = (char*)str1 + 1;
			str2 = (char*)str2 + 1;
		}
	}
	return (*(char*)str1-*(char*)str2);
}

void* my_memmove(char*dest,const char* src,size_t n)
{
	if(NULL == dest || NULL == src)
		return NULL;
	void* tmp = dest;
	if(dest >= src && dest<= src+n-1)
	{
		dest = (char*)dest + n -1;
		src = (char*)src + n - 1;
		while(n--)
		{
			*(char*)dest = *(char*)src;
			dest = (char*)dest - 1;
			src = (char*)src - 1;
		}
	}
	else
	{
		while(n--)
		{
			*(char*)dest = *(char*)src;
			dest = (char*)dest + 1;
			src = (char*)src + 1;
		}
	}
	return tmp;
}


int main()
{
	char str1[] = "123456";
	char str2[] = "126";
	//char* ret = my_strncpy1(str1+2,str1,4);
	/*char* ret = my_strncat(str1,str2,2);
	printf("%s\n",ret);
	printf("%s\n",str1);*/
	//printf("%d\n",my_strlen(str));
	
	//printf("%d\n",my_strncmp(str1,str2,0));
	//my_memcpy(str1,str2,3);
	//printf("%s\n",str1);

	//printf("%d\n",my_memcmp(str1,str2,3));

	char* ret = my_strcpy1(str1+2,str1);
	//memmove(str1+2,str1,4);
	//my_memmove(str1+2,str1,4);
	printf("%s\n",str1);
	
}
