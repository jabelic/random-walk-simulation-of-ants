//2610180082 水野 響 期末レポート
#include <stdio.h>
#include <glsc.h>
#include <stdlib.h>

#define N 10
#define IMAX 20
#define JMAX 20
#define M 10
double dice();

//配列に関してはi行j列は[i][j]に格納.
int main(void){
    int i, j, S, cmax;
    int c[IMAX + 1][JMAX + 1] = {};
    double d[IMAX + 1][JMAX + 1] = {}; //配列cを正規化した値を格納する配列
    int x[M] = {}, y[M] = {};          //蟻の最終位置を記録する配列
    int fourway[4] = {};               //最終位置の周りのマスの足跡の数を格納する配列
    double rate[200] = {};
    int list_numeric = 0;
    //rprintf("シード値(自然数)を入力:");
    //scanf("%d", &S); //乱数
    //srand(S);
    for (int s = 0; s <= 200; s++){

        srand(s);
        //初期化
        g_init("GRAPH", 200.0, 100.0);
        g_device(G_DISP);

        //仮想座標系を定義
        g_def_scale(1, -0.5, 2 * (IMAX + 0.5) + 5.0, -0.5, JMAX + 0.5, 10.0, 10.0, 180.0, 80.0);
        g_sel_scale(1);

        g_box(-0.5, IMAX + 0.5, -0.5, JMAX + 0.5, G_YES, G_NO);

        //縦線の描画
        for (i = 0; i < IMAX + 1; i++)
        {
            g_move(i - 0.5, -0.5);
            g_plot(i - 0.5, JMAX + 0.5);
        }
        //横線の描画
        for (j = 0; j < JMAX + 1; j++)
        {
            g_move(-0.5, j - 0.5);
            g_plot(IMAX + 0.5, j - 0.5);
        }

        //m匹のプログラム
        for (int m = 1; m <= M; m++){
            //i,jの初期値の設定
            i = IMAX / 2;
            j = JMAX / 2;
            //１匹ずつ描画
            for (int k = 0; k < N; k++)
            {
                g_marker_type(-1);
                g_marker_color(G_RED); //丸のマーカーで描画
                g_marker_size(3);
                g_marker(i, j);
                //g_sleep(0.001);
                g_marker_color(G_WHITE); //白のマーカで赤のマーカーを消す
                g_marker(i, j);
                g_marker_type(-1);
                g_marker_color(G_BLUE); //青のマーカーで巣の場所を描画
                g_marker(IMAX / 2, JMAX / 2);
                c[i][j] += 1;
                int r = dice(5); //ここで乱数(0~4)を生成
                //乱数を判定して次の座標を決定
                if (r == 0){
                    i++;
                }
                else if (r == 1){
                    i--;
                }
                else if (r == 2){
                    j++;
                }
                else if (r == 3){
                    j--;
                } //r==4の時はその場に止まる

                //lec9,課題3の条件のはみ出した時の対処(N<IMAX,JMAXの場合ははみ出さないのでいらない)
                if (i < 0)
                {
                    i = IMAX;
                }
                else if (IMAX < i)
                {
                    i = 0;
                }
                else if (j < 0)
                {
                    j = JMAX;
                }
                else if (JMAX < j)
                {
                    j = 0;
                }
                //g_sleep(0.001);
                //最終位置を記録
                if (k == N - 1)
                {
                    x[m - 1] = i;
                    y[m - 1] = j;
                }
            }
        }
        //c配列のなかで一番大きい値を抽出
        for (i = 1; i <= IMAX; i++){
            for (j = 1; j <= JMAX; j++){
                if (i == 1 && j == 1){
                    cmax = c[i][j];
                }
                else if (cmax < c[i][j]){
                    cmax = c[i][j];
                }
            }
        }
        //配列cを正規化して配列dに格納
        for (i = 1; i <= JMAX; i++)
        {
            for (j = 1; j <= IMAX; j++)
            {
                d[i][j] = c[i][j] / (double)cmax;
            }
        }
        /*配列dを描画
        for (i = 1; i <= JMAX; i++)
        {
            for (j = 1; j <= IMAX; j++)
            {
                printf("%3.1f ", d[i][j]);
            }
            printf("\n");
        }*/
        /*念のためm匹の最終位置を表示
        for(int p = 0;p<M;p++){
            printf("%d,%d ",x[p],y[p]);
        }*/

        //正規化された値をz軸方向で表現
        g_hidden(100.0, 100.0, 50.0, 0.0, 1.0, 500.0, 30.0, 35.0, 95.0, 0.0, 100.0, 100.0, (double *)d, IMAX + 1, JMAX + 1, 1, 0, 1, 1);
        g_sleep(0.01);
        g_cls(); //一旦消す

        //帰巣プログラム
        int s = 0;
        int f = 0;
        //初期化
        g_init("GRAPH", 200.0, 100.0);
        g_device(G_DISP);
        g_def_scale(2, -0.5, 2 * (IMAX + 0.5) + 5.0, -0.5, JMAX + 0.5, 10.0, 10.0, 180.0, 80.0); //仮想座標系をもう一度定義
        g_sel_scale(2);
        g_hidden(100.0, 100.0, 50.0, 0.0, 1.0, 500.0, 30.0, 35.0, 95.0, 0.0, 100.0, 100.0, (double *)d, IMAX + 1, JMAX + 1, 1, 0, 1, 1);
        for (int m = 1; m <= M; m++){
            //最終位置
            i = x[m - 1];
            j = y[m - 1];
            int i_0, j_0; //次に動くマスの座標
            int can_move = 1;
            int step;
            int STEP = N;
            g_box(-0.5, IMAX + 0.5, -0.5, JMAX + 0.5, G_YES, G_NO);
            //縦線の描画
            for (int pp = 0; pp < IMAX + 1; pp++)
            {
                g_move(pp - 0.5, -0.5);
                g_plot(pp - 0.5, JMAX + 0.5);
            }
            //横線の描画
            for (int qq = 0; qq < JMAX + 1; qq++)
            {
                g_move(-0.5, qq - 0.5);
                g_plot(IMAX + 0.5, qq - 0.5);
            }
            step = 0;
            while ((i != IMAX / 2 || j != JMAX / 2) && can_move == 1 && step < STEP)
            {
                //蟻の帰巣の描画
                int max_footprint = c[i][j];
                fourway[0] = c[i + 1][j];
                fourway[1] = c[i - 1][j];
                fourway[2] = c[i][j + 1];
                fourway[3] = c[i][j - 1];

                //最大値を取得/バブルソート
                for (int count = 0; count < 5; count++)
                {
                    for (int count_q = 4; count_q > count; count_q--)
                    {
                        if (fourway[count] < fourway[count_q - 1])
                        {
                            //ソート
                            int tmp = fourway[count];
                            fourway[count] = fourway[count_q - 1];
                            fourway[count_q - 1] = tmp;
                        }
                    }
                }
                /*確認のために配列fourwayを出力
                for (int pq = 0; pq < 4; pq++)
                {
                    printf("%d ", fourway[pq]);
                }*/
                max_footprint = fourway[0];

                //ここに配列の最大値の要素が２つ以上ある場合のランダム抽出プログラムをかく
                //下の判定プログラムは最大値が１つのみの場合なので、if文を用いて一つインデントをあげることにする
                if (fourway[0] == fourway[1] && fourway[1] == fourway[2] && fourway[2] == fourway[3]){
                    //maxfootprintと配列の値を照合し、配列の位置を記憶させる
                    if (max_footprint == c[i + 1][j]){
                        i_0 = i + 1;
                        j_0 = j;
                        step += 1;
                    }
                    else if (max_footprint == c[i - 1][j]){
                        i_0 = i - 1;
                        j_0 = j;
                        step += 1;
                    }
                    else if (max_footprint == c[i][j + 1]){
                        i_0 = i;
                        j_0 = j + 1;
                        step += 1;
                    }
                    else if (max_footprint == c[i][j - 1]){
                        i_0 = i;
                        j_0 = j - 1;
                        step += 1;
                    }
                    else{
                        i_0 = i;
                        j_0 = j;
                        can_move = 0;
                    }
                }
                else if (fourway[0] == fourway[1] && fourway[1] == fourway[2]){
                    //maxfootprintと配列の値を照合し、配列の位置を記憶させる
                    if (max_footprint == c[i + 1][j]){
                        i_0 = i + 1;
                        j_0 = j;
                        step += 1;
                    }
                    else if (max_footprint == c[i - 1][j]){
                        i_0 = i - 1;
                        j_0 = j;
                        step += 1;
                    }
                    else if (max_footprint == c[i][j + 1]){
                        i_0 = i;
                        j_0 = j + 1;
                        step += 1;
                    }
                    else if (max_footprint == c[i][j - 1]){
                        i_0 = i;
                        j_0 = j - 1;
                        step += 1;
                    }
                    else{
                        i_0 = i;
                        j_0 = j;
                        can_move = 0;
                    }
                }
                else if (fourway[0] == fourway[1]){
                    //maxfootprintと配列の値を照合し、配列の位置を記憶させる
                    if (max_footprint == c[i + 1][j]){
                        i_0 = i + 1;
                        j_0 = j;
                        step += 1;
                    }
                    else if (max_footprint == c[i - 1][j]){
                        i_0 = i - 1;
                        j_0 = j;
                        step += 1;
                    }
                    else if (max_footprint == c[i][j + 1]){
                        i_0 = i;
                        j_0 = j + 1;
                        step += 1;
                    }
                    else if (max_footprint == c[i][j - 1]){
                        i_0 = i;
                        j_0 = j - 1;
                        step += 1;
                    }
                    else{
                        i_0 = i;
                        j_0 = j;
                        can_move = 0;
                    }
                }
                else{
                    //maxfootprintと配列の値を照合し、配列の位置を記憶させる
                    if (max_footprint == c[i + 1][j]){
                        i_0 = i + 1;
                        j_0 = j;
                        step += 1;
                    }
                    else if (max_footprint == c[i - 1][j]){
                        i_0 = i - 1;
                        j_0 = j;
                        step += 1;
                    }
                    else if (max_footprint == c[i][j + 1]){
                        i_0 = i;
                        j_0 = j + 1;
                        step += 1;
                    }
                    else if (max_footprint == c[i][j - 1]){
                        i_0 = i;
                        j_0 = j - 1;
                        step += 1;
                    }
                    else{
                        i_0 = i;
                        j_0 = j;
                        can_move = 0;
                    }
                }

                //lec9,課題3の条件のはみ出した時の対処
                if (i < 0){
                    i = IMAX;
                }
                else if (IMAX < i){
                    i = 0;
                }
                else if (j < 0){
                    j = JMAX;
                }
                else if (JMAX < j){
                    j = 0;
                }
                g_marker_type(-1);
                g_marker_color(G_RED); //赤のマーカで描画
                g_marker_size(3);
                g_marker(i_0, j_0);
                //g_sleep(0.01);
                g_marker_color(G_WHITE); //白のマーカーで赤のマーカーを消す
                g_marker(i_0, j_0);
                g_marker_type(-1);
                g_marker_color(G_BLUE); //青のマーカーで巣の場所を描画
                g_marker(IMAX / 2, JMAX / 2);
                i = i_0;
                j = j_0;
                //printf("\n");
                //g_sleep(0.001);
            }
            if (can_move == 1 && step < STEP)
            {
                s += 1;
            }
            else
            {
                f += 1;
            }
        }
        double p = ((double)s / (double)(M)) * 100;
        printf("s = %d, f = %d ", s, f);
        printf("p=%lf\n", p);
        rate[list_numeric] = p;
        list_numeric += 1;
    }
    for(i=0;i<100;i++){
        printf("%5.2lf, ",rate[i]);
    }
    g_sleep(G_STOP);
    g_term();
    return 0;
}

//サイコロ関数 n個の値(0~n-1までの値)をランダムに返す.
double dice(int n)
{
    int r;
    double R;
    r = rand();
    R = (double)(r % n);
    return (int)R;
}
