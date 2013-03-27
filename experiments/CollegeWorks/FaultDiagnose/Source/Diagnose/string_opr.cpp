/*  ���ļ��а������������ַ����������ܵĺ�����*/

#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<ctype.h>

#include	"macro.h"


char	*nli_get_compact_string(char	*);
int		nli_start_with_string(char *,char *);
int		nli_end_with_string(char *, char *);
char	* nli_trim(char	*);
int		nli_is_white_space(char *, int);
char	* nli_sub_string_tail(char *, int );
char	* nli_sub_string_middle(char *, int , int );
char	* nli_replace_with_string(char	*, char *, char *);
int		nli_index_of_string(char *, char *);
int		nli_last_index_of_string(char *, char *);
char	* nli_expand_string(char	*, float);
char	* nli_del_char(char *, char);
int		strcmp_ignore_case( char *, char *);


/*���Դ�str�Ƿ���pre_str��ͷ���ɹ�����SUCCESS,ʧ�ܷ���FAILURE*/
int	nli_start_with_string(char * str,char * pre_str)
{
	int	length,pre_str_length;

	if( pre_str == NULL )
		return FAILURE;
	
	//��ǿ���
	length = strlen(str);
	pre_str_length = strlen(pre_str);
	if (length<pre_str_length)
		return FAILURE;

	while( * pre_str == * str && * pre_str != STR_END)
	{
		str ++;
		pre_str ++;
	}
	
	if( * pre_str == STR_END )
		return	SUCCESS;
	else
		return	FAILURE;
}

/*���Դ�str�Ƿ���post_str��β���ɹ�����SUCCESS,ʧ�ܷ���FAILURE*/
int	nli_end_with_string(char *str, char * post_str)
{
	int	length,post_str_length;
	char	* temp_str;

	if( post_str == NULL )
		return	FAILURE;
	length = strlen(str);
	post_str_length = strlen(post_str);

	//��ǿ���
	if (length<post_str_length)
		return FAILURE;

	temp_str = str + length - post_str_length;

	if( strcmp( temp_str, post_str) == 0 )
		return	SUCCESS;
	else
		return	FAILURE;
}

/*�Ӵ�str�õ����մ��������أ�ɾ����ͷ���м�Ŀհ��ַ�*/
char	* nli_get_compact_string(char	*str)
{
	char	*result;
	int		i;
	int		j = 0;
	int		length = strlen(str);
	char	ch;
	int		half_total = 0;

	result = ( char * ) malloc( length+1 );
	for( i = 0; i < length; i ++)
	{
		ch = *( str + i );
		if( ch > 32 )
		{
			*( result + j ) = ch;
			j ++;
		}
		else	if( ch < 0 )
		{
			half_total ++;
			if( half_total % 2 == 1 && ( ch == -95 && *( str + i + 1) == -95 ) )
			{
				i ++;
				continue;
			}
			else
			{
				*( result + j ) = ch;
				j ++;
			}
		}
		//add by fqz
		else if (ch=' ')
		{
			//����Ӣ����ĸ֮��Ŀո�ɾ��
			if (i>0 && i<length-1)
				if (str[i-1]>='A' && str[i-1]<='z' && str[i+1]>='A' && str[i+1]<='z')
				{
					*( result + j ) = ch;
					j ++;
				}
		}
		
	}

	*( result + j ) = STR_END;

	return	result;
}


/*�õ���begin��ʼ��str���Ӵ�*/
char	* nli_sub_string_tail(char *str, int begin)
{
	char	* result;
	int		i,length = strlen(str);

	result = ( char * ) malloc( length - begin+1);
	for( i = begin; i < length; i ++)
		*( result + i - begin ) = *( str + i );

	*( result + i - begin ) = STR_END;

	return	result;
}

/*�õ���str�Ĵ�begin��ʼ��end(excluded)�������Ӵ�*/
char	* nli_sub_string_middle(char	*str, int begin, int end)
{
	char	* result;
	int		i,length = strlen(str);  

	result = ( char * ) malloc (end - begin + 2);
	for( i = begin;i < end; i ++)
		*( result + i - begin ) = *( str + i);

	*( result + i - begin ) = STR_END;

	return	result;
}

/*�����ڴ�str����new_sub_strȡ��old_sub_str�õ����´�*/
//���²����ڴ溯��-fqz
char	* nli_replace_with_string(char	*str, char *old_sub_str, char *new_sub_str)
{
	char	* result;
	char	*p;
	int		index;
	int		length,old_sub_length,new_sub_length;
	int		max;

	length = strlen(str);
	old_sub_length = strlen(old_sub_str);
	new_sub_length = strlen(new_sub_str);

	p = (char *)malloc(length+1);
	strcpy(p, str);
	result = p;

	while( (index = nli_index_of_string(p,old_sub_str)) != NONE )
	{
		result = (char *)malloc( strlen(p) + new_sub_length - old_sub_length + 1 );
		strncpy(result,p,index);
		*( result + index ) = STR_END;
		strcat(result,new_sub_str);
		max = strlen(p) - old_sub_length;
		if( index < max )
			strcat(result, p + index + old_sub_length);
		else
			strcat(result,"\0");
		free(p);
		p = result;
	}
	return	result;
}

/*�����ڴ�str�У��״γ���sub_str��λ����Ϣ*/
int	nli_index_of_string(char *str, char *sub_str)
{
	int	index = NONE;
	int	length,sub_length;
	int	i,j;

	length = strlen(str);
	sub_length = strlen(sub_str);

	for(i = 0 ;i <= length - sub_length; i ++)
	{
		for(j = 0; j < sub_length; j ++)
			if( *( str + i + j ) != *( sub_str + j ))
					break;
		if( j == sub_length)
		{
			index = i;
			break;
		}	
	}
	
	//�������������䣬�������ֲ���������ֵĴ���
	if (str[i]<0)
		i++;
	
	return	index;
}

int	nli_index_of_string_transmean(char *str, char *sub_str)
{
	int	index = NONE;
	int	length,sub_length;
	int	i,j;
	int half_count=0;

	length = strlen(str);
	sub_length = strlen(sub_str);
	for(i = 0 ;i <= length - sub_length; i ++)
	{
		if (str[i]<0)
		{
			half_count++;
			/*�����ǰ�ǵ�ż������Ǻ��ַ��������κβ���*/
			if(half_count==2)
			{
				half_count=0;
				continue;
			}
		}
		for(j = 0; j < sub_length; j ++)
			if( *( str + i + j ) != *( sub_str + j ))
					break;
		if( j == sub_length)
		{
			if (str[i-1]!='\\')
			{
				index = i;
				break;
			}
		}	
	}
	return	index;
}

/*�����ڴ�str�У����һ�γ���sub_str��λ����Ϣ*/
int	nli_last_index_of_string(char	*str, char *sub_str)
{
	int	index = NONE;
	int	length,sub_length;
	int	i,j;

	length = strlen(str);
	sub_length = strlen(sub_str);

	for(i = length - sub_length; i >= 0; i --)
	{
		for( j = 0 ; j < sub_length; j ++)
			if( *( str + i + j ) != *( sub_str + j ))
				break;
		if( j == sub_length)
		{
			index = i;
			break;
		}
	}
	return	index;
}

/* ����str�е��ַ�chɾ�� */
char * nli_del_char(char *str, char ch)
{
	char	*result;
	int		i,j,length;

	length = strlen(str);
	result = (char *)malloc(length+1);
	
	for( i = 0,j = 0;i < length; i ++)
		if( *( str + i ) != ch )
			*( result + j++ ) = *( str + i);

	*( result + j ) = '\0';

	return	result;
}


/*�������ķŴ����������ַ����Ŀռ䣬ͬʱ������������ */
char	* nli_expand_string(char	*str, float 	multiple)
{
	char	*result;
	int		i,length = 0;

	length = strlen(str);

	result = (char	*)malloc((int)(length * multiple)+1);
	for(i = 0 ;i < length; i ++)
		*( result + i ) = *( str + i );

	*( result + i ) = STR_END;

	free(str);

	return	result;
}


/*�Ƚ������ַ��������Դ�Сд�Ĳ��*/
int strcmp_ignore_case( char *string1, char *string2 )
{
	while( toupper(*string1) == toupper(*string2) )
	{
		if( * string1 == '\0' )
			return 0;
		string1 ++;
		string2 ++;
	}
	return	* string1 - * string2;
}

char *get_str_from_str(char *str,int startpos,char *substr,int transmean)
{
	//ע��ת�����
	int i;
	int length;
	char *tmpstr;

	length=strlen(str);
	if (startpos>=length)
		return NULL;
	else
	{
		tmpstr=str+startpos;
		if  (transmean==0)
			i=nli_index_of_string(tmpstr,substr);
		else
			i=nli_index_of_string_transmean(tmpstr,substr);
		if (i==-1)
			return nli_sub_string_middle(str, startpos, length);
		else
			return nli_sub_string_middle(str, startpos,i+startpos);
	}
}

/*��ԭ�ַ�����ָ��λ�ÿ�ʼ��ȡ�ַ�cǰ���Ӵ�*/
char *get_str_from_char(char c, char *str,int startpos)
{
	char *sub_str;
	int i,len;
	len=strlen(str);
	if (startpos>=len)
		return "";
	else
	{
		i=startpos;
		while (str[i] !=c && str[i]!='\0')
			i++;
		sub_str=nli_sub_string_middle(str, startpos, i);
		return sub_str;
	}
}
