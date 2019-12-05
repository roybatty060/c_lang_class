#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXWORD 100

struct plist
{
	int id;
	char *item;
	struct plist *next;
};
struct tnode
{
	char *name;
	struct plist *pb;
	struct tnode *left;
	struct tnode *right;
};

char *sItem[] = {"phone", "email", "address", "memo"};

char *strdupl(char *);
void addList(struct plist **pstart, struct plist *pj); //실습 1번
struct tnode *addTree(struct tnode *, struct tnode *); //실습 1번
void treeprint(struct tnode *);
void dispNode(struct tnode *p);						//실습 1번
struct tnode *searchTree(struct tnode *p, char *k); //실습 2번

/* strdup: make a duplicate of a string */
char *strdupl(char *s)
{
	char *p;
	p = (char *)malloc(strlen(s) + 1); // +1 for '\0'
	if (p != NULL)
		strcpy(p, s);
	return p;
}

/* addList: add a list at or next pi in increasing order of id */
void addList(struct plist **pstart, struct plist *pj)
{
	//실습 1번
	//id 오름차순으로 리스트에 pj를 삽입하는 함수,
	//pstart는 리스트 첫 노드의 포인터의 포인터
	struct plist *temp = *pstart;
	if (*pstart == NULL)
		*pstart = pj;
	else if (pj->id > temp->id)
		addList(&(temp->next), pj);
	else
	{
		pj->next = temp;
		*pstart = pj;
	}
}

/* addTree: add a node at or below p
print error message if there is same name */
struct tnode *addTree(struct tnode *p, struct tnode *r)
{
	//실습 1번
	//트리에 r을 삽입하는 함수

	//처음 이 함수가 호출되었을 때, p는 트리의 루트를 의미함.

	//p==NULL일 경우, p에 r을 대입 후 p를 반환
	// strcmp를 활용하여 p와 r의 name 아스키값을 비교,
	//이스키 값이 p==r라면, 이미 트리에 같은 name이 저장되있음을 의미 -> error 출력
	//p>r라면 r은 p의 왼쪽자손, p<r이라면 r은 p의 오른쪽 자손이 됨을 의미함.
	//p의 값(해당 함수의 첫 번째 인자)을 바꿔가며 해당 함수를 재귀적으로 호출하고,
	//최종적으로 트리의 리프에 r 삽입
	if (p == NULL)
		p = r;
	else
	{
		int ret = strcmp(p->name, r->name);
		if (ret < 0)
			p->right = addTree(p->right, r);
		else if (ret == 0)
			printf("error\n");
		else
			p->left = addTree(p->left, r);
	}
	return p;
}
/* treeprint: in-order print of tree p */
void treePrint(struct tnode *p)
{
	if (p != NULL)
	{
		treePrint(p->left);
		dispNode(p);
		treePrint(p->right);
	}
}
/*dispNode: display a node including list*/
void dispNode(struct tnode *p)
{
	//실습 1번
	//p의 name과 pb의 모든 정보를 출력하는 함
	//p가 NULL일 경우 “error” 출력.
	/*출력 예시
	name: aa phone: 010 7297 1180 memo: this is memo
	p의 이름 출력 후, 리스트의 정보를 출력한다.(빈 리스트일 경우, 이름까지만 출력)
	*/
	if (p == NULL)
		printf("error\n");
	else
	{
		printf("name: %s", p->name);
		struct plist *temp = p->pb;
		for (int i = 0; i < 4; i++)
		{
			if (temp == NULL)
				break;
			printf(" %s: %s", sItem[temp->id - 1], temp->item);
			temp = temp->next;
		}
		printf("\n");
	}
}
/* searchTree: search tree with key by non-recursion
return tnode pointer matched or NULL if not found */
struct tnode *searchTree(struct tnode *p, char *k)
{
	// 실습 2번
	// p는 트리의 루트, 트리에서 name이 k인 노드를 찾아 리턴하는 함수,
	// 트리에 name이 k인 노드가 없다면 NULL 리턴
	// 재귀호출이 아닌 반복문 사용할 것.
	int ret;
	struct tnode *temp = p;
	while (temp != NULL)
	{
		ret = strcmp(temp->name, k);
		if (ret < 0)
			temp = temp->right;
		else if (ret == 0)
			return temp;
		else
			temp = temp->left;
	}
	return NULL;
}
int main()
{
	struct tnode *root = NULL;
	while (1)
	{
		int menu;
		printf("(0)exit (1)add (2)print (3)search\n");
		scanf("%d", &menu);
		if (menu == 0)
		{
			break;
		}
		else if (menu == 1)
		{

			char name[MAXWORD];
			scanf("%s", name);

			struct tnode *temp = (struct tnode *)malloc(sizeof(struct tnode));
			temp->name = strdupl(name);
			temp->pb = NULL;
			temp->left = NULL;
			temp->right = NULL;

			struct plist **start = &(temp->pb);

			while (1)
			{
				int type;
				printf("(0)exit (1)phone (2)email (3)address (4)memo \n");
				scanf("%d", &type);
				if (type == 0)
				{
					break;
				}
				else if (type <= 4)
				{
					char content[MAXWORD];
					scanf(" %[^\n]", content);
					// %앞에 꼭 한 칸 뛰어야 정상 작동

					struct plist *tlist = (struct plist *)malloc(sizeof(struct plist));
					tlist->id = type;
					tlist->item = strdupl(content);
					tlist->next = NULL;

					addList(start, tlist);
				}
			}

			root = addTree(root, temp);
		}
		else if (menu == 2)
		{
			treePrint(root);
		}
		else if (menu == 3)
		{
			char name[MAXWORD];
			scanf("%s", name);
			dispNode(searchTree(root, name));
		}
	}
}