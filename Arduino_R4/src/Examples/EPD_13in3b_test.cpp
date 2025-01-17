/*****************************************************************************
* | File      	:   EPD_13IN3B_test.c
* | Author      :   Waveshare team
* | Function    :   13.3inch e-paper (B) test demo
* | Info        :
*----------------
* |	This version:   V1.0
* | Date        :   2024-04-08
* | Info        :
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documnetation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to  whom the Software is
# furished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#
******************************************************************************/
#include "EPD_Test.h"
#include "../e-Paper/EPD_13in3b.h"

int EPD_13in3b_test(void)
{
    Debug("EPD_13IN3B_test Demo\r\n");
    if(DEV_Module_Init()!=0){
        return -1;
    }

    Debug("e-Paper Init and Clear...\r\n");
	EPD_13IN3B_Init();
    EPD_13IN3B_Clear();


    //Create a new image cache named IMAGE_BW and fill it with white
    UBYTE *Image; // Red or Yellow
    UDOUBLE Imagesize = ((EPD_13IN3B_WIDTH % 8 == 0)? (EPD_13IN3B_WIDTH / 8 ): (EPD_13IN3B_WIDTH / 8 + 1)) * EPD_13IN3B_HEIGHT;
    if((Image = (UBYTE *)malloc(Imagesize/4)) == NULL) {
        Debug("Failed to apply for black memory...\r\n");
        return -1;
    }

    Debug("NewImage:Image\r\n");
    Paint_NewImage(Image, EPD_13IN3B_WIDTH/2, EPD_13IN3B_HEIGHT/2, 0, WHITE);

    //Select Image
    Paint_SelectImage(Image);
    Paint_Clear(WHITE);
	
#if 1   // show bmp
    EPD_13IN3B_Display_Base(gImage_13in3b_b, gImage_13in3b_r);
    DEV_Delay_ms(3000);
#endif

#if 1  // Drawing on the image
    /*Horizontal screen*/
    //1.Draw black image
    EPD_13IN3B_Init();
    Paint_NewImage(Image, EPD_13IN3B_WIDTH/2, EPD_13IN3B_HEIGHT/2, 0, WHITE);
    Debug("Draw black image\r\n");
    Paint_SelectImage(Image);
    Paint_Clear(WHITE);
    Paint_DrawPoint(10, 80, BLACK, DOT_PIXEL_1X1, DOT_STYLE_DFT);
    Paint_DrawPoint(10, 90, BLACK, DOT_PIXEL_2X2, DOT_STYLE_DFT);
    Paint_DrawPoint(10, 100, BLACK, DOT_PIXEL_3X3, DOT_STYLE_DFT);
    Paint_DrawPoint(10, 110, BLACK, DOT_PIXEL_3X3, DOT_STYLE_DFT);
    Paint_DrawLine(20, 70, 70, 120, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
    Paint_DrawLine(70, 70, 20, 120, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);      
    Paint_DrawRectangle(20, 70, 70, 120, BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
    Paint_DrawRectangle(80, 70, 130, 120, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawString_EN(10, 0, "waveshare", &Font16, BLACK, WHITE);    
    Paint_DrawString_CN(130, 20, "微雪电子", &Font24CN, WHITE, BLACK);
    Paint_DrawNum(10, 50, 987654321, &Font16, WHITE, BLACK);
    EPD_13IN3B_Display_WritePicture(Image, 0);
    
    
    //2.Draw red image
    Debug("Draw red image\r\n");
    Paint_SelectImage(Image);
    Paint_Clear(WHITE);
    Paint_DrawCircle(160, 95, 20, BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
    Paint_DrawCircle(210, 95, 20, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawLine(85, 95, 125, 95, BLACK, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
    Paint_DrawLine(105, 75, 105, 115, BLACK, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);  
    Paint_DrawString_CN(130, 0,"你好abc", &Font12CN, BLACK, WHITE);
    Paint_DrawString_EN(10, 20, "hello world", &Font12, WHITE, BLACK);
    Paint_DrawNum(10, 33, 123456789, &Font12, BLACK, WHITE);
    EPD_13IN3B_Display_WritePicture(Image, 1);
    Debug("EPD_Display\r\n");
    DEV_Delay_ms(2000);
#endif

#if 0
	Debug("Partial refresh\r\n");
    EPD_13IN3B_Clear_Base();
    Paint_NewImage(Image, Font20.Width * 7, Font20.Height, 0, WHITE);
    Debug("Partial refresh\r\n");
    Paint_SelectImage(Image);
    Paint_Clear(WHITE);
	
    PAINT_TIME sPaint_time;
    sPaint_time.Hour = 12;
    sPaint_time.Min = 34;
    sPaint_time.Sec = 56;
    UBYTE num = 10;
    for (;;) {
        sPaint_time.Sec = sPaint_time.Sec + 1;
        if (sPaint_time.Sec == 60) {
            sPaint_time.Min = sPaint_time.Min + 1;
            sPaint_time.Sec = 0;
            if (sPaint_time.Min == 60) {
                sPaint_time.Hour =  sPaint_time.Hour + 1;
                sPaint_time.Min = 0;
                if (sPaint_time.Hour == 24) {
                    sPaint_time.Hour = 0;
                    sPaint_time.Min = 0;
                    sPaint_time.Sec = 0;
                }
            }
        }
        Paint_ClearWindows(0, 0, Font20.Width * 7, Font20.Height, WHITE);
        Paint_DrawTime(0, 0, &sPaint_time, &Font20, WHITE, BLACK);
        num = num - 1;
        if(num == 0) {
            break;
        }
		EPD_13IN3B_Display_Partial(Image, 10, 130, 10 + Font20.Width * 7, 130 + Font20.Height);
		DEV_Delay_ms(500);//Analog clock 1s
    }
#endif

	Debug("Clear...\r\n");
    EPD_13IN3B_Init();
    EPD_13IN3B_Clear();
	
    Debug("Goto Sleep...\r\n");
    EPD_13IN3B_Sleep();
    free(Image);
    Image = NULL;
    DEV_Delay_ms(2000);//important, at least 2s
    // close 5V
    Debug("close 5V, Module enters 0 power consumption ...\r\n");
    DEV_Module_Exit();
    return 0;
}

