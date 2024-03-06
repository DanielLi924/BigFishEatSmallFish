#include <graphics.h>
#include <conio.h>

bool isPointInsideRectangle(int x, int y, int left, int top, int right, int bottom) {
    return (x >= left && x <= right && y >= top && y <= bottom);
}

void drawButton(int left, int top, int right, int bottom, const char* text) //程序的标准按钮绘制
{
    setfillcolor(LIGHTGRAY);
    bar(left, top, right, bottom);
    rectangle(left, top, right, bottom);
    outtextxy(left + 10, top + 10, text);
}

int main() {
    initgraph(1920,1080);

   
    int button2Left = 50, button2Top = 150, button2Right = 150, button2Bottom = 200;

    
    drawButton(button2Left, button2Top, button2Right, button2Bottom, "History_record");

    bool button1Clicked = false;
    bool button2Clicked = false;

    while (1) {
        if (MouseHit()) {
            MOUSEMSG msg = GetMouseMsg();
            int x = msg.x;
            int y = msg.y;

            if (msg.uMsg == WM_LBUTTONDOWN) {
                // Check if the mouse click is inside button 1
                if (isPointInsideRectangle(x, y, button1Left, button1Top, button1Right, button1Bottom)) {
                    button1Clicked = true;
                    button2Clicked = false;
                }
                // Check if the mouse click is inside button 2
                else if (isPointInsideRectangle(x, y, button2Left, button2Top, button2Right, button2Bottom)) {
                    button2Clicked = true;
                    button1Clicked = false;
                }
            }
            else if (msg.uMsg == WM_LBUTTONUP) {
                // Check if the mouse button is released
                if (button1Clicked) {
                    cleardevice();
                    IMAGE img;
                    loadimage(&img, "D:/Programming/vs2022/Project/BigFishEatSmallFish/image/background.jpg",1920,1080,true);
                    // Display the image
                    putimage(0,0,&img);

                    // Wait for a key press before closing the window
                    _getch();

                    // Close the graphics window
                    closegraph();

                }
                else if (button2Clicked)
                {
                    IMAGE img;
                    loadimage(&img, "D:/Programming/vs2022/Project/BigFishEatSmallFish/image/History_background.jpg", 1920, 1080, true);
                    // Display the image
                    putimage(0, 0, &img);
                }

                // Reset button states
                button1Clicked = false;
                button2Clicked = false;
            }
        }

        Sleep(10);
    }

    closegraph();
    return 0;
}

int starting() //程序的开始界面
{
    int button1Left = 50, button1Top = 50, button1Right = 150, button1Bottom = 100;
    drawButton(button1Left, button1Top, button1Right, button1Bottom, "Login");
    drawButton(button1Left, button1Top, button1Right, button1Bottom, "Sign Up");
    drawButton(button1Left, button1Top, button1Right, button1Bottom, "Exit");
}
