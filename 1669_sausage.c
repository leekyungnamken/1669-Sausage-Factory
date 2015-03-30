#include <stdio.h>
#include <assert.h>

struct sausage {
int length;
int width;
};

struct sausage sausage[5000];

int ooo[5000];
int ooo_count;

int in_order(int x, int y)
{
	if (x < y) return 1;
	else return 0;
}

void quick_sort(struct sausage list[], int left, int right)
{
        int i, j;
        struct sausage t;
        int key = list[left].length;

        i = left;
        j = right;

        if (right < 0) return;
        if (left >= right) return;

        if (right - left == 1)
        {
                if (in_order(list[left].length, list[right].length)) return;
                else
                {
                        t = list[left];
                        list[left] = list[right];
                        list[right] = t;
                }
                return;
        }

        j = j+1;

        do {
                i++;
                while(in_order(list[i].length, key) && i <= right )
                {
                        i++;
                }

                j--;
                while(in_order(key, list[j].length) && j >= left)
                {
                        j--;
                }
                if (i < j)
                {
                        t = list[i];
                        list[i] = list[j];
                        list[j] = t;
                }
        } while(i < j);

        {
                t = list[left];
                list[left] = list[j];
                list[j] = t;
        }
        quick_sort(list, left, j-1);
        quick_sort(list, i, right);

}

void sort_sausage_length(int nSausage)
{
	quick_sort(sausage, 0, nSausage-1);
}

int is_in_order(int i, int j)
{
assert(i >= 0);
assert(j >= 0);

	if ((sausage[i].length <= sausage[j].length) &&
	    (sausage[i].width <= sausage[j].width))
	{
		return 1;
	}
	else return 0;
}

void find_ooo_sausage(int nSausage)
{
	int i;
	ooo_count = 0;
	for(i=0;i<nSausage-1;i++)
	{
		if (is_in_order(i, i+1) == 0)
		{
			ooo[ooo_count] = i+1;
			ooo_count++;
		}
	}
}

void exchange(int i, int j)
{
assert(i >= 0);
assert(j >= 0);
	sausage[j] = sausage[i];
	sausage[i] = sausage[i-1];
}

int is_safe_remove(int i)
{
assert(i >= 0);

	if (is_in_order(i-1, i+1) == 1) return 1;
	else return 0;
}

int is_fit(int i, int j)
{
assert(i >= 0);
assert(j >= 0);
	if (is_in_order(i, j)) return 1;
	else return 0;
}

int is_exchangeable(int i, int j)
{
assert(i >= 0);
assert(j >= 0);
	if (is_safe_remove(i) == 0)
		return 0;

	if (is_fit(i, j) == 0)
		return 0;

	return 1;
}

void f(int ooo_index)
{
	int i, j, ie;
	for(i=ooo_index;i<ooo_count-1;i++)
	{
		for(j=i+1;j<ooo_count;j++)
		{
			ie = is_exchangeable(ooo[i], ooo[j]);
			if (ie)
			{
				exchange(ooo[i], ooo[j]-1);
				ooo[i] = -1;
				ooo[j] = ooo[j] - 1;
				break;
			}
		}
	}
}

void process(int nSausage)
{
	find_ooo_sausage(nSausage);
}

void printooo()
{
	int i;
	int count = 0;
	for(i=0;i<ooo_count;i++)
	{
		if(ooo[i] != -1)
		{
			count++;
		}
	}
	printf("%d\n", count+1);
}

void printsausage(nSausage)
{
	int i;
	for(i=0;i<nSausage;i++)
	{
		printf("%d%d", sausage[i].length, sausage[i].width);
	}
}


int ff(struct sausage list[], int nCount, int plen, int pwid) 
{
	struct sausage head;
	int totalTime, minTotalTime;
	int i;

	if(nCount == 2)
	{
		int time01, time10;
		time01 = time10 = 0;

		/* 01 */
		if ((plen > list[0].length) || (pwid > list[0].width)) time01++;
		if ((list[0].length > list[1].length) || (list[0].width > list[1].width)) time01++;

		/* 10 */
		if ((plen > list[1].length) || (pwid > list[1].width)) time10++;
		if ((list[1].length > list[0].length) || (list[1].width > list[0].width)) time10++;

		if (time01 < time10) return time01;
		else return time10; 
	}
	
	totalTime = 0;
	minTotalTime = 10000;
	for(i=0;i<nCount;i++)
	{
		int time = 0;
		head = list[i];
		if((head.length < plen) || (head.width < pwid))
		{
			time = 1;
		}
		
		list[i] = list[nCount-1];
		
		totalTime = time + ff(list, nCount-1, head.length, head.width);
		
		list[i] = head;
		if(minTotalTime > totalTime)
		{
			minTotalTime = totalTime;
		} 
	}
	return minTotalTime;
}

int main()
{
	int i;
	int nSausage;
	int length, width;
	int ooocount, pooocount;
	scanf("%d", &nSausage);

	for(i=0;i<nSausage;i++)
	{
		scanf("%d %d", &length, &width);
		sausage[i].length = length;
		sausage[i].width = width;
	}

/*
	sort_sausage_length(nSausage);

	process(nSausage);
	ooocount = ooo_count;
	pooocount = 0;
	while(pooocount != ooocount)
	{
	pooocount = ooocount;
	f(0);

	find_ooo_sausage(nSausage);
	ooocount = ooo_count;
	}
*/

/*
	ooo_count = ff(sausage, nSausage, 0, 0);
*/
	printf("%d\n", ooo_count+1);

	return 0;
}

