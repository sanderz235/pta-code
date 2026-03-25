#include <stdio.h>
#include <string.h>
char map[505][505],A[12][12];

int check_position(int r,int c) {
    for(int i=0;i<7;i++)for(int j=0;j<7;j++){
        int edge = (i==0||i==6||j==0||j==6);
        int center = (i>=2&&i<=4&&j>=2&&j<=4);
        char ch = map[r+i][c+j];
        if(edge||center){if(ch!='*')return 0;}
        else{if(ch!='.')return 0;}
    }
    return 1;
}

int main() {
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=0;i<n;i++) scanf("%s",map[i]);

    int qr_x = -1, qr_y = -1;
    // 遍历所有21x21大正方形区检测3枚finder
    for(int i=0; i <= n-21; i++) {
        for(int j=0; j <= m-21; j++) {
            // 检查左上、左下、右上三个 7x7 finder
            if(check_position(i, j) && check_position(i+14, j) && check_position(i, j+14)) {
                qr_x = i;
                qr_y = j;
                goto FOUND;
            }
        }
    }
FOUND:
    // 自然假定题目保证存在二维码，无需额外报错处理

    // 采样有效区A[12][12]，其左上角是map[qr_x+9][qr_y+9]
    int base_r = qr_x + 9, base_c = qr_y + 9;
    for(int i=0;i<12;i++)
        for(int j=0;j<12;j++)
            A[i][j]=map[base_r+i][base_c+j];

    int bits[144], cnt=0;
    for(int pair=0; pair<6; pair++) {
        int col1 = 11 - pair*2;
        int col2 = col1 - 1;
        for(int row=11; row>=0; row--) {
            bits[cnt++] = (A[row][col1] == '*');
            bits[cnt++] = (A[row][col2] == '*');
        }
    }
    int x = bits[0]*2 + bits[1];
    int a = 0, b = 0, idx = 14;
    for(int i=2;i<6;i++) a = a*2 + bits[i];
    for(int i=6;i<14;i++) b = b*2 + bits[i];
    const char* typenames[4] = {"payment","wifi","account","address"};
    printf("%s ", typenames[x]);
    for(int i=0;i<b;i++) {
        int t=0;
        for(int j=0;j<a;j++)
            t = (t<<1) | bits[idx++];
        putchar((t%95) + 32);
    }
    puts("");
    return 0;
}