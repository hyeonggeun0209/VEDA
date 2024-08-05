#include <stdio.h>

int gcd(int a, int b) {
    int ans;
    for (int i = 1; i <= a; i++) {
        if(a % i == 0 && b % i == 0)
            ans = i;
    }
    return ans;
}

int main() {
    int i, n;
    int arr[10] = {0, };

    scanf("%d", &n);

    for(i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    int ans = arr[0];

    for(i = 1; i < n; i++) {
        ans = gcd(ans, arr[i]);
    }

    return 0;
}