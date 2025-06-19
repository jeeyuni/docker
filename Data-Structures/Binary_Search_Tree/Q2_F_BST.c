//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section F - Binary Search Trees Questions
Purpose: Implementing the required functions for Question 2 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _bstnode{
	int item;
	struct _bstnode *left;
	struct _bstnode *right;
} BSTNode;   // You should not change the definition of BSTNode

typedef struct _stackNode{
	BSTNode *data;
	struct _stackNode *next;
}StackNode; // You should not change the definition of StackNode

typedef struct _stack
{
	StackNode *top;
}Stack; // You should not change the definition of Stack

///////////////////////// function prototypes ////////////////////////////////////

// You should not change the prototypes of these functions
void inOrderTraversal(BSTNode *node);

void insertBSTNode(BSTNode **node, int value);

void push(Stack *stack, BSTNode *node);
BSTNode *pop(Stack *s);
BSTNode *peek(Stack *s);
int isEmpty(Stack *s);
void removeAll(BSTNode **node);

///////////////////////////// main() /////////////////////////////////////////////

int main()
{
	int c, i;
	c = 1;

	//Initialize the Binary Search Tree as an empty Binary Search Tree
	BSTNode *root;
	root = NULL;

	printf("1: Insert an integer into the binary search tree;\n");
	printf("2: Print the in-order traversal of the binary search tree;\n");
	printf("0: Quit;\n");


	while (c != 0)
	{
		printf("Please input your choice(1/2/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to insert into the Binary Search Tree: ");
			scanf("%d", &i);
			insertBSTNode(&root, i);
			break;
		case 2:
			printf("The resulting in-order traversal of the binary search tree is: ");
			inOrderTraversal(root); // You need to code this function
			printf("\n");
			break;
		case 0:
			removeAll(&root);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}

	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

void inOrderTraversal(BSTNode *root)
{
	 /* 문제 접근 방식:
	 루트 노드에서 왼쪽 자식을 끝까지 내려가며 스택에 쌓고, 왼쪽이 끝나면 스택에서 pop을 하여 방문한다.
	 그다음 오른쪽 자식으로 이동한다.
	 스택을 이용하기 때문에 가장 왼쪽에 있는 노드 부터 방문한다.
	 */

	 //스택을 생성한다
	 Stack stk;
	 stk.top = NULL; // 스택을 초기화 한다
	 
	//현재 탐색을 할 포인터를 만들어주고, 지금은 root로 지정한다.
	 BSTNode *cur = root; 

	/*외부에 있는 이 while문은 순회 전체 반복을 위한 루프이다. 
	cur 포인터가 NULL을 가리키거나, 스택이 비었다면 중지한다.
	즉 트리 전체를 모두 방문할때 까지 반복. */
	 while (cur != NULL || !isEmpty(&stk)) {
		/*내부에 있는 이번 while문은 현재 노드의 왼쪽 자식이 존재하는 한 계속 왼쪽으로 내려가며
		지나가는 노드를 스택에 쌓아두게 되고 가장 마지막에 저장된 제일 왼쪽에 있는 노드가
		먼저 pop되게 된다. 
		*/
		while (cur != NULL) {
			push(&stk, cur); 
			cur = cur -> left; // cur이 NULL을 가리킬때까지 왼쪽으로 이동
		}

		//왼쪽 끝에 가게 됐다면 while에서 나오게 되고, 가장 최근에 저장 된 노드를 pop하고 그 루트를 cur로 갱신. 
		cur = pop(&stk); 
		printf("%d " , cur->item);

		//오른쪽 자식이 있다면 오른쪽 자식으로 설정하고 이동.
		cur = cur-> right;
	 }
}

///////////////////////////////////////////////////////////////////////////////

void insertBSTNode(BSTNode **node, int value){
	if (*node == NULL)
	{
		*node = malloc(sizeof(BSTNode));

		if (*node != NULL) {
			(*node)->item = value;
			(*node)->left = NULL;
			(*node)->right = NULL;
		}
	}
	else
	{
		if (value < (*node)->item)
		{
			insertBSTNode(&((*node)->left), value);
		}
		else if (value >(*node)->item)
		{
			insertBSTNode(&((*node)->right), value);
		}
		else
			return;
	}
}

//////////////////////////////////////////////////////////////////////////////////

//사용법: 스택과 푸시할 노드를 받는다
void push(Stack *stack, BSTNode * node)
{
	StackNode *temp;

	temp = malloc(sizeof(StackNode));

	if (temp == NULL)
		return;
	temp->data = node;

	if (stack->top == NULL)
	{
		stack->top = temp;
		temp->next = NULL;
	}
	else
	{
		temp->next = stack->top;
		stack->top = temp;
	}
}

BSTNode * pop(Stack * s)
{
	StackNode *temp, *t;
	BSTNode * ptr;
	ptr = NULL;

	t = s->top;
	if (t != NULL)
	{
		temp = t->next;
		ptr = t->data;

		s->top = temp;
		free(t);
		t = NULL;
	}

	return ptr;
}

BSTNode * peek(Stack * s)
{
	StackNode *temp;
	temp = s->top;
	if (temp != NULL)
		return temp->data;
	else
		return NULL;
}

int isEmpty(Stack *s)
{
	if (s->top == NULL)
		return 1;
	else
		return 0;
}


void removeAll(BSTNode **node)
{
	if (*node != NULL)
	{
		removeAll(&((*node)->left));
		removeAll(&((*node)->right));
		free(*node);
		*node = NULL;
	}
}
