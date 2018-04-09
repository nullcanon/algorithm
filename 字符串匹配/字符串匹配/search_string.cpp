#include<string.h>
#include<stdio.h>
#include<math.h>
#include<vector>
#include<map>
#include<algorithm>
using namespace std;

/**************************** 暴力匹配 ****************************/
void NaiveSearch(const char* T,const char* P)
{
	int n = strlen(T);
	int m = strlen(P);
	for (int s = 0; s < n - m+1; ++s)
	{
		int i = s, j = 0;
		for (;j < m-1;)
		{
			if (T[i] == P[j]) ++i, ++j;
			else break;
		}
		if (T[i] == P[j])
			printf("%d\n",s);		
	}
}

/**************************** Rabin-Karp算法 ****************************/
//d为基数,q为素数
//处理一般ASCII,d取128,q取6999997
void RKSearch(const char* T,const char* P,int d = 128,int q = 6999997)
{
	int n = strlen(T);
	int m = strlen(P);
	int h = ((int)pow((double)d, m - 1)) % q;
	int p = 0, t = 0;
	
	int i = 0;
	for (; i < m; ++i)//预处理
	{
		p = (d*p + P[i]) % q;
		t = (d*t + T[i]) % q;
	}
	int s = 0;
	for (; s < n - m+1; ++s)//匹配
	{
		if (p == t)
		{
			int i = s, j = 0;
			for (; j < m - 1;)//进一步筛选
			{
				if (T[i] == P[j]) ++i, ++j;
				else break;
			}
			if (T[i] == P[j])
				printf("%d\n", s);
		}
		if (s < n - m)//更新t为ts+1
			t = (d*(t - T[s] * h%q+q) +( T[s + m])) % q;
	}
}
/**************************** 有限自动机匹配 ****************************/
typedef vector<map<char, int> > TAB;

//判断P[0..k-1]是否为P[0...q-1]+ch的后缀
bool IsPrefix(const char*P, int k, int q, char ch)
{
	if (0 == k)
		return true;
	if (1 == k)
		return (P[0] == ch);
	return (P[k - 1] == ch && (strncmp(P, P + q - k + 1, k - 1) == 0));
}

//构建跳转表
TAB TransitionFun(const char* P,const char* CharTab)
{
	int m = strlen(P);
	TAB TransitionMap(m+1);
	for (int q = 0; q < m; ++q)//q表示状态
	{
		int j = 0;
		while (CharTab[j] != '\0')
		{
			int k = min(m + 1, q + 2);

			while (!IsPrefix(P, k, q, CharTab[j]))
				--k;

			TransitionMap[q][CharTab[j]] = k;
			++j;
		}
	}
	return TransitionMap;
}

void AutoMatcherSearch(const char* T, const char* P,const char* CharTab)//Chartab表示字母表集
{
	int n = strlen(T);
	int m = strlen(P);
	int q = 0;//q表示状态
	TAB g = TransitionFun(P,CharTab);
	for (int i = 0; i < n; ++i)
	{
		q = g[q][T[i]];//变迁
		if (q == m)//达到YES状态,输出偏移量
			printf("%d\n", i - m+1);
	}
}
/**************************** KMP算法 ****************************/
void PrefixTable(const char* P, int prefix[], int n)//n为前缀表的长度
{
	prefix[0] = 0;
	int len = 0;
	int i = 1;
	while (i < n)
	{
		if (P[len] == P[i])
		{
			len++;
			prefix[i] = len;
			i++;
		}
		else
		{
			//不相等的情况 例如ABA+A的情况
			//len-1所对应的值就是新的len的取值
			if (len > 0)
				len = prefix[len - 1];
			else
			{
				prefix[i] = len;
				i++;
			}
		}
	}
}

void MovePrefixTable(int prefix[], int n)
{
	for (int i = n - 1; i > 0; i--)
		prefix[i] = prefix[i - 1];
	prefix[0] = -1;
}

void KMPSearch(const char* T, const char* P)
{
	int n = strlen(T);
	int m = strlen(P);
	int* prefix = new int[n];
	PrefixTable(P,prefix,n);
	MovePrefixTable(prefix,n);
	int q = 0;//q控制着P,i控制着T
	for (int i = 0; i < n;)
	{
		if (q == m - 1 && P[q] == T[i])
		{
			printf("%d\n", i - q);
			q = prefix[q];//匹配到了继续迭代
		}

		if (P[q] == T[i]) i++, q++;
		else
		{
			q = prefix[q];
			if (q == -1) i++, q++;
		}
	}
}

/**************************** test ****************************/
void TestKMPSearch()
{
	char* T = "abcabaabcabaa";
	char* P = "abaa";
	KMPSearch(T, P);
}
void TestPrefixTable()
{
	char* P = "ABAB";
	int n = strlen(P);
	int* prefix = new int[n];
	PrefixTable(P,prefix,n);
	for (int i = 0; i < n;++i)
		printf("%d\n",prefix[i]);
}
void TestAutoMatcherSearch()
{
	char* chartab = "abc";
	char* T = "abcabaabcabaa";
	char* P = "abaa";
	
	AutoMatcherSearch(T, P, chartab);
}

void TestRKSearch()
{
	/*char* T = "2359023141526739921";
	char* P = "31415";*/
	char* T = "abcabaabcabaa";
	char* P = "abaa";
	RKSearch(T,P);

}

void TestNaiveSearch()
{
	char* T = "abcabaabcabaa";
	char* P = "abaa";
	NaiveSearch(T, P);
}

int main()
{
	//TestNaiveSearch();
	/*int i = INT_MAX;

	int n = (i + 1)%7;*/

	//TestRKSearch();
	//TestAutoMatcherSearch();
	//TestPrefixTable();
	TestKMPSearch();
	return 0;
}