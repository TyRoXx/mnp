#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct Node
{
	struct Node *next;
	int element;
}
Node;

static Node *createNode(int value)
{
	Node * const result = malloc(sizeof(*result));
	if (result)
	{
		result->next = 0;
		result->element = value;
	}
	return result;
}

static Node *getNext(Node *current)
{
	assert(current);
	return current->next;
}

static void appendAtTheEnd(Node *root, Node *toAppend)
{
	Node *last = root;

	assert(root);
	assert(toAppend);

	while (last->next)
	{
		last = last->next;
	}

	last->next = toAppend;
}

static int hasNext(Node *current)
{
	assert(current);
	return (current->next != 0);
}

static int getValue(Node *current)
{
	assert(current);
	return current->element;
}

typedef struct LinkedList
{
	Node *first, *last;
}
LinkedList;

static void createLinkedList(LinkedList *list)
{
	list->first = list->last = 0;
}

static void destroyLinkedList(LinkedList *list)
{
	Node *current = list->first;
	while (current)
	{
		Node * const next = current->next;
		free(current);
		current = next;
	}
}

static int pushBack(LinkedList *list, int value)
{
	Node * const node = createNode(value);
	if (node)
	{
		if (list->last)
		{
			list->last->next = node;
		}
		else
		{
			list->first = node;
		}
		list->last = node;
		return 1;
	}
	return 0;
}

int const ListSize = 32;

int main(void)
{
	int result;
	LinkedList list;
	Node *current;
	int i;

	(void)appendAtTheEnd; /*pushBack is better*/

	createLinkedList(&list);

	for (i = 0; i < ListSize; ++i)
	{
		if (!pushBack(&list, i))
		{
			printf("No memory\n");
			result = 1;
			goto leave;
		}
	}

	i = 0;
	current = list.first;
	for (;;)
	{
		if (!current)
		{
			printf("cannot check because current is NULL\n");
			result = 1;
			goto leave;
		}

		if (getValue(current) != i)
		{
			printf("Expected %i\n", i);
			result = 1;
			goto leave;
		}

		++i;
		if (hasNext(current))
		{
			current = getNext(current);
		}
		else
		{
			break;
		}
	}

	if (i != ListSize)
	{
		printf("Unexpected number of elements\n");
		result = 1;
		goto leave;
	}

	printf("Test passed\n");
	result = 0;

leave:
	destroyLinkedList(&list);
	return result;
}

