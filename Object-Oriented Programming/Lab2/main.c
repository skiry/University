#include <stdio.h>

int isPrime(int nr) {
	// function that verifies if NR is a prime number
	// 1 if Prime, 0 if Not Prime
	for(int d = 2; d*d <= nr; d++)
		if(nr % d == 0) return 0;
	return 1;
}

void primeFactors(int n) {
	// decompose N into prime factors. 
	// loop through all the prime factors and divide N to those as long as the remainder is 0.
	int a[100], cp = n;

	for(int d = 1; d <= 100; d++) a[d] = 0;
	if(isPrime(n)) {
		printf("%d = %d ^ 1", n, n);
	}
	else {
		for(int d = 2; d <= n; d++) {
			if(isPrime(d)) {
				while(n % d == 0) {
					a[d]++;
					n /= d;
				}
			}
		}
		printf("N = ");
		int ok = 0;
		for(int d = 2; d <= cp; d++) {
			if(a[d] && ok) {
				printf("* %d ^ %d ", d, a[d]);
			}
			else if(a[d] && !ok){
				printf("%d ^ %d ", d, a[d]);
				ok = 1;
			}

		}
	}
}

int same(int el1, int el2) {
	// input : el1, el2 
	// output : 0 daca vectorii de frecventa sunt la fel, 1 daca numerele sunt formate din exact aceleasi cifre
	int f1[10], f2[10];
	for(int i = 0; i < 10; i++) f1[i] = f2[i] = 0;

	while(el1) {
		f1[el1 % 10]++;
		el1 /= 10;
	}

	while(el2) {
		f2[el2 % 10]++;
		el2 /= 10;
	}

	for(int i = 0; i < 10; i++)
		if( f1[i] != f2[i]) return 0;

	return 1;
}

void longestSeq(int a[100], int n) {
	// input : a[100], n
	// print the longest contiguous subsuqence such that the numbers have the same digits
	int maxi = 0, len = 0, pos = n;
	for(int i = 1; i < n; i++) {
		if( same(a[i], a[i+1]) ) {
			len++;
			if(i == n - 1 && len > maxi){
				maxi = len;
				pos = i;
				len = 10;
			}
		}
		else {
			if(len > maxi) {
				maxi = len;
				pos = i;
				len = 0;
			}
		}
	}
	if(len == 10) pos++;
	printf("The longest subseq with consec elements having the same digits is : \n");
	for(int i = pos - maxi; i <= pos; i++){
		printf("%d ", a[i]);
	}
}
int main(){
	int x = 3;
	while(x){
		printf("\n\n1. Decompose a number in its prime factors.\n");
		printf("2. Find the longest contiguous subseq such that any consec elements contain the same digits.\n");
		printf("0. Quit.\n");
		scanf("%d", &x);
		if(x == 1) {
			x = 9;
			int n;

			printf("N = ");
			scanf("%d", &n);

			primeFactors(n);
		}
		else if(x == 2) {
			x = 9;
			int n, a[100];

			printf("N = ");
			scanf("%d", &n);

			for(int i = 1; i <= n; i++) {
				scanf("%d", &a[i]);
			}

			longestSeq(a, n);
		}
	}
	

	return 0;
}