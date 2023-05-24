#include <stdio.h>
/*
 * Binary Search Tree #1
 *
 * Data Structures
 *
 * School of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node { //node 구조체 선언
	int key;          //int형 변수 key 선언, 현재 노드의 값
	struct node *left; //struct형 포인터 변수 node *left 선언, 왼쪽 자식 노드
	struct node *right; //struct형 포인터 변수 node *right 선언, 오른쪽 자식 노드
} Node;

int initializeBST(Node** h); //int형을 반환하는 함수 initializeBST(Node **h) 선언

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


int main()
{
	char command; //char형 변수 command 선언
	int key;      //int형 변수 key 선언
	Node* head = NULL;  //Node *head 선언하고 NULL로 초기화
	Node* ptr = NULL;	//Node *ptr 선언하고 NULL로 초기화, 현재 위치를 가리킴                         /* temp */

    printf("[----- [Kim ah hyeon] [2022041010] -----]\n");


	do{
		printf("\n\n");                                                               //줄바꿈
		printf("----------------------------------------------------------------\n"); //---------------------------------------------------------------- 출력
		printf("                   Binary Search Tree #1                        \n"); //                   Binary Search Tree #1                         출력
		printf("----------------------------------------------------------------\n"); //---------------------------------------------------------------- 출력
		printf(" Initialize BST       = z                                       \n"); // Initialize BST       = z                                        출력
		printf(" Insert Node          = n      Delete Leaf Node             = d \n"); // Insert Node          = n      Delete Leaf Node             = d  출력
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n"); // Inorder Traversal    = i      Search Node Recursively      = s  출력
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f \n"); // Preorder Traversal   = p      Search Node Iteratively      = f  출력
		printf(" Postorder Traversal  = t      Quit                         = q \n"); // Postorder Traversal  = t      Quit                         = q  출력
		printf("----------------------------------------------------------------\n"); //---------------------------------------------------------------- 출력

		printf("Command = ");    //Command =  출력
		scanf(" %c", &command); //문자형 command를 입력받음

		switch(command) { //제어식이 command
		case 'z': case 'Z': //command가 'z'이거나 'Z'이면
			initializeBST(&head); //initializeBST(&head) 함수 호출
			break;               //break문
		case 'q': case 'Q': //command가 'q'이거나 'Q'이면
			freeBST(head); //freeBST(head) 함수 호출
			break;               //break문
		case 'n': case 'N': //command가 'z'이거나 'Z'이면
			printf("Your key = ");   //Your key =  출력
			scanf("%d", &key);      //key 값을 입력받음
			insert(head, key);      //insert(head, key) 함수 호출
			break;               //break문
		case 'd': case 'D': //command가 'z'이거나 'Z'이면
			printf("Your Key = ");   //Your key =  출력
			scanf("%d", &key);      //key 값을 입력받음
			deleteLeafNode(head, key); //deleteLeafNode(head, key) 함수 호출
			break;               //break문
		case 'f': case 'F': //command가 'z'이거나 'Z'이면
			printf("Your Key = ");   //Your key =  출력
			scanf("%d", &key);      //key 값을 입력받음
			ptr = searchIterative(head, key); //ptr에 searchIterative(head, key) 값 대입
			if(ptr != NULL) //ptr이 NULL이 아니면
				printf("\n node [%d] found at %p\n", ptr->key, ptr); // node [%d] found at %p 출력
			else           //ptr이 NULL이라면
				printf("\n Cannot find the node [%d]\n", key); // Cannot find the node  출력
			break;               //break문
		case 's': case 'S': //command가 'z'이거나 'Z'이면
			printf("Your Key = ");   //Your key =  출력
			scanf("%d", &key);      //key 값을 입력받음
			ptr = searchRecursive(head->left, key); //ptr에 searchRecursive(head->left, key) 대입
			if(ptr != NULL) //ptr이 NULL이 아니면
				printf("\n node [%d] found at %p\n", ptr->key, ptr); // node [%d] found at %p 출력
			else           //ptr이 NULL이라면
				printf("\n Cannot find the node [%d]\n", key); // Cannot find the node  출력
			break;               //break문

		case 'i': case 'I': //command가 'z'이거나 'Z'이면
			inorderTraversal(head->left);
			break;               //break문
		case 'p': case 'P': //command가 'z'이거나 'Z'이면
			preorderTraversal(head->left);
			break;               //break문
		case 't': case 'T': //command가 'z'이거나 'Z'이면
			postorderTraversal(head->left);
			break;               //break문
		default:            //위의 경우가 모두 아니라면
			printf("\n       >>>>>   Concentration!!   <<<<<     \n"); //       >>>>>   Concentration!!   <<<<<      출력
			break; //break문
		}

	}while(command != 'q' && command != 'Q'); //command가 'q'가 아니고 'Q'가 아니면 실행

	return 1; //1 값 반환
}

int initializeBST(Node** h) { //int형을 반환하는 initializeBST(Node** h) 함수

	/* if the tree is not empty, then remove all allocated nodes from the tree*/ //트리가 비어있지 않다면, 모든 할당된 노드를 트리에서 제거
	if(*h != NULL) //*h가 NULL이 아니라면
		freeBST(*h); //freeBST(*h) 함수 호출

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node)); //*h에 (Node*)malloc(sizeof(Node)) 대입
	(*h)->left = NULL;	/* root */   //(*h)->left를 NULL로 초기화
	(*h)->right = *h;               //(*h)->right에 *h 값 대입
	(*h)->key = -9999;              //(*h)->key에 -9999 대입
	return 1;                       //1 값 반환
}



void inorderTraversal(Node* ptr) //void형을 반환하는 함수 inorderTraversal(Node* ptr), 중위 순회
{
	if(ptr) {//ptr이 NULL이 아니면
		inorderTraversal(ptr->left); //왼쪽 자식 노드 탐색
		printf(" [%d] ", ptr->key); //ptr->key 값 출력
		inorderTraversal(ptr->right); //오른쪽 자식 노드 탐색
	}
}


void preorderTraversal(Node* ptr) //void형을 반환하는 함수 preorderTraversal(Node* ptr), 전위 순회
{
	if(ptr) { //ptr이 NULL이 아니면
		printf(" [%d] ", ptr->key); //ptr->key 값 출력
		preorderTraversal(ptr->left); //왼쪽 자식 노드 탐색
		preorderTraversal(ptr->right); //오른쪽 자식 노드 탐색
	}
}

void postorderTraversal(Node* ptr) //void형을 반환하는 함수 postorderTraversal(Node* ptr), 후위 순회
{
	if(ptr) { //ptr이 NULL이 아니면
		postorderTraversal(ptr->left); //왼쪽 자식 노드 탐색
		postorderTraversal(ptr->right); //오른쪽 자식 노드 탐색
		printf(" [%d] ", ptr->key); //ptr->key 값 출력
	}
}


int insert(Node* head, int key) //int형 insert(Node* head, int key) 함수
{
	Node* newNode = (Node*)malloc(sizeof(Node)); //*newNode를 동적할당
	newNode->key = key;        //newNode->key에 key 값 대입
	newNode->left = NULL;      //newNode->left를 NULL로 초기화
	newNode->right = NULL;     //newNode->left를 NULL로 초기화

	if (head->left == NULL) { //head->left가 NULL이면
		head->left = newNode; //head->left에 newNode 대입
		return 1; //1 값 반환
	}

	/* head->left is the root */
	Node* ptr = head->left;  //Node *ptr에 head->left 대입

	Node* parentNode = NULL; //Node *parentNode를 NULL로 초기화
	while(ptr != NULL) { //ptr이 NULL이 아니면

		/* if there is a node for the key, then just return */
		if(ptr->key == key) return 1; //ptr->key가 key이면 1 값 반환

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr; //parentNode에 ptr 값 대입

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key) //ptr->key가 key 값보다 작으면
			ptr = ptr->right;//ptr에 ptr->right 값 대입
		else //ptr->key가 key 값보다 같거나 크면
			ptr = ptr->left; //ptr에 ptr->left 값 대입
	}

	/* linking the new node to the parent */
	if(parentNode->key > key) //parentNode->key가 key보다 크면
		parentNode->left = newNode; //parentNode->left에 newNode 대입
	else //parentNode->key가 key보다 작거나 같으면
		parentNode->right = newNode; //parentNode->right에 newNode 대입
	return 1; //1 값 반환
}

int deleteLeafNode(Node* head, int key) //int형 함수 deleteLeafNode(Node* head, int key)
{
	if (head == NULL) { //head가 NULL이면
		printf("\n Nothing to delete!!\n"); // Nothing to delete!! 출력
		return -1; //-1 값 반환
	}

	if (head->left == NULL) {
		printf("\n Nothing to delete!!\n");// Nothing to delete!! 출력
		return -1; //-1 값 반환
	}

	/* head->left is the root */
	Node* ptr = head->left; //Node *ptr에 head->left 대입


	/* we have to move onto children nodes,
	 * keep tracking the parent using parentNode */
	Node* parentNode = head; //Node *parentNode에 head 대입

	while(ptr != NULL) { //ptr이 NULL이 아니면

		if(ptr->key == key) { //ptr->key가 key이면
			if(ptr->left == NULL && ptr->right == NULL) { //ptr->left가 NULL이고 ptr->right가 NULL이면

				/* root node case */
				if(parentNode == head) //parentNode가 head이면
					head->left = NULL; //head->left를 NULL로 초기화

				/* left node case or right case*/
				if(parentNode->left == ptr) //parentNode->left에 ptr 대입
					parentNode->left = NULL; //parentNode->left를 NULL로 초기화
				else
					parentNode->right = NULL; //parentNode->right를 NULL로 초기화

				free(ptr); //ptr 메모리의 주소 값 해제
			}
			else { //ptr이 NULL이면
				printf("the node [%d] is not a leaf \n", ptr->key); //the node [%d] is not a leaf 출력
			}
			return 1; //1 값 반환
		}

		/* keep the parent node */
		parentNode = ptr; //parentNode에 ptr 대입

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key) //ptr->key가 key보다 작으면
			ptr = ptr->right; //ptr에 ptr->right 대입
		else //ptr->key가 key보다 같거나 크면
			ptr = ptr->left; //ptr에 ptr->left 대입


	}

	printf("Cannot find the node for key [%d]\n ", key); //Cannot find the node for key 출력

	return 1; //1 값 반환
}

Node* searchRecursive(Node* ptr, int key) //Node *searchRecursive(Node *ptr, int key)
{
	if(ptr == NULL) //ptr이 NULL이면
		return NULL; //NULL 값 반환

	if(ptr->key < key) //ptr->key가 key보다 작으면
		ptr = searchRecursive(ptr->right, key); //ptr에 searchRecursive(ptr->right, key) 대입
	else if(ptr->key > key) //ptr->key가 key보다 크면
		ptr = searchRecursive(ptr->left, key); //ptr에 searchRecursive(ptr->left, key) 대입

	/* if ptr->key == key */
	return ptr; //ptr 값 반환

}
Node* searchIterative(Node* head, int key) //Node *searchIternative(Node *head, int key)
{
	/* root node */
	Node* ptr = head->left; //Node *ptr에 head->left 대입

	while(ptr != NULL) //ptr이 NULL이 아니면
	{
		if(ptr->key == key) //ptr->key가 key이면
			return ptr; //ptr 값 반환

		if(ptr->key < key) ptr = ptr->right; //ptr->key가 key보다 작으면 ptr에 ptr->right 대입
		else //ptr->key가 key보다 크거나 같으면
			ptr = ptr->left; //ptr에 ptr->left 대입
	}

	return NULL; //NULL 값 반환
}

void freeNode(Node* ptr) //void형 freeNode(Node *ptr)
{
	if(ptr) { //ptr이 NULL이 아니면
		freeNode(ptr->left); //freeNode(ptr->left) 함수 호출
		freeNode(ptr->right); //freeNode(ptr->right) 함수 호출
		free(ptr); //ptr 메모리의 주소 해제
	}
}

int freeBST(Node* head) //int형 freeBST(Node *head) 함수
{

	if(head->left == head) //head->left가 head이면
	{
		free(head); //head의 메모리 주소 해제
		return 1; //1 값 반환
	}

	Node* p = head->left; //Node *p에 head->left 대입

	freeNode(p); //freeNode(p) 함수 호출

	free(head); //head의 메모리 해제
	return 1; //1 값 반환

}