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
2.这两步操作能将看起来很接近的元素，如区域内部的空洞或外部孤立的点连接成一体.
3.区域的外观和面积不会有明显示的改变。



/**********************击中与击不中原理**********************/
1.A被B腐蚀。
2.A的补集被B的补集腐蚀.
3.合成以上的两个结果的交集即为所求。




/**********************灰度腐蚀原理---直接对图像操作**********************/
1.灰度值腐蚀能够被用来分开相互连接的亮物体和连接支离破碎的暗物体。
2.腐蚀运算是将图像中的像素点赋值为其局部邻域中从度的最小值.
3.因此图像整体灰度值减少,图像中暗的区域变得更暗,较亮的区域被抑制。


/**********************灰度膨胀原理---直接对图像操作**********************/
1.腐蚀运算是将图像中的像素点赋值为其局部邻域中从度的最大值.
2.经过灰度图像膨胀操作，较亮的局部区域被“扩大”了
3.而较暗的局部区域被“收缩”了，图像整体变得更亮。

