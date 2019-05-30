#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <time.h>
#include <stdlib.h> 
#include <math.h>
const int SIZE = 100;
struct Item {
	int indx;
	double weight;
	Item *next;
};
struct Point {
	double d;
	Point* pred;
	int indx;
	double x;
	double y;
	Item *list;
};
struct Table {
	int n;
	Point point[SIZE];
};
int DAddPoint(Table *);
int DAddReb(Table *);
int DDeletePoint(Table *);
int DFindWay(Table *);
int DShowGraph(Table *);
void init(Table *);
int dialog();
int getInt(int *);
char *getStr();
int AddPoint(Table *, int, int, int);
int AddReb(Table *, int, int);
int FindPoint(Table *, int);
int DeletePoint(Table *, int);
void DeleteReb(Item *, int);
double Dijkstra(Table *, int, int);
int ExtractMin(Table*, int*, int*);
void RemoveNum(Table *, int*, int*);
void RemoveNum1(Table*, int*, int*, int);
int min(Table *, int, int);
int FindNum(int*, int*, int);
int(*fptr[])(Table *) = { NULL,DAddPoint,DAddReb,DDeletePoint,DFindWay,DShowGraph/*,timing*/ };
int main() {
	int rc;
	Table tbl;
	init(&tbl);
	while (rc = dialog()) {
		if (fptr[rc](&tbl))
			break;
	}
	return 0;
}
void init(Table *tbl) {
	int i;
	tbl->n = 0;
	for (i = 0; i < SIZE; ++i)
		tbl->point[i].list = NULL;
}
int dialog() {
	int nom, n, i;
	char *ptr[7] = { "0.Quit","1.AddPoint","2.AddReb","3.DeletePoint","4.FindWay","5.ShowGraph" ,"6.Timing" };
	printf("Menu\n");
	for (i = 0; i< 7; ++i)
		printf("%s\n", ptr[i]);
	printf("vvedite nomer deistvie\n");
	if (!(n = getInt(&nom)) || (nom > 6) || (nom < 0)) {
		printf("wrong enter\n");
		return 0;
	}
	else
		return nom;
}
int getInt(int *ptr) {
	int n;
	n = scanf("%d", ptr);
	return n > 0 ? 1 : 0;
}
char *getStr() {
	char * ptr = (char *)malloc(1);
	char buf[81];
	int n, len = 0;
	*ptr = '\0';
	do {
		n = scanf("%80[^\n]", buf);
		if (n < 0) {
			free(ptr);
			ptr = NULL;
			continue;
		}
		if (n == 0)
			scanf("%*c");
		else {
			len += strlen(buf);
			ptr = (char*)realloc(ptr, len + 1);
			strcat(ptr, buf);
		}
	} while (n > 0);
	return ptr;
}
int DAddPoint(Table *tbl) {
	int indx,x,y,n;
	printf("Enter name and ñoordinates\n");
	if (getInt(&indx) == 0) {
		printf("wrong enter\n");
		return 1;
	}
	if (getInt(&x) == 0) {
		printf("wrong enter\n");
		return 1;
	}
	if (getInt(&y) == 0) {
		printf("wrong enter\n");
		return 1;
	}
	n = AddPoint(tbl, indx, x, y);
	if (n == 2) 
		printf("doublename\n");
	if (n == 1)
		printf("table is full\n");
	if (n == 2)
		printf("OK\n");
	return 0;
}
int AddPoint(Table *tbl, int indx, int x, int y) {
	int i;
	if (tbl->n >= SIZE)
		return 1;
	for (i = 0; i < tbl->n; ++i)
		if (tbl->point[i].indx == indx)
			return 2;
	tbl->point[tbl->n].indx = indx;
	tbl->point[tbl->n].x = x;
	tbl->point[tbl->n].y = y;
	++tbl->n;
	return 0;
}
int DAddReb(Table *tbl) {
	int indx1, indx2,weight;
	printf("Enter name1\n");
	if (getInt(&indx1) == 0) {
		printf("wrong enter\n");
		return 1;
	}
	printf("Enter name2\n");
	if (getInt(&indx2) == 0) {
		printf("wrong enter\n");
		return 1;
	}
	if (AddReb(tbl, indx1, indx2) == 1)
		printf("Rebro doesn't exist\n");
	else printf("OK\n");
	return 0;
}
int AddReb(Table *tbl,int indx1,int indx2) {
	int i1 = FindPoint(tbl, indx1);
	int i2 = FindPoint(tbl, indx2);
	if (i1 == -1)
		return 1;
	if (i2 == -1)
		return 1;
	double x1 = tbl->point[i1].x;
	double x2 = tbl->point[i2].x;
	double y1 = tbl->point[i1].y;
	double y2 = tbl->point[i2].y;
	double weight = sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));
     tbl->point[i1].list;
	Item *elem1 = (Item *)calloc(1, sizeof(Item));
	elem1->indx = i2;
	elem1->weight = weight;
	elem1->next = tbl->point[i1].list;
	tbl->point[i1].list = elem1;
    /*Item *elem2= (Item *)calloc(1, sizeof(Item));
	elem2->indx = i1;
	elem2->weight = weight;
	elem2->next = tbl->point[i2].list;
	tbl->point[i2].list = elem2;*/
	return 0;
}
int FindPoint(Table *tbl, int indx) {
	int i;
	for (i = 0; i < tbl->n; ++i)
		if (tbl->point[i].indx == indx)
			return i;
	return -1;
}
int DDeletePoint(Table *tbl) {
	int indx;
	printf("enter indx\n");
	if (getInt(&indx) == 0) {
		printf("wrong enter\n");
		return 1;
	}
	if (DeletePoint(tbl, indx) == 1)
		printf("point doesn't exist\n");
	else printf("OK\n");
	return 0;
}
int DeletePoint(Table *tbl,int indx) {
	int i = FindPoint(tbl, indx);
	if (i == -1)
		return 1;
	Item *list = tbl->point[i].list;
	while (list->next != NULL) {
		int i1 = FindPoint(tbl, list->indx);
		Item *list1= tbl->point[i].list;
		DeleteReb(list1, indx);
	}
	for (; i < tbl->n - 1; ++i)
		tbl->point[i] = tbl->point[i + 1];
	--tbl->n;
	return 0;
}
void DeleteReb(Item *list, int indx) {
	while (list->next != NULL) 
		if (list->next->indx == indx) {
			list->next = list->next->next;
			break;
		}
}
int DFindWay(Table *tbl) {
	int indx1, indx2;
	printf("enter name1\n");
	if (getInt(&indx1) == 0) {
		printf("wrong enter\n");
		return 1;
	}
	printf("enter name2\n");
	if (getInt(&indx2) == 0) {
		printf("wrong enter\n");
		return 1;
	}
	int i1 = FindPoint(tbl, indx1);
	int i2 = FindPoint(tbl, indx2);
	if (i1 == -1 || i2 == -1) {
		printf("point doesn't find\n");
		return 0;
	}
	double way = Dijkstra(tbl, i1, i2);
	printf("Way:%f\n", way);
	return 0;
}
double Dijkstra(Table *tbl,int i1,int i2) {
	int i;
	int Q[1000],S[1000];
	for (i = 0; i < tbl->n; ++i) {
		tbl->point[i].d =10000;
		tbl->point[i].pred = NULL;
	}
	tbl->point[i1].d = 0;
	
	for (i = 0; i < tbl->n; ++i) {
		Q[i] = i;
		S[i] = 0;
	}
	Q[i1] = 0;
	Q[0] = i1;
	int kolQ = tbl->n;
	i = 0;
	while (kolQ > 0) {
		int u = ExtractMin(tbl, Q, &kolQ);
		S[i] = u;
		i++;
		Item* list = tbl->point[u].list;
		while (list != NULL) {
			int index = list->indx;
			double weight = list->weight;
			if (tbl->point[index].d > tbl->point[u].d + weight) {
				tbl->point[index].d = tbl->point[u].d + weight;
				tbl->point[index].pred =&tbl->point[u];
				RemoveNum1(tbl,Q, &kolQ, index);
			}
			list = list->next;
		}
	}
	return tbl->point[i2].d;
}
int ExtractMin(Table* tbl,int* Q,int* kolQ) {
	int res = Q[0];
	Q[0] = Q[*kolQ - 1];
	--*kolQ;
	RemoveNum(tbl,Q,kolQ);
	return res;
}
void RemoveNum(Table *tbl,int* Q, int* kolQ) {
	int t=1;
	int i = 0,m1;
	int nomL = Q[2*i+1];
	int nomR = Q[2*i+2];
	int nom = Q[i];
	while (t&&(i<*kolQ)) {
		t = 0;
		m1 = i;
		if (2 * i + 1 < *kolQ)
			m1 = min(tbl, nom, nomL);
		if(2*i+2<*kolQ)
			m1 = min(tbl, m1, nomR);
		if (i!=m1) {
			int b;
			b = Q[2 * i + 1];
			Q[2 * i + 1] = Q[i];
			Q[i] = b;
			i = m1;
			t = 1;
		}
      }
}
int min(Table *tbl, int nom, int nom1) {
	if (tbl->point[nom].d > tbl->point[nom1].d)
		return nom1;
	else
		return nom;
}
void RemoveNum1(Table* tbl,int* Q,int* kolQ,int index ) {
	int i=FindNum(Q,kolQ,index);
	int t = 1;
	int nom = Q[i];
	while (t && (i>0)) {
		t = 0;
		int i1 = i - 1 / 2;
		if (tbl->point[i1].d>tbl->point[i].d) {
			int b;
			b = Q[i1];
			Q[i1] = Q[i];
			Q[i] = b;
			i = i1;
			t = 1;
		}
	}
}
int FindNum(int* Q, int* kolQ, int index) {
	int i;
	for (i = 0; i < *kolQ; ++i)
		if (Q[i] == index)
			break;
	return i;
}
int DShowGraph(Table *tbl) {
	int i;
	if (tbl->n == 0) {
		printf("table is empty\n");
		return 0;
	}
	for (i = 0; i < tbl->n; ++i) {
		printf("\nVertix: %d; another vertixes: ", tbl->point[i].indx);
		Item* list = tbl->point[i].list;
		while (list != NULL) {
			printf(" %d,weight:%f, ", list->indx, list->weight);
			list = list->next;
		}
	}
	return 0;
}

