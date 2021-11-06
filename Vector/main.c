# include <stdio.h>
# include <stdlib.h>

typedef struct linkedlist {
	int number;

	struct linkedlist *next;
} t_list;

t_list	*init_list(void)
{
	t_list *a;

	a = (t_list *)malloc(sizeof(t_list) * 1);
	a->number = 0;
	a->next = NULL;
	return (a);
}

int main() {
	t_list	*a;
	t_list *tmp;
	int		i;


	
	a = init_list(); 
	tmp = a;
	if (a == NULL)
		return (-1);
	i = 0;
	while (i != 10) {
		a->number = i;
		a->next = init_list();
		a = a->next;
		i++;
	}
	a = tmp;

	while (a->next)
	{
		printf("%d ", a->number);
		a = a->next;
	}
	return (0);
}


