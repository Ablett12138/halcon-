//********越亮的点灰度值越大**************************************//
pirnt("越亮的点灰度值越大")
//*************************将面积计算结果以字符串形式显示在窗口中　（文字）　
disp_message (WindowHandle, 'A area : ' + Area + ' pixel' , 'window', Row, Column, 'black', 'true')

//***************************row和colum的概念
row=y;    //竖着的
column=x; //横着的


//******************************图片读取及其初始化**************************************//
*图片初始处理
read_image (Image, 'D:/机器视觉/halcon_project/字母.png')

rgb1_to_gray (Image, GrayImage)

get_image_size (GrayImage, Width, Height)

dev_close_window ()

dev_open_window (0, 0, Width, Height, 'black', WindowHandle)

dev_set_color ('blue')

dev_set_draw ('fill')

/**可选部分*/
*设置填颜色为12种
dev_set_colored (12)

*设置填充模式为轮廓
dev_set_draw ('margin')

*设置线宽
dev_set_line_width (2)

*输出伪彩色图像
dev_set_lut ('temperature')



/*************************开运算的计算步骤****************************************************************/
1.先腐蚀，后膨胀。
2.通过开运算能去除一些孤立的、细小的点，平滑毛糙的边缘线.
3.同时原区域面积也不会有明显的改变，类似于一种“去毛刺”的效果。 



/*************************闭运算的计算步骤：*******************************************/
1.先膨胀，后腐蚀。
