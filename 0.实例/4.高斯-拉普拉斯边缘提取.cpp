程序如下：
*关闭窗口dev_close_window ()
*获取图像read_image (Image, 'mreut')
*获得图像大小get_image_size (Image, Width, Height)
*打开与图像大小相适应的窗口dev_open_window (0, 0, Width, Height, 'black', WindowID)
*设置窗口的字体,14号字,Courier New字体,粗体set_display_font (WindowID, 14, 'mono', 'true', 'false')
*进行高斯-拉普拉斯变换
laplace_of_gauss (Image, ImageLaplace, 5)
*通过提取高斯-拉普拉斯图像上的零交叉点进行边缘检测
zero_crossing (ImageLaplace, RegionCrossing2)
