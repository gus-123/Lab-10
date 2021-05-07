/*
 * Binary Search Tree #2
 *
 * Data Structures
 *
 * Department of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>


//트리의 노드 구조를 구조체로 정의
typedef struct node {
	int key;
	struct node *left;  //왼쪽 노드
	struct node *right;  //오른쪽 노드
} Node;

//스택을 위한 요소
#define MAX_STACK_SIZE		20  //스택의 최대 사이즈
Node* stack[MAX_STACK_SIZE];
int top = -1;

Node* pop();
void push(Node* aNode);

//큐를 위한 요소
#define MAX_QUEUE_SIZE		20  //큐의 최대 사이즈
Node* queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;

Node* deQueue();
void enQueue(Node* aNode);


int initializeBST(Node** h);

//함수 리스트
void recursiveInorder(Node* ptr);	  //중위 순회 재귀 연산
void iterativeInorder(Node* ptr);     //중위 순회 반복 연산
void levelOrder(Node* ptr);	          //레벨 순서 순회 연산
int insert(Node* head, int key);      //트리의 key값 삭제 연산
int deleteNode(Node* head, int key);  //트리의 key값 삭제 연산
int freeBST(Node* head); //트리의 메모리 해제 연산




void printStack() {

}



int main()
{
	char command;
    printf("[----- [김현민]  [2018038088] -----]");
	int key;
	Node* head = NULL;

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #2                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(head, key);
			break;

		case 'r': case 'R':
			recursiveInorder(head->left);
			break;
		case 't': case 'T':
			iterativeInorder(head->left);
			break;

		case 'l': case 'L':
			levelOrder(head->left);
			break;

		case 'p': case 'P':
			printStack();
			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	//트리가 null이 아닌 경우 트리에 삽입된 모든 노드를 삭제
	if(*h != NULL)
		freeBST(*h);

	//head를 생성
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	//루트
	(*h)->right = *h;
	(*h)->key = -9999;

	top = -1;

	front = rear = -1;

	return 1;
}



void recursiveInorder(Node* ptr)
{
	if(ptr) {
		recursiveInorder(ptr->left);
		printf(" [%d] ", ptr->key);
		recursiveInorder(ptr->right);
	}
}

/**
 * textbook: p 224s
 */
void iterativeInorder(Node* node) {
    int top = -1;  //스택 초기화
	Node* stack[MAX_STACK_SIZE];  

	for ( ; ; ) {
	    for ( ; node; node = node->left) {
			push(node);  //스택에 삽입
		}
		node = pop();  //스택에서 삭제

		if (!node) {  //공백 스택인 경우
			break;
		}
		printf("[%d]  ", node->key);

		node = node->right;  //node의 right를 node에 저장
	}
}

/**
 * textbook: p 225
 */
void levelOrder(Node* ptr) {
    Node* temp;
    enQueue(ptr);  //ptr을 큐에 삽입

    while (ptr) {  //ptr이 null이 아닌 경우 
        temp = deQueue();  //큐에서 부모 노드의 key값을 삭제하여 temp에 저장
        
        if (temp == NULL) {  //temp가 null인 경우
            break;
        }
        printf("[%d]  ", temp->key);  
        
        if (temp->left) {  //출력한 부모 노드의 왼쪽 자식 노드 key값을 삽입
            enQueue(temp->left);
        }
        if (temp->right) {  //출력한 부모 노드의 오른쪽 자식 노드 key값을 삽입
            enQueue(temp->right);
        }
    }
}


int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;

	if (head->left == NULL) {
		head->left = newNode;
		return 1;
	}

	//head->left가 루트를 나타냄
	Node* ptr = head->left;

	Node* parentNode = NULL;
	while(ptr != NULL) {

		//key값에 대한 노드가 있을 경우
		if(ptr->key == key) return 1;

		//부모 노드를 사용하여 자식 노드의 위치 탐색
		parentNode = ptr;

		//부모 노드의 key값이 추가한 key값보다 큰 경우 새로운 노드를 오른쪽 자식 노드에 삽입, 작을 경우 왼쪽 자식 노드에 삽입
		if(ptr->key < key)
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}

	//새로운 노드를 부모 노드에 연결
	if(parentNode->key > key)
		parentNode->left = newNode;
	else
		parentNode->right = newNode;
	return 1;
}


int deleteNode(Node* head, int key) {
    Node* parent, * p, * succ_parent, * succ; 
	Node* child;

	parent = NULL;  
	p = head->left;

	while ((p != NULL) && (p->key != key)) {  //삭제할 p 노드의 위치 탐색
		parent = p;

		if (key < p->key) {
			p = p->left;
		}
		else {
			p = p->right;
		}
	}

	if (p == NULL) {  //삭제할 p 노드가 null인 경우
		printf("\n 삭제 할 키가 이진트리에 없습니다!");

		return 0;
	}

	//삭제할 p 노드가 단말 노드인 경우
	if ((p->left == NULL) && (p->right == NULL)) {
		if (parent != NULL) {  //부모 노드가 null이 아닌 경우
			if (parent->left == p) {
				parent->left = NULL;
			}
			else {
				parent->right = NULL;
			}
		}
		else {  //부모 노드가 null인 경우
			head = NULL;  
		}  
	}

	//삭제할 p 노드가 자식 노드를 한 개 가진 경우
	else if ((p->left == NULL) || (p->right == NULL)) {
		if (p->left != NULL) {
			child = p->left;
		}
		else {
			child = p->right;
		}

		if (parent != NULL) {  //부모 노드가 null이 아닌 경우
			if (parent->left == p) {
				parent->left = child;
			}
			else {
				parent->right = child;
			}
		}
		else {  //부모 노드가 null이여서 자식 노드가 부모 노드가 되는 경우
			head = child;  
		}
	}

	//삭제할 p 노드가 자식 노드를 두 개 가진 경우
	else {
	    succ_parent = p;
		succ = p->right;

		while (succ->left != NULL) {  //오른쪽 자식 노드에서 가장 작은 값을 찾기
			succ_parent = succ;
			succ = succ->left;
		}

		//자식 노드에 대한 후계 노드의 부모 노드와 자식 노드를 연결
		if (succ_parent->left == succ) {   
			succ_parent->left = succ->right;
		}
		else {  //후계노드의 부모 노드가 null이여서 가장 작은 값을 가진 오른쪽 자식 노드가 부모 노드가 되는 경우
			succ_parent->right = succ->right;  
		}
		p->key = succ->key;
		p = succ;
	}
	free(p);
}


void freeNode(Node* ptr)
{
	if(ptr) {
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	}
}

int freeBST(Node* head)
{

	if(head->left == head)
	{
		free(head);
		return 1;
	}

	Node* p = head->left;

	freeNode(p);

	free(head);
	return 1;
}



Node* pop() {
    Node* aNode = NULL;
    if (top == -1) {  //스택의 top의 위치가 -1인 경우 aNode로 다시 리턴
        return aNode;
    }
    aNode = stack[top];  //스택의 top의 key값을 aNode의 위치에 저장
    top--;  //스택 top의 위치를 가르키는 숫자 값을 감소

    return aNode;
}

void push(Node* aNode) {
    if (top == MAX_STACK_SIZE - 1) {  //스택의 top의 위치를 가르키는 숫자값이 스택의 최대 사이즈-1을 한 숫자 값을 나타낸 경우 다시 리턴
        return;
    }
	++top;  //스택 top의 위치를 가르키는 숫자 값을 증가
    stack[top] = aNode;  //aNode의 key값을 스택의 top의 위치에 저장
}



Node* deQueue() {
    Node* aNode = NULL;

    if (front == rear) {  //front의 위치와 rear의 위치가 같을 경우
        if (front != -1) {  //큐의 front의 위치가 -1이 아닌 경우
            aNode = queue[front];  //큐의 front의 key값을 aNode의 위치에 저장
            front = rear = -1;  //큐 초기화
        }

        return aNode;
    }
    aNode = queue[front];  //큐의 front의 key값을 aNode의 위치에 저장
    front++;  //큐 front의 위치를 가르키는 숫자 값을 증가

    return aNode;
}

void enQueue(Node* aNode) {
    if (rear == MAX_QUEUE_SIZE - 1) {  //큐의 rear의 위치를 가르키는 숫자값이 큐의 최대 사이즈-1을 한 숫자 값을 나타낸 경우 다시 리턴
        return;
    }

    if (front == -1) {  //큐의 front의 위치가 -1인 경우
        front++;  //큐 front의 위치를 가르키는 숫자 값을 증가
    }
    rear++;  //큐 rear의 위치를 가르키는 숫자 값을 증가
    queue[rear] = aNode;  //aNode의 key값을 큐의 rear의 위치에 저장
}





