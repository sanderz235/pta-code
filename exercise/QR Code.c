#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const int FORMAT_INFO_DECODE[32] = {
    0x5412, 0x5125, 0x5E7C, 0x5B4B, 0x45F9, 0x40CE, 0x4F97, 0x4AA0,
    0x77C4, 0x72F3, 0x7DAA, 0x789D, 0x662F, 0x6318, 0x6C41, 0x6976,
    0x1689, 0x13BE, 0x1CE7, 0x19D0, 0x0762, 0x0255, 0x0D0C, 0x083B,
    0x355F, 0x3068, 0x3F31, 0x3A06, 0x24B4, 0x2183, 0x2EDA, 0x2BED
};

int hammingDistance(int a, int b) {
    int x = a ^ b;
    int cnt = 0;
    while (x) {
        cnt += x & 1;
        x >>= 1;
    }
    return cnt;
}

int maskBit(int mask, int r, int c) {
    switch (mask) {
        case 0: return ((r + c) % 2) == 0;
        case 1: return (r % 2) == 0;
        case 2: return (c % 3) == 0;
        case 3: return ((r + c) % 3) == 0;
        case 4: return (((r / 2) + (c / 3)) % 2) == 0;
        case 5: return (((r * c) % 2) + ((r * c) % 3)) == 0;
        case 6: return ((((r * c) % 2) + ((r * c) % 3)) % 2) == 0;
        case 7: return ((((r + c) % 2) + ((r * c) % 3)) % 2) == 0;
        default: return 0;
    }
}

int isFinderPattern(int r, int c) {
    if (r >= 0 && r <= 6 && c >= 0 && c <= 6) return 1;
    if (r >= 0 && r <= 6 && c >= -0 && c <= 6) return 1;
    return 0;
}

int isFunctionModule(int r, int c, int moduleCount, int version) {
    // finder pattern + separators
    if (r <= 8 && c <= 8) return 1;
    if (r <= 8 && c >= moduleCount - 8) return 1;
    if (r >= moduleCount - 8 && c <= 8) return 1;
    // timing
    if (r == 6 && c >= 8 && c < moduleCount - 8) return 1;
    if (c == 6 && r >= 8 && r < moduleCount - 8) return 1;
    // version info for version>=7 not needed in v1
    if (r == 8 && c == 8) return 1;
    return 0;
}

int readInt(const int *bits, int start, int len) {
    int val = 0;
    for (int i = 0; i < len; i++) {
        val = (val << 1) | bits[start + i];
    }
    return val;
}

int main() {
    int n, m;
    if (scanf("%d %d", &n, &m) != 2) return 0;

    char **grid = (char **)malloc(n * sizeof(char *));
    for (int i = 0; i < n; i++) {
        grid[i] = (char *)malloc((m + 1) * sizeof(char));
        scanf("%s", grid[i]);
    }

    int minr = n, maxr = -1, minc = m, maxc = -1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == '*') {
                if (i < minr) minr = i;
                if (i > maxr) maxr = i;
                if (j < minc) minc = j;
                if (j > maxc) maxc = j;
            }
        }
    }

    if (maxr < minr || maxc < minc) {
        for (int i = 0; i < n; i++) free(grid[i]);
        free(grid);
        return 0;
    }

    int height = maxr - minr + 1;
    int width = maxc - minc + 1;
    int side = (height > width ? height : width);
    int sr = minr;
    int sc = minc;
    if (sr + side > n) sr = n - side;
    if (sc + side > m) sc = m - side;
    if (sr < 0) sr = 0;
    if (sc < 0) sc = 0;

    int *square = (int *)malloc(side * side * sizeof(int));
    for (int i = 0; i < side; i++) {
        for (int j = 0; j < side; j++) {
            int r = sr + i;
            int c = sc + j;
            char ch = '.';
            if (r >= 0 && r < n && c >= 0 && c < m) ch = grid[r][c];
            square[i * side + j] = (ch == '*') ? 1 : 0;
        }
    }

    int moduleCount = 0;
    int version = 0;
    int moduleMatrix[177][177] = {{0}};

    for (int ver = 1; ver <= 40; ver++) {
        int candidate = 17 + 4 * ver;
        if (candidate > side) break;
        if (side % candidate != 0) continue;
        int msize = side / candidate;

        int tmp[177][177];
        for (int i = 0; i < candidate; i++) {
            for (int j = 0; j < candidate; j++) {
                int count = 0;
                for (int ii = 0; ii < msize; ii++) {
                    for (int jj = 0; jj < msize; jj++) {
                        int r = i * msize + ii;
                        int c = j * msize + jj;
                        if (square[r * side + c]) count++;
                    }
                }
                tmp[i][j] = (count * 2 >= msize * msize) ? 1 : 0;
            }
        }

        int ok = 1;
        // Check finder patterns at 3 corners
        for (int i = 0; i < 7 && ok; i++) {
            for (int j = 0; j < 7 && ok; j++) {
                int exp = (((i == 0 || i == 6) || (j == 0 || j == 6)) || (i >= 2 && i <= 4 && j >= 2 && j <= 4)) ? 1 : 0;
                if (tmp[i][j] != exp) ok = 0;
                if (tmp[i][candidate - 7 + j] != exp) ok = 0;
                if (tmp[candidate - 7 + i][j] != exp) ok = 0;
            }
        }

        if (!ok) continue;

        // dark module check
        int darkR = 8;
        int darkC = 4 * ver + 9;
        if (darkC < candidate) {
            if (tmp[darkR][darkC] != 1) ok = 0;
        }

        if (!ok) continue;

        moduleCount = candidate;
        version = ver;
        for (int i = 0; i < moduleCount; i++) {
            for (int j = 0; j < moduleCount; j++) {
                moduleMatrix[i][j] = tmp[i][j];
            }
        }
        break;
    }

    int decoded = 0;
    int x = 0, a = 0, b = 0;
    char result[1000] = "";

    if (moduleCount > 0) {
        int format1 = 0;
        int poslist1[15][2] = {
            {8,0},{8,1},{8,2},{8,3},{8,4},{8,5},{8,7},{8,8},{7,8},{5,8},{4,8},{3,8},{2,8},{1,8},{0,8}
        };
        for (int i = 0; i < 15; i++) {
            int r = poslist1[i][0];
            int c = poslist1[i][1];
            format1 = (format1 << 1) | moduleMatrix[r][c];
        }

        int format2 = 0;
        int poslist2[15][2] = {
            {moduleCount-1,8},{moduleCount-2,8},{moduleCount-3,8},{moduleCount-4,8},{moduleCount-5,8},{moduleCount-6,8},{moduleCount-7,8},{8,moduleCount-8},{8,moduleCount-7},{8,moduleCount-6},{8,moduleCount-5},{8,moduleCount-4},{8,moduleCount-3},{8,moduleCount-2},{8,moduleCount-1}
        };
        for (int i = 0; i < 15; i++) {
            int r = poslist2[i][0];
            int c = poslist2[i][1];
            format2 = (format2 << 1) | moduleMatrix[r][c];
        }

        int bestMask = -1;
        int bestFormat16 = 0;
        int bestDist = 16;
        for (int i = 0; i < 32; i++) {
            int d1 = hammingDistance(format1, FORMAT_INFO_DECODE[i]);
            int d2 = hammingDistance(format2, FORMAT_INFO_DECODE[i]);
            int d = d1 < d2 ? d1 : d2;
            if (d < bestDist) {
                bestDist = d;
                bestMask = i & 0x7;
                bestFormat16 = i;
            }
        }

        if (bestMask >= 0) {
            int dataBits[4096];
            int dataLen = 0;

            int r = moduleCount - 1;
            int upward = 1;
            while (r > 0) {
                if (r == 6) { r--; continue; }
                if (upward) {
                    for (int i = moduleCount - 1; i >= 0; i--) {
                        for (int c = r; c >= r - 1; c--) {
                            if (c < 0) continue;
                            if (isFunctionModule(i, c, moduleCount, version)) continue;
                            int bit = moduleMatrix[i][c];
                            if (maskBit(bestMask, i, c)) bit ^= 1;
                            dataBits[dataLen++] = bit;
                        }
                    }
                } else {
                    for (int i = 0; i < moduleCount; i++) {
                        for (int c = r; c >= r - 1; c--) {
                            if (c < 0) continue;
                            if (isFunctionModule(i, c, moduleCount, version)) continue;
                            int bit = moduleMatrix[i][c];
                            if (maskBit(bestMask, i, c)) bit ^= 1;
                            dataBits[dataLen++] = bit;
                        }
                    }
                }
                upward = !upward;
                r -= 2;
            }

            if (dataLen >= 14) {
                x = readInt(dataBits, 0, 2);
                a = readInt(dataBits, 2, 4);
                b = readInt(dataBits, 6, 8);
                if (a <= 0) a = 1;
                int pos = 14;
                int outlen = 0;
                for (int i = 0; i < b; i++) {
                    if (pos + a > dataLen) break;
                    int t = readInt(dataBits, pos, a);
                    pos += a;
                    result[outlen++] = (char)((t % 95) + 32);
                }
                result[outlen] = '\0';
                decoded = 1;
            }
        }
    }

    if (!decoded) {
        int totalBits = height * width;
        int *raw = (int *)malloc(totalBits * sizeof(int));
        int idx2 = 0;
        for (int i = minr; i <= maxr; i++) {
            for (int j = minc; j <= maxc; j++) {
                raw[idx2++] = (grid[i][j] == '*') ? 1 : 0;
            }
        }
        if (totalBits >= 14) {
            x = 0; a = 0; b = 0;
            for (int i = 0; i < 2; i++) x = (x << 1) | raw[i];
            for (int i = 0; i < 4; i++) a = (a << 1) | raw[2 + i];
            for (int i = 0; i < 8; i++) b = (b << 1) | raw[6 + i];
            if (a <= 0) a = 1;
            int pos = 14;
            int outlen = 0;
            for (int i = 0; i < b; i++) {
                if (pos + a > totalBits) break;
                int t = 0;
                for (int j = 0; j < a; j++) {
                    t = (t << 1) | raw[pos + j];
                }
                pos += a;
                result[outlen++] = (char)((t % 95) + 32);
            }
            result[outlen] = '\0';
        }
        free(raw);
    }

    const char *types[] = {"payment", "wifi", "account", "address"};
    const char *typeName = "unknown";
    if (x >= 0 && x <= 3) typeName = types[x];

    printf("%s %s\n", typeName, result);

    for (int i = 0; i < n; i++) free(grid[i]);
    free(grid);
    free(square);

    return 0;
}

