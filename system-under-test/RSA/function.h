
long long candp(int m,int e,int p,int q)
{
	long long n=p*q;
	long long result=1;
	for(int i=0;i<e;i++)
	{
		long long temp=result*(m%n);
		result=result%n;
	}
	return result;
}

