#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
const int SIZE = 100;
struct Node {
	int n;
	int key[3];
	char *info[3];
	Node *ptr[4];
	Node *parent;
};
int dialog();
int getInt(int *);
char *getStr();
int DFind(Node **);
Node *Find(Node *, int, int *);
int DAdd(Node **);
int Add(Node **, int, char *);
void TreeSplit(Node *, int);
void removekeys(Node *, int);
void rewritekeys(Node *, Node *, Node *, int);
Node *init(Node *);
int InsertNonfull(Node *, int,char *);
int DDelete(Node **);
int Delete(Node *, int);
Node *ObrRoot(Node *);
void DeleteNode(Node *);
int FindKey(Node *, int);
Node *Situation1(Node *, int);
Node *RemoveKeys1(Node *, Node *, Node *, int);
Node *RemoveKeys2(Node *, Node *, Node *, int);
Node *Situation2(Node *, int,int *);
Node *RemoveKeys3(Node *, Node *, int,int *);
Node *RemoveKeys4(Node *, Node *, int,int *);
int DShowElem(Node **);
int DShowTable(Node **);
void PutTree(Node *x, int lvl);
int timing(Node **);
void generate(Node **, int);
void FindElem(Node *, int);
int(*fptr[])(Node **) = { NULL,DAdd,DFind,DDelete,DShowTable,DShowElem,timing};

int main() {
	srand(time(NULL));
	int rc;
	Node *root =(Node *)malloc(sizeof Node);
	root = init(root);
	while (rc = dialog()) {
		if (fptr[rc](&root))
			break;
	}
	return 0;
}
int dialog() {
	int nom, n, i;
	char *ptr[7] = { "0.Quit","1.Add","2.Find","3.Delete","4.ShowTable","5.ShowElem" ,"6.Timing"};
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
int DFind(Node **proot) {
	int key;
	int i;
	char *info;
	printf("enter key\n");
	if (getInt(&key) == 0) {
		printf("wrong enter\n");
		return 1;
	}
	*proot = Find(*proot, key,&i);
	if (*proot == NULL)
		printf("key not found\n");
	else printf("key=%d,info=%s\n",(*proot)->key[i], (*proot)->info[i]);
	return 0;
}
Node *Find(Node *pr, int k,int *i) {
	while (pr!=NULL) {
		for (*i = 0; *i < pr->n && k > pr->key[*i]; ++*i);
		if (*i!=4&&k == pr->key[*i])
			return pr;
		else pr = pr->ptr[*i];
	}
	return NULL;
}
int DAdd(Node **proot) {
	int key;
	int i;
	char *info,*info1;
	printf("enter key and info\n");
	if (getInt(&key) == 0) {
		printf("wrong enter\n");
		return 1;
	}
	if ((info = getStr()) == NULL)
	{
		printf("wrong enter\n");
		return 1;
	}
	if (Add(proot, key, info) == 1) {
		printf("doublekey\n");
		return 1;
	}
	else {
		printf("OK\n");
		return 0;
	}
}
int Add(Node **pr, int key, char *info) {
	Node *r = *pr;
	if (r->n == 3) {
		Node *s = (Node*)malloc(sizeof Node);
		s = init(s);
		s->n = 0;
		s->ptr[0] = r;
		*pr = s;
		TreeSplit(s, 0);
		r = s;
   }
	if (InsertNonfull(r, key,info) == 1)
		return 1;
	else return 0;
}
void TreeSplit(Node *x, int i) {
	Node *z=(Node *)malloc(sizeof Node);
	Node *y = x->ptr[i];
	removekeys(x, i);//переставление ключей в родительском узле
	z=init(z);//создание пустого узла
	rewritekeys(x, y, z,i);//перезапись значений из разбиваемого узла в пустой узел и род. дерево
}
void removekeys(Node *x,int i) {
	int i1;
	for (i1 = x->n-1; i1>=i; --i1) {
		x->key[i1 + 1] = x->key[i1];
		x->ptr[i1 + 2] = x->ptr[i1 + 1];
	}
	++x->n;
}
void rewritekeys(Node *x, Node *y, Node *z,int i) {
	z->key[0] = y->key[2];//запись в пустой узел 
	z->info[0] = y->info[2];//
	z->ptr[0] = y->ptr[2];//
	z->ptr[1] = y->ptr[3];//
	x->key[i] = y->key[1];//запись в родительский узел
	x->info[i] = y->info[1];//
	x->ptr[i + 1] = z;//
	y->key[1] = 0;//освобождение ключей разбиваемом узле
	y->info[1] = NULL;//
	y->ptr[2] = NULL;//
	y->key[2] = 0;//
	y->info[2] = NULL;//
	y->ptr[3] = NULL;//
	y->n = 1;
	z->n = 1;
}
Node *init(Node *z) {
	int i;
	z->n = 0;
	for (i = 0; i < 3; ++i)
	{
		z->key[i] = 0;
		z->info[i] = NULL;
	}
	for (i = 0; i < 4; ++i)
		z->ptr[i] = NULL;
	return z;
}
int InsertNonfull(Node *x, int k,char* info) {
	int i,i1;
	while (x->ptr[0] != NULL) {
		for (i = 0; i < x->n && k> x->key[i]; ++i);
		if ((i<x->n)&&(k == x->key[i])) 
			return 1;
		if (x->ptr[i] == NULL) {
			x->ptr[i] = (Node *)malloc(sizeof Node);
			x->ptr[i] = init(x->ptr[i]);
		}
		Node* s = x->ptr[i];
		if (s->n == 3) {
			TreeSplit(x, i);
			if (k > x->key[i])
				s = x->ptr[i + 1];
		}
		s->parent = x;
		x = s;
	}
	for (i = 0; i < x->n && k>x->key[i]; ++i)
		;
	//printf("%d\n", i);
	if (k == x->key[i])
		return 1;
	/*if (i == x->n)
	{
		x->key[i] = k;
		x->info[i] = info;
		x->n++;
		return 0;
	}
	else*/
	for (i1=x->n-1; i1>=i ; --i1) {
		x->key[i1+1] = x->key[i1];
		x->info[i1+1] = x->info[i1];
	}
	x->key[i] = k;
	x->info[i] = info;
	++x->n;
	return 0;
}
int DDelete(Node **proot) {
	int key;
	printf("enter key\n");
	if (getInt(&key) == 0) {
		printf("wrong enter\n");
		return 1;
	}
	if (Delete(*proot, key) == 1) {
		printf("key not find\n");
		return 0;
	}
	else {
		printf("OK\n");
			return 0;
	}
}
 int Delete(Node *x, int key) {
	int i;
	x = ObrRoot(x);
	while (x->ptr[0] != NULL) {
		i = FindKey(x,key);
		if (i==x->n||x->key[i] != key)
			x = Situation1(x,i);
		else
			x = Situation2(x,i,&key);
	}
	printf("%d\n", key);
	i = FindKey(x,key);
	if (i == 3 || key != x->key[i])
		return 1;
	else {
		for (; i < x->n - 1; ++i) {
			x->key[i] = x->key[i + 1];
			x->info[i] = x->info[i + 1];
		}
		x->key[x->n-1] = 0;
		x->info[x->n-1]=NULL;
		--x->n;
		return 0;
	}
}
Node *ObrRoot(Node *x) {
	if (x->n == 1&&x->ptr[0]->n==1&&x->ptr[1]->n==1) {
		Node *y = x->ptr[0];
		Node *z = x->ptr[1];
		y->key[1] = x->key[0];//запись из х
		y->info[1] = x->info[0];//
		y->key[2] = z->key[0];//запись из z
		y->info[2] = z->info[0];//
		y->ptr[2] = z->ptr[0];//
		y->ptr[3] = z->ptr[1];//
		y->n = 3;
		//DeleteNode(x);
		DeleteNode(z);
		x = y;
	}
	return x;
}
void DeleteNode(Node *node) {
	int i;
	for (i = 0; i < node->n; ++i) {
		node->key[i] = 0;
		free(node->info[i]);
		node->ptr[i] = NULL;
	}
	node->ptr[i] = NULL;
	node->n = 0;
}
int FindKey(Node *x,int key) {
	int i;
	for (i = 0; i<x->n && key>x->key[i]; ++i);
	return i;
}
Node *Situation1(Node *x,int i) {
	if (i == x->n) {
		Node *y = x->ptr[x->n];
		Node *z = x->ptr[x->n-1];
		if (y->n == 1 && z->n > 1)
			y = RemoveKeys1(x, y, z, i);
		else
			if (y->n == 1 && z->n == 1)
				y = RemoveKeys2(x, y, z, i);
		x = y;
		return x;
	}
	if (i!=x->n) {
		Node *y = x->ptr[i];
		Node *z = x->ptr[i+1];
		if (y->n == 1 && z->n > 1)
			y = RemoveKeys1(x, y, z, i);
		else
			if (y->n == 1 && z->n == 1)
				y = RemoveKeys2(x, y, z, i);					
		x = y;
		return x;
	}
}
Node *RemoveKeys1(Node *x, Node *y, Node *z,int indx) {
	int i;
	y->key[1] = x->key[indx];//запись из х в у
	y->info[1] = x->info[indx];//
	x->key[indx] = z->key[0];//запись из z в х
	x->info[indx] = z->info[0];//
	y->ptr[2] = z->ptr[0];//перестановка ключей z
	y->n = 2;
	for (i = 0; i < z->n-1; ++i) {//
		z->key[i] = z->key[i + 1];//
		z->info[i] = z->info[i + 1];//
		z->ptr[i+1] = z->ptr[i + 2];//
	}
	z->ptr[i] = z->ptr[i + 1];//
	z->key[i + 1] = 0;
	z->info[i + 1] = NULL;
	z->ptr[i + 2] = NULL;
	--z->n;
	return y;
}
Node *RemoveKeys2(Node *x, Node *y, Node *z, int indx) {
	int i;
	y->key[1] = x->key[indx];//работа с х
	y->info[1] = x->info[indx];//
	for (i = indx; i < x->n-1; ++i) {//
		x->key[i] = x->key[i + 1];//
		x->info[i] = x->info[i + 1];//
		x->ptr[i+1] = x->ptr[i + 2];//
		//--x->n;
	}
	x->ptr[i] = x->ptr[i + 1];//
	--x->n;
	y->key[2] = z->key[0];//работа с z
	y->info[2] = z->info[0];//
	y->ptr[2] = z->ptr[0];//
	y->ptr[3] = z->ptr[1];//
	DeleteNode(z);//
	y->n = 3;
	return y;
}
Node *Situation2(Node *x, int indx,int *key) {
	Node *y = x->ptr[indx];
	Node *z = x->ptr[indx + 1];
	//int key = x->key[indx];
	if (y->n >= 2) {
		y = RemoveKeys3(x, y, indx,key);
		x = y;
		return x;
	}
	else
		if (z->n >= 2) {
			z = RemoveKeys4(x, z, indx,key);
			x = z;
			return x;
		}
		else {
			y = RemoveKeys2(x, y, z, indx);
			//if (Delete(y, *key) == 0);
			int i;
			y = ObrRoot(y);
			while (y->ptr[0] != NULL) {
				i = FindKey(y, *key);
				if (i == y->n || y->key[i] != *key)
					y = Situation1(y, i);
				else
					y = Situation2(y, i, key);
			}
			x = y;
			return x;
		}
}
Node *RemoveKeys3(Node *x, Node *y, int indx,int *key) {
	Node *right = y;
	while (right->ptr[right->n] != NULL) {
		right = right->ptr[right->n];
	}
	x->key[indx] = right->key[right->n-1];
	x->info[indx] = right->info[right->n-1];
	//if (Delete(y, right->key[right->n-1]) == 0);
	*key = right->key[right->n - 1];
	int i;
	y = ObrRoot(y);
	while (y->ptr[0] != NULL) {
		i = FindKey(y, *key);
		if (i == y->n || y->key[i] != *key)
			y = Situation1(y, i);
		else
			y = Situation2(y, i,key);
	}

	return y;
}
Node *RemoveKeys4(Node *x, Node *z, int indx,int *key) {
	Node *left = z;
	while (left->ptr[0] != NULL) {
		left = left->ptr[0];
	}
	x->key[indx] = left->key[0];
	x->info[indx] = left->info[0];
	//if (Delete(z, left->key[0]) == 0);
	*key = left->key[0];
	int i;
	z = ObrRoot(z);
	while (z->ptr[0] != NULL) {
		i = FindKey(z, *key);
		if (i == z->n || z->key[i] != *key)
			z = Situation1(z, i);
		else
			z = Situation2(z, i,key);
	}
	return z;
}
int DShowTable(Node **proot) {
	if (*proot == NULL) {
		printf("Tree is free\n");
		return 1;
	}
	PutTree(*proot, 0);
	return 0;
}
void PutTree(Node *x, int lvl) {
	int i, j;
	if (x&&x->n) {
		PutTree(x->ptr[x->n], lvl+1);
		for (i = x->n - 1; i >= 0; --i) {
			for (j = 0; j < lvl; ++j)
				printf("   ");
			printf("%d\n",x->key[i]);
			PutTree(x->ptr[i], lvl+1);
		}
	}
}
int DShowElem(Node **proot) {
	int key;
	int i;
	printf("Enter key\n");
	if (getInt(&key) == 0) {
		printf("wrong enter\n");
		return 1;
	}
	*proot = Find(*proot, key, &i);
	if (*proot == NULL) {
		printf("Element not find\n");
		return 0;
	}
	if ((*proot)->ptr[i + 1] != NULL) {
		Node *left = (*proot)->ptr[i + 1];
		while (left->ptr[0] != NULL) {
			left = left->ptr[0];
		}
		printf("key=%d,info=%s\n", left->key[0], left->info[0]);
		return 0;
	}
	if (i==(*proot)->n-1) {
		printf("Element not find\n");
		return 0;
	}
	else {
		printf("key=%d,info=%s\n", (*proot)->key[i+1], (*proot)->info[i+1]);
		return 0;
	}

}
int timing(Node **pptr) {
	int t0,t1,i;
	int n = 1;
	int cnt = 10;
	int key[100];
	for (i = 0; i < 100; ++i)
		key[i] = rand();
	while (cnt-- > 0) {
		generate(pptr, n);
		t0 = clock();
		for (i = 0; i < 100; ++i)
			FindElem(*pptr, key[i]);
		t1 = clock();
		printf("%d nodes, time = %d\n", n, t1 - t0);
		n *= 10;
	}
	return 0;
}
void generate(Node **pptr, int n) {
	int i = 0, k;
	while (i < n) {
		k = rand();
		if (Add(pptr, k, NULL))
			++i;
	}
}
void FindElem(Node *pr, int k) {
	int i;
	while (pr != NULL) {
		for (i = 0; i < pr->n && k > pr->key[i]; ++i);
		if ( k == pr->key[i]);
		else pr = pr->ptr[i];
	}
}

