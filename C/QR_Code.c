#include <stdio.h>

static char g[505][505];

static int finder(int r, int c) {
    for (int i = 0; i < 7; i++)
        for (int j = 0; j < 7; j++) {
            int edge = (i == 0 || i == 6 || j == 0 || j == 6);
            int mid  = (i >= 2 && i <= 4 && j >= 2 && j <= 4);
            char ch = g[r + i][c + j];
            if ((edge || mid) ? (ch != '*') : (ch != '.')) return 0;
        }
    return 1;
}

int main(void) {
    int n, m, qr = 0, qc = 0;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) scanf("%s", g[i]);

    for (int i = 0; i <= n - 21; i++) {
        for (int j = 0; j <= m - 21; j++) {
            if (finder(i, j) && finder(i + 14, j) && finder(i, j + 14)) {
                qr = i; qc = j;
                i = n;                 /* break 2 loops */
                break;
            }
        }
    }

    int br = qr + 9, bc = qc + 9, bits[144], k = 0;
    for (int p = 0; p < 6; p++) {
        int c1 = bc + 11 - 2 * p, c2 = c1 - 1;
        for (int r = br + 11; r >= br; r--) {
            bits[k++] = (g[r][c1] == '*');
            bits[k++] = (g[r][c2] == '*');
        }
    }

    int x = (bits[0] << 1) | bits[1], a = 0, b = 0, idx = 14;
    for (int i = 2; i < 6;  i++) a = (a << 1) | bits[i];
    for (int i = 6; i < 14; i++) b = (b << 1) | bits[i];

    static const char *tname[4] = {"payment", "wifi", "account", "address"};
    printf("%s ", tname[x]);

    for (int i = 0; i < b; i++) {
        int t = 0;
        for (int j = 0; j < a; j++) t = (t << 1) | bits[idx++];
        putchar(t % 95 + 32);
    }
    putchar('\n');
    return 0;
}