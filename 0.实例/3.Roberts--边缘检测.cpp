*读取图像
read_image (Image, 'fabrik')
*用Roberts滤波器提取边缘
roberts (Image, ImageRoberts, 'roberts_max')
*进行阈值分割
threshold (ImageRoberts, Region, 9, 255)
*进行区域骨骼化
skeleton (Region, Skeleton)
*显示图像
dev_display (Image)
*设置输出颜色为红色
dev_set_color ('red')
*显示骨骼
dev_display (Skeleton)