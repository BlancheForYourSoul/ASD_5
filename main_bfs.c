#include<windows.h>
#include<string.h>
#include<math.h>
#include "generator.h"
#include "draw.h"
#include "bfs.h"


//Функция окна
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc; //создаём контекст устройства
    PAINTSTRUCT ps; //создаём экземпляр структуры графического вывода
    LOGFONT lf;
    HFONT hFont;
    RECT r;
    HBRUSH hBrush;
    HPEN hPen;

    //Цикл обработки сообщений
    switch(message)
    {
        //сообщение рисования
        case WM_PAINT :
            hdc=BeginPaint(hWnd, &ps);

            int count = 0, floor = 1;
            int **A_cords = create_xy_array(10, 4);
            float x_cord = 500, y_cord = 50;
            while (count != n){
                for(int i = 0; i < floor; i++){
                    //Координата по x
                    if(i == 0){
                        int x = x_cord - half_edge * (floor - 1);
                        A_cords[count][0] = x;
                    } else{
                        A_cords[count][0] = A_cords[count-1][0] + edge;
                    }
                    //Координата по y
                    int y = y_cord;
                    A_cords[count][1] = y;
                    //Номер узла
                    A_cords[count][2] = count + 1;
                    count++;
                }
                floor++;
                y_cord += height;
            }
            double k1 = 1.0 - n3*0.01 - n4*0.005 - 0.15;
            srand(0304);
            int **A = get_matrix(n, k1);
            print_2Darray(A, n);
            struct Graph* graph = createGraph(n);
            //int **A1 = get_edge_matrix(A, n5);

            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    if (i != j && A[i][j] == 1){
                        addEdge(graph, i, j);
                        printf("\nadded %d->%d", i, j);
                    }
                }
            }

            int **routes = bfs(graph, 0);

            char *nn[10] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};

            hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
            SelectObject(hdc, hPen);

            for(int i = 0; i < n; i++){
                for(int j = 0; j < n; j++){
                    if(A[i][j] == 1){
                        Vertex(hdc, A_cords[i][0], A_cords[i][1], nn[i]);
                        if(i == j){
                            continue;
                        } else if (A_cords[i][1] == A_cords[j][1] && fabs(A_cords[i][0]-A_cords[j][0]) != edge){
                            Broken_arrow(hdc, A_cords[i][0], A_cords[i][1], A_cords[j][0], A_cords[j][1]);
                        } else if (fabs(A_cords[i][0]-A_cords[j][0]) == edge && fabs(A_cords[i][1]-A_cords[j][1]) > height){
                            Broken_arrow(hdc, A_cords[i][0], A_cords[i][1], A_cords[j][0], A_cords[j][1]);
                        } else if (fabs(A_cords[i][0]-A_cords[j][0]) == half_edge*3 && fabs(A_cords[i][1]-A_cords[j][1]) > height){
                            Broken_arrow(hdc, A_cords[i][0], A_cords[i][1], A_cords[j][0], A_cords[j][1]);
                        } else {
                            //normal
                            Arrow(hdc, A_cords[i][0], A_cords[i][1], A_cords[j][0], A_cords[j][1]);
                        }
                        Vertex(hdc, A_cords[j][0], A_cords[j][1], nn[j]);
                    }
                }
            }

            hBrush = CreateSolidBrush(RGB(255, 255, 255));
            hPen = CreatePen(PS_SOLID, 3, RGB(132, 56, 214));
            SelectObject(hdc, hPen);
            for(int i = 0; i < n; i++){
                Vertex(hdc, A_cords[i][0], A_cords[i][1], nn[i]);
            }

            for (int k = 1; k <= routes[0][0]; k++){
                int i = routes[0][k], j = routes[1][k];
                printf("%d->%d\n", routes[0][k], routes[1][k]);
                if(i == j){
                    continue;
                } else if (A_cords[i][1] == A_cords[j][1] && fabs(A_cords[i][0]-A_cords[j][0]) != edge){
                    Broken_arrow(hdc, A_cords[i][0], A_cords[i][1], A_cords[j][0], A_cords[j][1]);
                } else if (fabs(A_cords[i][0]-A_cords[j][0]) == edge && fabs(A_cords[i][1]-A_cords[j][1]) > height){
                    Broken_arrow(hdc, A_cords[i][0], A_cords[i][1], A_cords[j][0], A_cords[j][1]);
                } else if (fabs(A_cords[i][0]-A_cords[j][0]) == half_edge*3 && fabs(A_cords[i][1]-A_cords[j][1]) > height){
                    Broken_arrow(hdc, A_cords[i][0], A_cords[i][1], A_cords[j][0], A_cords[j][1]);
                } else {
                    //normal
                    Arrow(hdc, A_cords[i][0], A_cords[i][1], A_cords[j][0], A_cords[j][1]);
                }
                Vertex(hdc, A_cords[i][0], A_cords[i][1], nn[i]);
                Vertex(hdc, A_cords[j][0], A_cords[j][1], nn[j]);
                delay(1);
            }



            ValidateRect(hWnd, NULL);
            EndPaint(hWnd, &ps);
            break;

            //сообщение выхода - разрушение окна
        case WM_DESTROY:
            PostQuitMessage(0); //Посылаем сообщение выхода с кодом 0 - нормальное завершение
            DeleteObject(hPen);
            DeleteObject(hBrush);
            break;

        default:
            return(DefWindowProc(hWnd, message, wParam, lParam)); //освобождаем очередь приложения от нераспознаных
    }
    return 0;
}
