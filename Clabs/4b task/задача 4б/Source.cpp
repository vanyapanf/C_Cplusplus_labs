#include <stdio.h>
#include <malloc.h>
#include <string.h>
char *errors[] = { "OK","Overflow" };
int dialog();
struct Item {
	int key;
	int release;
	int offset;
	int len;
};
struct Table {
	int SZ;
	int n;
	Item *tbl;
	FILE *fd;
};
int DLoad(Table *);
int load(Table *, char *);
int create(Table *, char *, int);
int DAdd(Table *);
int insert(Table *, int, char *);
int DFind(Table *);
int DDelete(Table *);
int DShow(Table *);
void erase(Table *);
int getInt(int *);
int FindRelease(Table *, int);
char *getStr();
int Find(Table *, int, int);
int Add(Table *, int, char *);
int DSave(Table *);
Table *Delete(Table *);
int(*fptr[])(Table *) = { NULL,DAdd,DFind,DDelete,DShow };
int main() {
	int rc;
	Table tbl;
	if(DLoad(&tbl)==0)
		return 1;
	while (rc = dialog()) {
		if (fptr[rc](&tbl))
			break;
	}
	DSave(&tbl);
	erase(&tbl);
	return 0;
}
int DLoad(Table *ptab) {
	int SZ;
	char *fname = NULL;
	printf("Enter filename:-> ");
	fname = getStr();
	if (fname == NULL)
		return 0;
	if (load(ptab, fname)==0) {
		printf("Enter possible vector size:-> ");
		if (getInt(&SZ) == 0) 
			return 0;
		create(ptab, fname, SZ);
	}
	free(fname);
	return 1;
}
int load(Table *ptbl, char *fname) {
	fopen_s(&(ptbl->fd),fname, "r+b");
	if (ptbl->fd == NULL)
		return 0;
	fread(&ptbl->SZ, sizeof(int), 1, ptbl->fd);
	fread(&ptbl->n, sizeof(int), 1, ptbl->fd);
	ptbl->tbl = (Item*)calloc(ptbl->SZ, sizeof(Item));
	fread(ptbl->tbl, sizeof(Item), ptbl->n, ptbl->fd);
	return 1;
}
int create(Table *ptbl, char *fname, int sz) {
	ptbl->SZ = sz;
	ptbl->n = 0;
	if (fopen_s(&(ptbl->fd), fname, "w+b") != 0) {
		ptbl->tbl = NULL;
		return 0;
	}
	ptbl->tbl = (Item*)calloc(ptbl->SZ, sizeof(Item));
	fwrite(&ptbl->SZ, sizeof(int), 1, ptbl->fd);
	fwrite(&ptbl->n, sizeof(int), 1, ptbl->fd);
	fwrite(ptbl->tbl, sizeof(Item), ptbl->SZ, ptbl->fd);
	return 1;
}
void erase(Table *tbl) {
	int i;
	tbl->n = 0;
	for (i = 0; i < tbl->SZ; ++i) {
		tbl->tbl[tbl->n].key = 0;
		tbl->tbl[tbl->n].release = 0;
		tbl->tbl[tbl->n].len = 0;
    }
}
int dialog() {
	int nom, n, i;
	char *ptr[5] = { "0.Quit","1.Add","2.Find","3.Delete","4.Show" };
	printf("Menu\n");
	for (i = 0; i< 5; ++i)
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
	n = scanf_s("%d", ptr);
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
			scanf_s("%*c");
		else {
			len += strlen(buf);
			ptr = (char*)realloc(ptr, len + 1);
			strcat(ptr, buf);
		}
	} while (n > 0);
	return ptr;
}
int DFind(Table *tbl) {
	int key, release, i, fl, fl1 = 0;
	char *info = NULL;
	printf("0.key\n");
	printf("1.key and release\n");
	if (getInt(&fl) == 0) {
		printf("wrong enter\n");
		return 1;
	}
	if (fl == 0)
	{
		printf("Enter key:->");
		if (getInt(&key) == 0)
		{
			printf("wrong enter\n");
			return 1;
		}
		release = FindRelease(tbl, key);
		while ((i = Find(tbl, key, release)) >= 0) {
			char *info=NULL;
			fl1 = 1;
			info = (char*)malloc(tbl->tbl[i].len);
			fseek(tbl->fd, tbl->tbl[i].offset, SEEK_SET);
			fread(info, sizeof(char), tbl->tbl[i].len, tbl->fd);
			printf("key=%d,release=%d,info=%s\n", key, release, info);
			--release;
		}
		if (fl1 == 0)
			printf("Item not found\n");
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
		else {
			char *info = NULL;
			info = (char*)malloc(tbl->tbl[i].len);
			fseek(tbl->fd, tbl->tbl[i].offset, SEEK_SET);
			fread(info, sizeof(char), tbl->tbl[i].len, tbl->fd);
			printf("key=%d,release=%d,info=%s\n", key, release, info);
		}
	}
	return 0;
}
int Find(Table *tbl, int key, int release) {
	int i;
	for (i = tbl->n; i >= 0; --i) {
		if ((tbl->tbl[i].key == key) && (tbl->tbl[i].release == release))
			return i;
	}
	return -1;
}
int FindRelease(Table *tbl, int key) {
	int i;
	for (i = (tbl->n) - 1; i >= 0; --i)
		if (tbl->tbl[i].key == key)
			return(tbl->tbl[i].release);
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
	i = insert(tbl, key, info);
	printf("%s\n", errors[i]);
	free(info);
	return i;
}
int insert(Table *tbl, int key, char *info) {
	int release = FindRelease(tbl, key);
	++release;
	if (tbl->n >= tbl->SZ)
		return 1;
	tbl->tbl[tbl->n].key = key;
	tbl->tbl[tbl->n].release = release;
	tbl->tbl[tbl->n].len = strlen(info) + 1;
	fseek(tbl->fd, 0, SEEK_END);
	tbl->tbl[tbl->n].offset = ftell(tbl->fd);
	fwrite(info, sizeof(char), tbl->tbl[tbl->n].len, tbl->fd);
	++(tbl->n);
	return 0;
}
int DDelete(Table *tbl) {
	int i;
	if (tbl->n == 0)
		printf("Table is empty\n");
	else {
		Table *tbl1= Delete(tbl);
		tbl->n = tbl1->n;
		tbl->tbl = tbl1->tbl;
		printf("OK\n");
	}
	return 0;
}
Table *Delete(Table *tbl) {
	Table tbl1;
	int i;
	(&tbl1)->n = 0;
	(&tbl1)->tbl = tbl->tbl;
	(&tbl1)->SZ = tbl->SZ;
	(&tbl1)->fd = tbl->fd;
	for (i = 0; i < tbl->n; ++i) {
		if (Find(tbl, tbl->tbl[i].key, (tbl->tbl[i].release + 1)) < 0) {
			(&tbl1)->tbl[(&tbl1)->n].key = tbl->tbl[i].key;
			(&tbl1)->tbl[(&tbl1)->n].release = tbl->tbl[i].release;
			(&tbl1)->tbl[(&tbl1)->n].offset = tbl->tbl[i].offset;
			(&tbl1)->tbl[(&tbl1)->n].len = tbl->tbl[i].len;
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
		for (i = 0; i < tbl->n; ++i)
		{
			char *info = NULL;
			info = (char*)malloc(tbl->tbl[i].len);
			fseek(tbl->fd, tbl->tbl[i].offset, SEEK_SET);
			fread(info, sizeof(char), tbl->tbl[i].len, tbl->fd);
			printf("key=%d,release=%d,info=%s\n", tbl->tbl[i].key, tbl->tbl[i].release, info);
		}
	return 0;
}
int DSave(Table *ptbl)
{
	fseek(ptbl->fd, sizeof(int), SEEK_SET);
	fwrite(&ptbl->n, sizeof(int), 1, ptbl->fd);
	fwrite(ptbl->tbl, sizeof(Item), ptbl->n, ptbl->fd);
	fclose(ptbl->fd);
	ptbl->fd = NULL;
	return 1;
}