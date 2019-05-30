// test2.cpp: определяет точку входа для консольного приложения.
// 
#include "stdafx.h"
#include <malloc.h>
#include <string.h>
const int SIZE = 100;
char *errors[] = {"OK","Overflow"};
int dialog();
struct Item {
	int key;
	int release;
	char *info;
};
struct Table {
	int n;
	Item tab[SIZE];
};
int DAdd(Table *);
int DFind(Table *);
int DDelete(Table *);
int DShow(Table *);
void init(Table *);
void erase(Table *);
int getInt(int *);
int FindRelease(Table *, int);
char *getStr();
int Find(Table *, int, int );
int Add(Table *, int , char *);
Table *Delete(Table *);
int (*fptr[])(Table *) = { NULL,DAdd,DFind,DDelete,DShow };
int main() {
	int rc;
	Table tbl;
	init(&tbl);
	while (rc = dialog()) {
		if (fptr[rc](&tbl))
			break;
	}
	erase(&tbl);
	return 0;
}
void init(Table *tbl) {
	int i;
	tbl->n = 0;
	for (i = 0; i < SIZE; ++i)
		tbl->tab[i].info = NULL;
}
void erase(Table *tbl) {
	int i;
	tbl->n = 0;
	for (i = 0; i < SIZE; ++i)
		free(tbl->tab[i].info);
}
int dialog() {
	int nom, n,i;
	char *ptr[5] = { "0.Quit","1.Add","2.Find","3.Delete","4.Show" };
	printf("Menu\n");
	for (i=0; i< 5;  ++i)
		printf("%s\n", ptr[i]);
	printf("vvedite nomer deistvie\n");
	if (!(n = getInt(&nom)) || (nom > 4) || (nom < 0)) {
		printf("wrong enter\n");
		return 0;
	}
	else
	return nom;
}
int getInt(int *ptr) {
	int n;
	n = scanf("%d", ptr);
	/*if  (n == 0) {
		//printf("error!\n");
		scanf("%*c");
	}*/
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
int DFind(Table *tbl) {
		int key,release,i,fl,fl1=0;
		char *info = NULL;
		printf("0.key\n");
		printf("1.key and release\n");
		if (getInt(&fl) == 0) {
			printf("wrong enter\n");
			return 1;
		}
		if (fl == 0)
		{
			Table tbl1;
			init(&tbl1);
			printf("Enter key:->");
			if (getInt(&key) == 0)
			{
				printf("wrong enter\n");
				return 1;
			}
			release = FindRelease(tbl, key);
			while ((i = Find(tbl, key,release))>=0) {
				fl1 = 1;
				(&tbl1)->tab[(&tbl1)->n].key = tbl->tab[i].key;
				(&tbl1)->tab[(&tbl1)->n].release = tbl->tab[i].release;
				(&tbl1)->tab[(&tbl1)->n].info=tbl->tab[i].info;
				++(&tbl1)->n;
				--release;
			}
			if (fl1==0)
					printf("Item not found\n");
			else DShow(&tbl1);
		}
		if (fl == 1) {
			printf("Enter key and release:->");
			if (getInt(&key) == 0)
			{
				printf("wrong enter\n");
				return 1;
			}
			if (getInt(&release) == 0)
			{
				printf("wrong enter\n");
				return 1;
			}
			i = Find(tbl, key, release);
			if (i < 0) 
				printf("Item not found\n");
			else printf("key=%d,release=%d,info=%s\n", tbl->tab[i].key, tbl->tab[i].release, tbl->tab[i].info);
		}
		return 0;
}
int Find(Table *tbl, int key, int release) {
	int i;
	for (i = tbl->n; i >= 0; --i) {
		if ((tbl->tab[i].key == key) && (tbl->tab[i].release == release))
			return i;
	}
	return -1;
}
int FindRelease(Table *tbl, int key) {
	int i;
	for (i=(tbl->n)-1;i>=0;--i)
		if (tbl->tab[i].key==key)
			return(tbl->tab[i].release);
	return 0;
}
int DAdd(Table *tbl) {
		int key;
		char *info;
		int i;
		printf("Enter key and info\n");
		if (getInt(&key) == 0)
		{
			printf("wrong enter\n");
			return 1;
		}
		if ((info = getStr()) == NULL)
		{
			printf("wrong enter\n");
			return 1;
		}
		i = Add(tbl, key,info);
		printf("%s\n", errors[i]);
		free(info);
		return i;
}
int Add(Table *tbl, int key, char *info) {
	    int i,release; // = Find(tbl, key);
		release = FindRelease(tbl, key);
		++release;
		//while (++release, (i = Find(tbl, key, release)) >= 0);
		if (tbl->n == SIZE)
			return 1;
		tbl->tab[tbl->n].key = key;
		tbl->tab[tbl->n].release = release;
		tbl->tab[tbl->n].info = _strdup(info);
		tbl->n++;
		return 0;
}
int DDelete(Table *tbl) {
	int i;
	if (tbl->n == 0)
		printf("Table is empty\n");
	else {
		Table *tbl1 = Delete(tbl);
		init(tbl);
		tbl->n = tbl1->n;
		for (i = 0; i < tbl1->n; ++i) {
			tbl->tab[i].key = tbl1->tab[i].key;
			tbl->tab[i].release = tbl1->tab[i].release;
			tbl->tab[i].info = tbl1->tab[i].info;
		}
		printf("OK\n");
	}
	return 0;
 }
Table *Delete(Table *tbl) {
	Table tbl1;
	int i;
	init(&tbl1);
	for (i = 0; i < tbl->n; ++i) {
		if (Find(tbl, tbl->tab[i].key, (tbl->tab[i].release + 1)) < 0) {
			(&tbl1)->tab[(&tbl1)->n].key = tbl->tab[i].key;
			(&tbl1)->tab[(&tbl1)->n].release = tbl->tab[i].release;
			(&tbl1)->tab[(&tbl1)->n].info = tbl->tab[i].info;
			(&tbl1)->n++;
		}
	}
	return &tbl1;
}
int DShow(Table *tbl) {
	int i;
	if (tbl->n == 0)
		printf("Table is empty\n");
	else
		for (i=0;i<tbl->n;++i)
			printf("key=%d,release=%d,info=%s\n", tbl->tab[i].key, tbl->tab[i].release, tbl->tab[i].info);
	return 0;
}

	
