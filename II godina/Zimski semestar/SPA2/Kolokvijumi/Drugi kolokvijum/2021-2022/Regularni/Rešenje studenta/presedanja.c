#include<stdio.h>
#include<stdlib.h>

#define NEPOVEZAN 0
#define POVEZAN 1
#define INF -1
#define UNDF -2
#define TRUE 1
#define FALSE 0

typedef struct element
{
	int cvor;
	struct element *sledeci;
} Element;

void dodaj( Element **pocetak, Element **kraj, int u)
{
	Element *novi = (Element*)malloc(sizeof(Element));
	novi->cvor = u;
	novi->sledeci = NULL;
	if( *pocetak ==NULL)
	{
		*pocetak = novi;
		*kraj = novi;
	}
	else
	{
		(*kraj)->sledeci = novi;
		*kraj = novi;
	}
}

int skini( Element **pocetak, Element **kraj)
{
	if( *pocetak == NULL)
		return( UNDF);
	else
	{
		int u = (*pocetak)->cvor;
		Element *temp = *pocetak;
		if( (*pocetak)->sledeci == NULL)
			*kraj = NULL;
		*pocetak = (*pocetak)->sledeci;
		free(temp);
		return(u);
	}
}

int jeManji( int x, int y)
{
	if( x== INF)
		return( FALSE);
	else if( y==INF)
		return( TRUE);
	else
		return( x<y);
}

int main()
{
	int **graf;
	int *dx, *dy;
	int n, m, x, y, z, u;
	scanf("%d%d",&n,&m);
	
	// ALOK I INIC
	graf = (int**)malloc(n*sizeof(int*));
	dx = (int*)malloc(n*sizeof(int));
	dy = (int*)malloc(n*sizeof(int));
	int i;
	for(i=0;i<n;i++)
	{
		graf[i] = (int*)malloc(n*sizeof(int));
		for( int j=0;j<n;j++)
		{
			graf[i][j] = NEPOVEZAN;
		}
		dx[i] = UNDF;
		dy[i] = UNDF;
	}
	
	for( int i=0; i<m; i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		graf[u][v] = POVEZAN;
		graf[v][u] = POVEZAN;
	}
	
	scanf("%d%d",&x,&y);
	
	// BFS
	dx[x] = 0;
	Element *pocetak, *kraj;
	pocetak = NULL;
	kraj = NULL;
	dodaj( &pocetak, &kraj, x);
	while((u=skini( &pocetak,&kraj)) != UNDF)
	{
		for(int v=0;v<n;v++)
		{
			if( graf[u][v] == POVEZAN && dx[v] == UNDF)
			{
				dx[v] = dx[u] + 1;
				dodaj( &pocetak, &kraj, v);			
			}
		}
	}
	dy[y] = 0;
	pocetak = NULL;
	kraj = NULL;
	dodaj( &pocetak, &kraj, y);
	while((u=skini( &pocetak,&kraj)) != UNDF)
	{
		for(int v=0;v<n;v++)
		{
			if( graf[u][v] == POVEZAN && dy[v] == UNDF)
			{
				dy[v] = dy[u] + 1;
				dodaj( &pocetak, &kraj, v);			
			}
		}
	}

	// LOKACIJA
	int min = INF;
	int imin = UNDF;
	
	for( int i=0; i<n; i++)
		if( dx[i] == dy[i])
			if( jeManji( dx[i], min) )
			{
				min = dx[i];
				imin = i;
			}
	
	z = imin;
	
	if( z == UNDF)
		printf("NE POSTOЈI\n");
	else
		printf("%d\n", z);

	return(0);
}
/*
6 6
0 1
1 2
0 3
3 4
4 5
2 5
0 2
---
1
*/
/*
7 9
0 1
0 6
0 3
1 6
2 4
2 6
3 4
3 5
4 5
0 2
---
6
*/
/*
10 10
0 1
1 2
2 3
3 4
4 5
5 6
6 7
7 8
8 9
9 0
1 9
---
0
*/
