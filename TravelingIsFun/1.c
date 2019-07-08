#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define min(a,b) ((a>b) ? b : a)
#define max(a,b) ((a<b) ? b : a)

int findPath(int g, int origin, int destination) {
	int temp;
	int a = min(origin, destination);
	int b = max(origin, destination);
	while (b) {
		temp = a % b;
		a = b;
		b = temp;
	}
	if (a > g)
		return 1;
	else
		return 0;
}
int *connectedCities(int n, int g, int originCities_count, int *originCities, int destinationCities_count, int *destinationCities, int *result_count) {
	int *result, **weight, i, j, k;
	*result_count = originCities_count;
	result = (int *)malloc(sizeof(int) * (*result_count));
	weight = (int **)malloc(sizeof(int *) * n);
	for (i = 0; i < n; i++) {
		weight[i] = (int *)malloc(sizeof(int) * n);
		for (j = 0; j < n; j++)
			weight[i][j] = 100000;
	}
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			if (findPath(g, i + 1, j + 1) == 1)
				weight[i][j] = 1;
		}
	}
	for (k = 0; k < n; k++) {
		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++) {
				if (weight[i][j] > weight[i][k] + weight[k][j])
					weight[i][j] = weight[i][k] + weight[k][j];
			}
		}
	}
	for (i = 0; i < originCities_count; i++) {
		if (weight[originCities[i] - 1][destinationCities[i] - 1] < 5000)
			*(result + i) = 1;
		else
			*(result + i) = 0;
	}

	for (i = 0; i < n; i++)
		free(weight[i]);
	free(weight);
	return result;
}

int main()
{
	int n, g, originCities_count, *originCities, destinationCities_count, *destinationCities, result_count;
	scanf("%d%d%d", &n, &g, &originCities_count);
	originCities = (int *)malloc(sizeof(int)*originCities_count);
	for (int i = 0; i < originCities_count; i++) {
		scanf("%d", (originCities + i));
	}
	scanf("%d", &destinationCities_count);
	destinationCities = (int *)malloc(sizeof(int)*destinationCities_count);
	for (int i = 0; i < destinationCities_count; i++)
		scanf("%d", (destinationCities + i));
	int *result = connectedCities(n, g, originCities_count, originCities, destinationCities_count, destinationCities, &result_count);
	for (int i = 0; i < result_count; i++)
		printf("%d\n", *(result + i));

}