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
        h->rlink = NULL; //삭제
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
    if (h->llink == NULL) // 공백 리스트의 경우
    {
        printf("List is Empty!!! \n");
        return 0;
    }

    if(h->llink == h->rlink){ // 노드가 1개인 리스트
        free(h->llink);
        h->llink = NULL;
        h->rlink = NULL; // 삭제
        return 0;
    }

    listNode* p = h->rlink;

    p->rlink->llink = h; // 새 첫 노드의 llink는 헤더노드를 가리킴
    h->rlink = p->rlink; // 헤더노드의 rlink는 새 첫 노드를 가리킴
    free(p);

    return 0;
}

int invertList(listNode* h){
    if(h->rlink == NULL || (h->rlink->rlink == h)){ // 공백이거나 노드가 1개인 경우
        printf("List is Empty or has only one node \n");
        return 0;
    }

    listNode* current = h->rlink; // 현재 노드 (반전 실행되는 노드)
    listNode* post = current->rlink; // 다음 노드
    listNode* trail = h; // 이전 노드

    while(current->key != -9999){ //current가 헤드에 도달할 때 까지
        current->llink = current->rlink;
        current->rlink = trail; // 좌 /우 link 반전

        trail = current;
        current = post;
        post = post->rlink; // 노드 포인터들 한칸씩 우로 이동
    }

    current->llink = current->rlink; // 헤드 노드에서도 링크 바꿔줌
    current->rlink = trail;

    return 0;
}

int insertNode(listNode* h, int key){
    listNode* n = createNode(key);

    if(h->llink == NULL){ //공백 리스트
        insertFirst(h, key);
        return 0;
    }

    listNode* p = h->rlink;

    if(n->key <= p->key && n->llink == n->rlink){ //노드가 1개인 리스트의 맨 앞에 삽입하는 경우
        insertFirst(h, key);
        return 0;
    }


    while(p->rlink != h){
        
        if(n->key <= p->key){ // 삽입 위치 발견
            if(p->llink == h){ // 첫번째 위치인 경우
                insertFirst(h, key);
                return 0;
            }

            p->llink->rlink  = n;
            n->llink = p->llink;
            n->rlink = p;
            p->llink = n; // 노드 삽입
            return 0;  
        }

        p = p->rlink; // 다음노드로 링크 이동
    }

    insertLast(h, key); //삽입위치 발견 못함 -> 최댓값 -> 마지막 위치에 삽입
    return 0;
}

int deleteNode(listNode* h, int key){
    if (h->llink == NULL) // 공백 리스트의 경우
    {
        printf("List is Empty!!! \n");
        return 0;
    }

    listNode* p = h->rlink; // 첫 노드부터 탐색

    while(p->key != -9999){

        if(p->key == key){// key값과 같은 노드 발견
            if(p->llink == h){ // p의 llink가 헤드노드를 가리킴 (첫 노드인경우)
                deleteFirst(h);
                return 0;
            }

            if(p->rlink == h){ // p의 rlink가 헤드노드를 가리킴 (마지막 노드인 경우)
                deleteLast(h);
                return 0;
            }

            p->llink->rlink = p->rlink; // 삭제될 노드 다음 노드의 llink 변경
            p->rlink->llink = p->llink; // 삭제될 노드 이전 노드의 rlink 변경
            free(p);                    // 노드 삭제(할당 해제)
            return 0;
        }
        p = p->rlink; // 다음 노드로 링크 이동
    }

    printf("Can't find value %d \n", key); // 삭제하려는 key값의 노드가 존재하지 않음
    return 0;
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
    
    listNode* n = (listNode*)malloc(sizeof(listNode)); // 노드 생성
    n->key = key;
    n->llink = NULL;
    n->rlink = NULL; // 초기화

    return n;
} // key를 key값으로 갖는 노드 생성함수