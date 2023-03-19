程序如下：
*关闭窗口
dev_close_window ()
*获取图像
read_image (Image, 'photometric_stereo/embossed_01')
*获得图像尺寸
get_image_size (Image, Width, Height)
*打开适应图像大小的窗口
dev_open_window (0, 0, Width, Height, 'black', WindowHandle1)
*在图像上使用均值滤波器进行适当平滑 
mean_image (Image, ImageMean, 59, 59)
*动态阈值分割，提取圆区域
dyn_threshold (Image, ImageMean, RegionDynThresh, 15, 'not_equal')
* 显示图像
dev_display (Image)
*显示提取区域
dev_display (RegionDynThresh)