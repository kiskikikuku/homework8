#include<stdio.h>
#include<stdlib.h>

typedef struct Node
{
    int key;
    struct Node* llink;
    struct Node* rlink;
}listNode;

int initialize(listNode** h);
int freeList(listNode* h);
int insertLast(listNode* h, int key);
int deleteLast(listNode*h);
int insertFirst(listNode* h, int key);
int deleteFirst(listNode* h);
int invertList(listNode* h);

int insertNode(listNode* h, int key);
int deleteNode(listNode* h, int key);

void printList(listNode* h);

listNode* createNode(int key);

int main(){

    char command;
    int key;
    listNode* headNode = NULL;

    do{
        printf("---------------[2018068040]-------[Park Taehyun]----------------\n");
        printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

        printf("Command = ");
        scanf(" %c", &command);

        switch(command)
        {
        case 'z': case 'Z':
            initialize(&headNode);
            break;
        case 'p': case'P':
            printList(headNode);
            break;
        case 'i': case'I':
            printf("Key = ");
            scanf(" %d", &key);
            insertNode(headNode, key);
            break;
        case 'd': case'D':
            printf("Key = ");
            scanf(" %d", &key);
            deleteNode(headNode, key);
            break;
        case 'n': case'N':
            printf("Key = ");
            scanf(" %d", &key);
            insertLast(headNode, key);
            break;
        case 'e': case'E':
            deleteLast(headNode);
            break;
        case 'f': case'F':
            printf("Key = ");
            scanf(" %d", &key);
            insertFirst(headNode, key);
            break;
        case 't': case'T':
            deleteFirst(headNode);
            break;
        case 'r': case 'R':
            invertList(headNode);
            break;
        case 'q': case'Q':
            freeList(headNode);
            break;
        default:
            printf("\n       >>>>>   Concentration!!   <<<<<     \n");
            break;
        }

    }while(command != 'q'&& command != 'Q');

    return 1;
}

int initialize(listNode** h){

    if(*h != NULL) //비어있지 않으면
        freeList(*h); // 할당 해제

    *h = (listNode*)malloc(sizeof(listNode));
    (*h)->llink = NULL;
    (*h)->rlink = NULL;
    (*h)->key = -9999; // 새 공간 할당 후 초기화 진행
    return 1;
}

int freeList(listNode *h){
    if(h == NULL){
        printf("Empty List !!!\n");
        return 0;
    }

    listNode* p = h->llink;

    while(p->key != -9999){
        p = p->rlink;
        free(p->llink); // 헤드까지 p가 이동하며 이전 노드를 해제
    }

    free(h); // 현재 p는 헤드를 가리킴

    return 0;
}

int insertLast(listNode* h, int key){
    listNode* p = createNode(key);

     if(h->llink==NULL){ //공백 리스트의 경우
        h->llink = h->rlink = p; // 처음이자 마지막 노드이므로, 헤더의 두 링크가 모두 가리킴
        p->llink = p->rlink = h; // 처음이자 마지막 노드이므로, 노드의 링크는 모두 헤더를 가리킴
        return 0;
    }
    
    p->llink = h->llink; // 삽입될 노드의 llink는 기존 마지막 노드를 가리킴
    h->llink->rlink = p; // 기존 마지막 노드의 rlink는 삽입될 노드를 가리킴
    p->rlink = h;        // 삽입될 노드의 rlink는 헤더노드를 가리킴
    h->llink = p;        // 헤더노드의 llink는 삽입될 노드를 가리킴

    return 0;
}

int deleteLast(listNode*h){
    if (h->llink == NULL) // 공백 리스트의 경우
    {
        printf("List is Empty!!! \n");
        return 0;
    }

    if(h->llink == h->rlink){ // 노드가 1개인 리스트
        free(h->llink);
        h->llink = NULL;
        h->rlink = NULL;
        return 0;
    }

    listNode* p = h->rlink;

    while(p->rlink != h){ //p가 마지막 노드를 가리킬 때 까지 이동
        p = p->rlink;
    }

    p->llink->rlink = h; //삭제될 노드의 이전 노드가 헤드를 가리킴(새 마지막 노드)
    h->llink = p->llink; // 헤드노드의 llink가 새 마지막 노드를 가리킴
    free(p);

    return 0;
}

int insertFirst(listNode* h, int key){
    listNode* p = createNode(key);

    if(h->llink==NULL){ //공백 리스트의 경우
        h->llink = h->rlink = p; // 처음이자 마지막 노드이므로, 헤더의 두 링크가 모두 가리킴
        p->llink = p->rlink = h; // 처음이자 마지막 노드이므로, 노드의 링크는 모두 헤더를 가리킴
        return 0;
    }

    h->rlink->llink = p; // 기존의 첫 노드의 llink가 삽입될 노드를 가리킴
    p->rlink = h->rlink; // p의 rlink는 기존의 첫노드를 가리킴
    h->rlink = p; // 첫 노드로 삽입, 헤더노드의 rlink가 가리킴
    p->llink = h; // 첫 노드의 llink는 헤더노드를 가리킴

    return 0;
}

int deleteFirst(listNode* h){

}

int invertList(listNode* h){

}

int insertNode(listNode* h, int key){

}

int deleteNode(listNode* h, int key){

}

void printList(listNode* h){
    int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink;

	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}
	printf("  items = %d\n", i);


	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

	i = 0;
	p = h->rlink;
	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink;
		i++;
	}
}

listNode* createNode(int key){
    
    listNode* n = (listNode*)malloc(sizeof(listNode));
    n->key = key;
    n->llink = NULL;
    n->rlink = NULL;

    return n;
}