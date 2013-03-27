#pragma once

#define dbger_inline __forceinline

dbger_inline char * dbger_strcpy(char * dst, const char * src)
{
	char * cp = dst;

	while( *cp++ = *src++ )
		;               /* Copy src over dst */

	return( cp-1 );
}

dbger_inline bool LoadFile(const char* fileName, char*& outBuffer, long& fileSize)
{
	ifstream streamGeom;
	streamGeom.open(fileName);
	if(!streamGeom) return false;

	// get pointer to associated buffer object
	filebuf *pFilebuf;
	pFilebuf=streamGeom.rdbuf();

	// get file size using buffer's members
	fileSize=pFilebuf->pubseekoff (0,ios::end,ios::in);
	pFilebuf->pubseekpos (0,ios::in);

	// allocate memory to contain file data
	outBuffer= (char*)malloc(fileSize+1);

	// get file data  
	pFilebuf->sgetn (outBuffer,fileSize);

	outBuffer[fileSize] = '\0';
	streamGeom.close();

	return true;
}

dbger_inline float GetNextValue(char*& p)
{
	char* szValue = p;
	while(*p++ != ' ');
	*(p-1) = '\0';
	return (float)atof(szValue);
}

dbger_inline float GetLastValue(char*& p)
{
	char* szValue = p;
	while(*p++ != '\n');
	*(p-1) = '\0';
	return  (float)atof(szValue);

}

dbger_inline char* MoveToTriangle(char* p, int num)
{
	int numlines = num * 3;
	while (numlines--)
	{
		while(*p++ != '\n');
	}
	return p;
}

dbger_inline char* MoveToRay(char* p, int num)
{
	int numlines = num * 2;
	while (numlines--)
	{
		while(*p++ != '\n');
	}
	return p;
}