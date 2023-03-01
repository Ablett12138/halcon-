/**********************膨胀操作是对所选区域进行“收缩”的一种操作，可以用于消除边缘和杂点。*******************/
*将图像通过阈值处理转化为二值化图像
threshold (GrayImage, Regions, 134, 239)
*使用半径为11的圆形结构膨胀得到区域
dilation_circle (Regions, RegionDilation, 11)
*使用长为13，宽为11的矩形结构元素膨胀得到区域
dilation_rectangle1 (Regions, RegionDilation1, 11, 13)
*生成短轴11，长轴13的椭圆形区域，作为结构元素
gen_ellipse (Ellipse, 100, 100, 0, 13, 11)
*使用生成的椭圆形结构元素膨胀得到区域
dilation1 (Regions, Ellipse, RegionDilation2, 1)
*使用生成的椭圆形结构元素膨胀得到区域（可设置参考点）
dilation2 (Regions, Ellipse, RegionDilation3, 0, 0, 1)



/**********************灰度膨胀**********************/
*对灰度图像进行膨胀操作
gray_dilation_shape (Image, ImageMax, 5, 5, 'octagon')
