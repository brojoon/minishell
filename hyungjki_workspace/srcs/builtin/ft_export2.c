#include "../../includes/minishell.h"

static int my_strcmp(const char *s1, const char *s2)
{
	int index;

	index = 0;
	while (s1[index] || s2[index])
	{
		if (s1[index] != s2[index])
			return (((unsigned char*)s1)[index] - ((unsigned char*)s2)[index]);
		++index;
	}
	return (0);
}

static void merge(t_env *array[], int low, int middle, int hight, t_env *temp[])
{
    int leftP = low;
    int rightP = middle + 1;
    int tempP = low;

    while ((leftP<=middle) && (rightP<=hight))
    {
		if(my_strcmp(array[leftP]->key, array[rightP]->key) < 0) temp[tempP++] = array[leftP++];
        else temp[tempP++] = array[rightP++];
    }

    while(leftP<=middle) temp[tempP++] = array[leftP++];
    while(rightP<=hight) temp[tempP++] = array[rightP++];

    tempP--;

    while(tempP >= low) {
        array[tempP] = temp[tempP];
        tempP--;
    }
}

static void mergeSort_i(t_env *array[], int low, int hight, t_env *temp[])
{
    if(low < hight) {
        int middle = (low + hight) / 2;
        mergeSort_i(array, low, middle, temp);
        mergeSort_i(array, middle + 1, hight, temp);
        merge(array, low, middle, hight, temp);
    }
}

void mergeSort(t_env *array[], int low, int hight)
{
    t_env **temp = malloc(sizeof(t_env*) * (hight - low + 1));
    mergeSort_i(array, low, hight, temp);
    free(temp);
}