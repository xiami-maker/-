#include <stdio.h>
#include <time.h>
#include <malloc.h>

#include "mec.h"

u8 *numberPool;

boolean isPrime(int num);
boolean isGoldbach(int num);
u8 *screenPrime(int count);

u8 *screenPrime(int count) {
	int i;
	int j;
	u8 *num;

	num = (u8 *) calloc(sizeof(u8), (count + 7) >> 3);

	for (i = 4; i < count; i += 2) {
		SET(num[i >> 3], i & 7);
	}
	for (i = 3; i*i <= count; i += 2) {
		if (GET(num[i >> 3], i & 7) == 0) {
			for (j = i*i; j < count; j += i) {
				SET(num[j >> 3], j & 7);
			}
		}
	}

	return num;
}

boolean isGoldbach(int num) {
	int i;

	for (i = 3; i <= num / 2; i += 2) {
		if (isPrime(i) && isPrime(num - i)) {
			// printf("%d = %d + %d\n", num, i, num - i);
			return TRUE;
		}
	}

	return FALSE;
}

boolean isPrime(int num) {
	return GET(numberPool[num >> 3], num & 0x07) == 0;
}

int main() {
	// int i;

	// numberPool = screenPrime(1000);
	// for (i = 2; i < 1000; i++) {
	// 	if (isPrime(i)) {
	// 		printf("%d ", i);
	// 	}
	// }
	// printf("\n");

	int maxNum;
	int i;
	long startTime;
	long endTime;
	long deltaTime;

	printf("请输入范围:");
	scanf("%d", &maxNum);

	numberPool = screenPrime(maxNum);

	startTime = clock();
	for (i = 6; i < maxNum; i += 2) {
		if (!isGoldbach(i)) {
			printf("%d!!!!!!!!永远不可能输出！\n", i);
			return 0;
		}
	}
	endTime = clock();
	deltaTime = endTime - startTime;
	printf("耗时:%ld.%03lds\n", deltaTime / CLOCKS_PER_SEC, deltaTime % CLOCKS_PER_SEC);
	printf("向老哥致敬！\n");

	free(numberPool);


	return 0;
}
