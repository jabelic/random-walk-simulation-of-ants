

//足跡の数が重なった時の判定の処理
//まず、４つの方向の足跡の数の最大値を出して、その最大値より現在の位置の足跡の数の方が大きかった場合は動かない。
//その後、サイコロを回してサイコロの目に応じて４方向のうちの一つと数を参照して、現在の位置の足跡数以上であった場合はそこに移動して、
//そうでなかった場合は再帰させてもう一回サイコロを回す。この時、最大値を出して現在の位置の足跡数と比較判定しているのでsegmentation fault:11にはならない。


#include <stdio.h>
#include <glsc.h>
#include <stdlib.h>

#define N 10    //蟻の歩数
#define IMAX 20
#define JMAX 20
#define M 20    //蟻の数
#define X_FEED 9 //餌の位置のx座標
#define Y_FEED 6  //餌の位置のy座標
int dice();     //サイコロ関数
void DeterminingTheHomingDirection();    //次に帰巣する方向を決める関数
void AntFootprintStamp();   //蟻の動きを描画する関数
void InitializeDrawingScreen();  //描画画面の初期化,仮想座標系の定義を添えて.
void DrawingGridAntsMove();   //蟻が動く格子の描画


int main(void){
    int i, j, S, cmax;
    int c[IMAX + 1][JMAX + 1] = {};
    double d[IMAX + 1][JMAX + 1] = {}; //配列cを正規化した値を格納する配列
    int x[M] = {}, y[M] = {};          //蟻の最終位置を記録する配列
    int fourway[4] = {};               //最終位置の周りのマスの足跡の数を格納する配列
    int AntFindFeed[M] = {}; //餌を見つけた蟻であれば,1.それ以外は0.

    printf("シード値(自然数)を入力:");
    scanf("%d", &S); //乱数
    srand(S);

    InitializeDrawingScreen();   //描画画面の初期化,仮想座標系の定義を添えて.

    DrawingGridAntsMove();    //蟻の動くマスの横線と縦線の描画とboxの定義

    //m匹のプログラム
    for (int m = 0; m < M; m++){
        //i,jの初期値の設定
        i = IMAX / 2;
        j = JMAX / 2;
        for (int k = 0; k < N; k++){

            AntFootprintStamp(i, j);//蟻の動きを描画する関数

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
            }//r==4の時はその場に止まる。
            //lec9,課題3の条件のはみ出した時の対処
            if (i < 0 && j < 0){
                i = IMAX+1;
                j = JMAX+1;
            }
            else if (i < 0 && j > JMAX+1){
                i = IMAX+1;
                j = 0;
            }
            else if (i > IMAX+1 && j > JMAX+1){
                i = 0;
                j = 0;
            }
            else if (i > IMAX+1 && j < 0){
                i = 0;
                j = JMAX+1;
            }
            else if (i < 0){
                i = IMAX+1;
            }
            else if (IMAX+1 < i){
                i = 0;
            }
            else if (j < 0){
                j = JMAX+1;
            }
            else if (JMAX+1 < j){
                j = 0;
            }

            if(i == X_FEED && j == Y_FEED){
                x[m] = i;
                y[m] = j;
                AntFindFeed[m] += 1;
                break;
            }
            //g_sleep(0.01);
            //最終位置を記録
            if (k == N - 1){
                x[m] = i;
                y[m] = j;
            }
        }
    }
    //c配列のなかで一番大きい値を抽出
    cmax = c[0][0]; 
    for (i = 0; i <= IMAX; i++){
        for (j = 0; j <= JMAX; j++){
            if (cmax < c[i][j])
                cmax = c[i][j];
        }
    }
    //配列cを正規化して配列dに格納
    for (i = 0; i <= JMAX; i++){
        for (j = 0; j <= IMAX; j++){
            d[i][j] = c[i][j] / (double)cmax;
        }
    }
    //配列dを表示
    for (i = 0; i <= JMAX; i++){
        for (j = 0; j <= IMAX; j++){
            printf("%3.1f ", d[i][j]);
        }
        printf("\n");
    }

    //正規化された値をz軸方向で表現
    g_hidden(100.0, 100.0, 50.0, 0.0, 1.0, 500.0, 30.0, 35.0, 95.0, 0.0, 100.0, 100.0, (double *)d, IMAX + 1, JMAX + 1, 1, 0, 1, 1);
    g_sleep(0.01);
    g_cls(); //一旦消す

    //帰巣プログラム
    int s = 0;
    int f = 0;
    
    InitializeDrawingScreen();//描画画面の初期化,仮想座標系の定義を添えて.
    g_hidden(100.0, 100.0, 50.0, 0.0, 1.0, 500.0, 30.0, 35.0, 95.0, 0.0, 100.0, 100.0, (double *)d, IMAX + 1, JMAX + 1, 1, 0, 1, 1);
    for (int m = 0; m < M; m++){ 
        
        //最終位置
        i = x[m];
        j = y[m];

        int i_0, j_0; //次に動くマスの座標
        int can_move = 1;//１のままだと動ける.0になると蟻は動けない.
        int step;
        int STEP = N;

        DrawingGridAntsMove();
        
        step = 0;
        
        while ((i != IMAX / 2 || j != JMAX / 2) && can_move == 1 && step < STEP){

            int max_footprint = c[i][j];
            fourway[0] = c[i + 1][j];
            fourway[1] = c[i - 1][j];
            fourway[2] = c[i][j + 1];
            fourway[3] = c[i][j - 1];
            //最大値を取得/バブルソート
            for (int count = 0; count < 5; count++){
                for (int count_q = 4; count_q > count; count_q--){
                    if (fourway[count] < fourway[count_q - 1]){
                        //ソート
                        int tmp = fourway[count];
                        fourway[count] = fourway[count_q - 1];
                        fourway[count_q - 1] = tmp;
                    }
                }
            }

            i_0 = i; //値の初期化
            j_0 = j; //値の初期化
            if(i == X_FEED && j == Y_FEED){//帰る途中に餌を見つけたらAntFindFeed+=1。
                AntFindFeed[m] += 1;
            }

            //次に帰巣する方向を決める関数
            DeterminingTheHomingDirection(&step, &can_move, &i_0, &j_0, c[i + 1][j], c[i - 1][j], c[i][j + 1], c[i][j - 1], max_footprint, i, j, fourway[0]);

            //lec9,課題3の条件のはみ出した時の対処
            if (i < 0 && j < 0){
                i = IMAX+1;
                j = JMAX+1;
            }
            else if (i < 0 && j > JMAX+1){
                i = IMAX+1;
                j = 0;
            }
            else if (i > IMAX+1 && j > JMAX+1){
                i = 0;
                j = 0;
            }
            else if (i > IMAX+1 && j < 0){
                i = 0;
                j = JMAX+1;
            }
            else if (i < 0){
                i = IMAX+1;
            }
            else if (IMAX+1 < i){
                i = 0;
            }
            else if (j < 0){
                j = JMAX+1;
            }
            else if (JMAX+1 < j){
                j = 0;
            }

            AntFootprintStamp(i, j);//蟻の動きを描画する関数

            i = i_0;
            j = j_0;
        }
        if (can_move == 1 && step < STEP){
            s += 1;
        }
        else{
            f += 1;
        }
    }
    double p = ((double)s / (double)(M)) * 100;
    printf("s = %d, f = %d ", s, f);
    printf("p=%lf％,", p);
    int AntCouldEet=0;
    for(int a = 0 ; a < M ; a ++){
        AntCouldEet += AntFindFeed[a];
    }
    printf("餌にありつけた蟻の数は%d匹\n", AntCouldEet);
    g_sleep(G_STOP);
    g_term();
    return 0;
}

//サイコロ関数 n個の値(0~n-1までの値)をランダムに返す.
int dice(int n){
    return (int)(rand() % n);
}

//次に帰巣する方向を決める関数
void DeterminingTheHomingDirection(int *step, int *can_move, int *i_0, int *j_0, int iplus_j, int iminus_j, int i_jplus, int i_jminus, int max_footprint, int i, int j, int fourWayMax){
    if (max_footprint > fourWayMax){
        *i_0 = i;
        *j_0 = j;
        *can_move = 0;
    }
    int foot_pro = dice(4);
    switch (foot_pro){
        case 0:
            if (max_footprint <= iplus_j){
                *i_0 = i + 1;
                *j_0 = j;
                *step += 1;
            }
            break;
        case 1:
            if (max_footprint <= iminus_j){
                *i_0 = i - 1;
                *j_0 = j;
                *step += 1;
            }
            break;
        case 2:
            if (max_footprint <= i_jplus){
                *i_0 = i;
                *j_0 = j + 1;
                *step += 1;
            }
            break;
        case 3:
            if (max_footprint <= i_jminus){
                *i_0 = i;
                *j_0 = j - 1;
                *step += 1;
            }
            break;
        
        default://ここで再帰
            DeterminingTheHomingDirection(step, can_move, i_0, j_0, iplus_j, iminus_j, i_jplus, i_jminus, max_footprint, i, j,fourWayMax);
    }
}

void DrawingGridAntsMove(){
    g_box(-0.5, IMAX + 0.5, -0.5, JMAX + 0.5, G_YES, G_NO);
        //縦線の描画
    for (int pp = 0; pp < IMAX + 1; pp++){
        g_move(pp - 0.5, -0.5);
        g_plot(pp - 0.5, JMAX + 0.5);
    }
        //横線の描画
    for (int qq = 0; qq < JMAX + 1; qq++){
        g_move(-0.5, qq - 0.5);
        g_plot(IMAX + 0.5, qq - 0.5);
    }
}

void AntFootprintStamp(int iStamp, int jStamp){
    g_marker_type(-1);
    g_marker_color(G_RED); //赤のマーカーで蟻を描画
    g_marker_size(3);
    g_marker(iStamp, jStamp);
    //g_sleep(0.005);
    g_marker_color(G_WHITE); //白のマーカーで赤のマーカーを消去
    g_marker(iStamp, jStamp);
    g_marker_type(-1);
    g_marker_color(G_BLUE); //青のマーカーで巣の場所を描画
    g_marker(IMAX / 2, JMAX / 2);
    g_marker_color(G_GREEN);
    g_marker(X_FEED,Y_FEED); //餌の位置を描画
}

void InitializeDrawingScreen(){
    g_init("GRAPH", 200.0, 100.0);
    g_device(G_DISP);
    g_def_scale(1, -0.5, 2 * (IMAX + 0.5) + 5.0, -0.5, JMAX + 0.5, 10.0, 10.0, 180.0, 80.0);
    g_sel_scale(1);
}