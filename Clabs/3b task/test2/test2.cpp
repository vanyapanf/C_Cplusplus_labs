// test2.cpp: определяет точку входа для консольного приложения.
//
#include "stdafx.h"
#include <malloc.h>

struct Item {
	char c;
	Item *next;
};

int getList(Item **);
void delList(Item *);
void printList(Item *);
Item *work(Item *);
Item *delSpace(Item *);
Item *delSimv(Item *,char);
int main()
{
	Item *src = NULL, *res = NULL;
	//res = NULL;
	while (puts("Enter"), getList(&src)) {//выводим Еnter ,  считываем строку с помощью функции , получаем адрес нач. эл -та
		printf("%s\n", "Source:");
		printList(src);//выводим начальную строку
		res = work(src);//получаем адрес нач. эл-та преобразованной строки
		printf("%s\n", "Result:");
		printList(res);//выводим результат
		delList(res);
	}
	return 0;
}
int getList(Item **pptr)
{
	char buf[81], *str;
	Item head = { '*', NULL };
	Item *last = &head;
	int n, r = 0;
	do {
		n = scanf("%80[^\n]", buf);
		if (n < 0) {
			delList(head.next);
			head.next = NULL;
			r = 0;
			continue;
		}
		r = 1;
		if (n > 0) {
			for (str = buf; *str; str++) {
				last->next = (Item*)malloc(sizeof(Item));
				last = last->next;
				last->c = *str;
			}
			last->next = NULL;
		}
		else scanf_s("%*c");
	} while (n > 0);
	*pptr = head.next;
	return r;
}
Item *work(Item *ptr)
{
	Item head = {'*',ptr};
	Item *src1 = &head;
	Item *src2 = NULL;
	int fl = 0,fl1 = 0;
	char simv;
	while ((src1->next=delSpace(src1->next)) &&src1){
        if( fl==0){
			simv = src1->next->c;
			fl = 1; 
		} 
		if (src1->next->c == simv && fl1==1) 
			src1->next = delSimv(src1->next,simv);
		fl1 = 1;
		if (src1->next!=NULL)
		do {
			src2 = src1;
			src1 = src1->next;
			if (src1->next != NULL)
			{
				if (src1->next->c == simv)
					src1->next = delSimv(src1->next, simv);
			}
		} while (src1->c != ' '&&src1->c!='\t'&&src1->next != NULL);
		if (src1->c == '\t')
			src1->c = ' ';
	}
	if (src2!=NULL)
	if (src2->next->c == ' ' || src2->next->c == '\t') {
		free(src2->next);
		src2->next = NULL;
	}
		return head.next;
}
Item *delSpace(Item *ptr) {
	if (ptr != NULL) {
		while (ptr&&ptr->next!=NULL&&(ptr->c == ' ' || ptr->c == '\t')) {
			Item *tmp = ptr;
			ptr = ptr->next;
			free(tmp);
		}
		if (ptr->c == ' ' || ptr->c == '\t')
			ptr = NULL;
       }
	return ptr;
}
Item *delSimv(Item *ptr,char ch) {
	while (ptr&&ptr->c == ch ) {
		Item *tmp = ptr;
		ptr = ptr->next;
		free(tmp);
	}
	return ptr;
}
void delList(Item *p) {
	Item *tmp = NULL;
	while (p) {
		tmp = p;
		p = p->next;
		free(tmp);
	}
}
void printList(Item *ptr)
{
	printf("\"");
	if (ptr !=NULL)
	do {
		printf("%c", (ptr->c));
		ptr = ptr->next;
	} while (ptr != NULL);
	printf("\"");
	printf("\n");
}
