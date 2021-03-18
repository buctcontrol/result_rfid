#include <stdio.h>

typedef int (*pf)(void* this, int a);

struct S
{
	pf f;
};

struct A
{
	pf f;
	int b;
};

struct B
{
	pf f;
	int c;
};

int fa(void* this, int n)
{
	struct A* a = (struct A*)this;
	return a->b + n;
}

int fb(void* this, int n)
{
	struct B* b = (struct B*)this;
	return b->c * n;
}

int callf(struct S* s, int n)
{
	return s->f(s, n);
}

int main()
{
	struct A a, a1;
	a.b = 100;
	a.f = fa;
	a1 = a; 

	struct B b;
	b.c = 100;
	b.f = fb;

	int m = callf((struct S*)&a, 10);
	printf("result:%d\n", m);

	m = callf((struct S*)&b, 10);
	printf("result:%d\n", m);
	return 0;
}

