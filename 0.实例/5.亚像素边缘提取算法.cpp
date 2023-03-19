程序如下：
*关闭窗口
dev_close_window ()
*读取图像
read_image (Image, 'fabrik')
*打开适应图像大小的窗口
dev_open_window_fit_image (Image, 0, 0, -1, -1, WindowHandle)
* 对图像进行亚像素区域提取
edges_sub_pix (Image, Edges, 'canny', 2, 12, 22)
* 放大图像用于详细的边缘检查
dev_set_part(160,250,210,300)
dev_display (Image)
dev_display (Edges)
