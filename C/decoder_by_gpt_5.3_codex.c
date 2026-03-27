#include <stdio.h>

#define MAXN 505

static char g[MAXN][MAXN];

/*
 * 判断从 (r,c) 开始的 7x7 是否为定位图形：
 * 外框黑，中间 3x3 黑，其余白
 */
int is_finder(int r, int c) {
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            char need = '.';
            if (i == 0 || i == 6 || j == 0 || j == 6) need = '*';
            else if (i >= 2 && i <= 4 && j >= 2 && j <= 4) need = '*';

            if (g[r + i][c + j] != need) return 0;
        }
    }
    return 1;
}

/*
 * 判断 21x21 的候选二维码左上角是否在 (r,c)
 * 条件：
 * 1) 区域内都必须是 '*' 或 '.'
 * 2) 三个定位图形分别在左上、右上、左下
 */
int is_qr_at(int n, int m, int r, int c) {
    if (r + 20 >= n || c + 20 >= m) return 0;

    for (int i = r; i <= r + 20; i++) {
        for (int j = c; j <= c + 20; j++) {
            if (g[i][j] != '*' && g[i][j] != '.') return 0;
        }
    }

    if (!is_finder(r, c)) return 0;           // 左上
    if (!is_finder(r, c + 14)) return 0;      // 右上
    if (!is_finder(r + 14, c)) return 0;      // 左下

    return 1;
}

/* 从 bits[pos..] 读取 len 位（二进制高位到低位）并转十进制 */
int read_bits(const int bits[], int *pos, int len) {
    int v = 0;
    for (int i = 0; i < len; i++) {
        v = (v << 1) | bits[(*pos)++];
    }
    return v;
}

int main(void) {
    int n, m;
    if (scanf("%d %d", &n, &m) != 2) return 0;

    for (int i = 0; i < n; i++) {
        scanf("%s", g[i]);
    }

    int sr = -1, sc = -1;

    /* 在场景中定位唯一合法二维码 */
    for (int r = 0; r + 20 < n && sr == -1; r++) {
        for (int c = 0; c + 20 < m; c++) {
            if (g[r][c] != '*') continue; // 小剪枝：定位图形左上角一定是黑
            if (is_qr_at(n, m, r, c)) {
                sr = r;
                sc = c;
                break;
            }
        }
    }

    /* 读取右下 12x12 存储区（行: sr+9..sr+20, 列: sc+9..sc+20）
       正确顺序：
       从最右两列开始 -> 每组两列都“自下而上”读取
       每一行内先右列再左列
    */
    int bits[144], k = 0;
    for (int right = sc + 20; right >= sc + 10; right -= 2) {
        int left = right - 1;
        for (int r = sr + 20; r >= sr + 9; r--) {
            bits[k++] = (g[r][right] == '*') ? 1 : 0;
            bits[k++] = (g[r][left]  == '*') ? 1 : 0;
        }
    }

    int pos = 0;
    int x = read_bits(bits, &pos, 2);  // 类型
    int a = read_bits(bits, &pos, 4);  // 每个十进制数由 a 位二进制组成
    int b = read_bits(bits, &pos, 8);  // 读取 b 个十进制数

    const char *type_name[4] = {"payment", "wifi", "account", "address"};
    if (x < 0 || x > 3) x = 0;

    printf("%s ", type_name[x]);

    if (a <= 0) { // 防异常保护
        putchar('\n');
        return 0;
    }

    int max_b = (k - pos) / a;
    if (b > max_b) b = max_b;

    for (int i = 0; i < b; i++) {
        int t = read_bits(bits, &pos, a);
        char ch = (char)(t % 95 + 32);
        putchar(ch);
    }
    putchar('\n');

    return 0;
}