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

int main(void)
{
	Node * const root = createNode(0);
	Node *current;
	int i;

	for (i = 1; i < 32; ++i)
	{
		appendAtTheEnd(root, createNode(i));
	}

	i = 0;
	current = root;
	for (;;)
	{
		if (!current)
		{
			printf("cannot check because current is NULL\n");
			return 1;
		}

		if (getValue(current) != i)
		{
			printf("Expected %i\n", i);
			return 1;
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

	if (i != 32)
	{
		printf("Unexpected number of elements\n");
		return 1;
	}

	printf("Test passed\n");
	return 0;
}

