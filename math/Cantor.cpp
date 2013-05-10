/*   Cantor展开    */

const int PermSize = 12;
int factory[PermSize] = 
{1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800, 39916800};
int Cantor(int a[])
{
  int i, j, counted;
	int result = 0;
	for (i = 0; i < PermSize; ++i)
	{
		counted = 0;
		for (j = i + 1; j < PermSize; ++j)
			if (a[i] > a[j])
				++counted;
		result = result + counted * factory[PermSize - i - 1];
	}
	return result;
}

bool h[13];

void UnCantor(int x, int res[])
{
	int i,j,l,t;
	for (i = 1;i <= 12;i++)
		h[i] = false;
	for (i = 1; i <= 12; i++)
	{
		t = x / factory[12 - i];
		x -= t * factory[12 - i];
		for (j = 1, l = 0; l <= t; j++)
			if (!h[j])l++;
		j--;
		h[j] = true;
		res[i - 1] = j;
	}
}
