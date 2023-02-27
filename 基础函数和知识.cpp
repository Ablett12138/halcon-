//将面积计算结果以字符串形式显示在窗口中　（文字）　
disp_message (WindowHandle, 'A area : ' + Area + ' pixel' , 'window', Row, Column, 'black', 'true')

//row和colum的概念
row=y;    //竖着的
column=x; //横着的

//图片初始处理
read_image (Image, 'D:/机器视觉/halcon_project/字母.png')

rgb1_to_gray (Image, GrayImage)

get_image_size (GrayImage, Width, Height)

dev_close_window ()

dev_open_window (0, 0, Width, Height, 'black', WindowHandle)

dev_set_color ('blue')

dev_set_draw ('fill')

//设置填颜色为12种
dev_set_colored (12)

//设置填充模式为轮廓
dev_set_draw ('margin')


//设置线宽
dev_set_line_width (2)

