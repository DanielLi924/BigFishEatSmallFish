/*
#include <graphics.h>
#include <conio.h>

bool isPointInsideRectangle(int x, int y, int left, int top, int right, int bottom) {
    return (x >= left && x <= right && y >= top && y <= bottom);
}

void drawButton(int left, int top, int right, int bottom, const char* text) {
    setfillcolor(LIGHTGRAY);
    bar(left, top, right, bottom);
    rectangle(left, top, right, bottom);
    outtextxy(left + 10, top + 10, text);
}

int main() {
    initgraph(640, 480);

    int button1Left = 50, button1Top = 50, button1Right = 150, button1Bottom = 100;
    int button2Left = 50, button2Top = 150, button2Right = 150, button2Bottom = 200;

    drawButton(button1Left, button1Top, button1Right, button1Bottom, "Button 1");
    drawButton(button2Left, button2Top, button2Right, button2Bottom, "Button 2");

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
                    outtextxy(200, 50, "Button 1 Clicked!");
                }
                else if (button2Clicked) {
                    outtextxy(200, 150, "Button 2 Clicked!");
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
*/
/*
#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    // Initialize graphics mode
    initgraph(1920, 1080);  // Adjust the resolution as needed

    // Load PNG image
    IMAGE img;
    loadimage(&img,"C:/Users/Cheng/Desktop/test.jpg");
    // Display the image
    putimage(200, 200, &img);

    // Wait for a key press before closing the window
    _getch();

    // Close the graphics window
    closegraph();

    return 0;
}
*/
#include <graphics.h>
#include <conio.h>

bool isPointInsideRectangle(int x, int y, int left, int top, int right, int bottom) {
    return (x >= left && x <= right && y >= top && y <= bottom);
}

void drawButton(int left, int top, int right, int bottom, const char* text) {
    setfillcolor(LIGHTGRAY);
    bar(left, top, right, bottom);
    rectangle(left, top, right, bottom);
    outtextxy(left + 10, top + 10, text);
}

int main() {
    initgraph(1920,1080);

    int button1Left = 50, button1Top = 50, button1Right = 150, button1Bottom = 100;
    int button2Left = 50, button2Top = 150, button2Right = 150, button2Bottom = 200;

    drawButton(button1Left, button1Top, button1Right, button1Bottom, "Start");
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

