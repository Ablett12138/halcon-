/**********************腐蚀操作是对所选区域进行“收缩”的一种操作，可以用于消除边缘和杂点。*******************/
threshold (GrayImage, Regions, 0, 182)
*使用圆形结构元素对区域进行腐蚀
erosion_circle (Regions, RegionErosion, 0.5)
*使用矩形结构元素对区域进行腐蚀
erosion_rectangle1 (Regions, RegionErosion1, 0.5, 0.5)

*生成一个椭圆
gen_ellipse (Ellipse, 100, 100, 0, 0.7, 0.5)

*使用生成的结构元素对区域进行腐蚀（参考点为结构元素中心）
erosion1 (Regions, Ellipse, RegionErosion2, 1)

*用生成的结构元素对区域进行腐蚀操作（可设置参考点位置）---可以改变腐蚀后区域的中心位
erosion2 (Regions, Ellipse, RegionErosion3, 50, 50, 1)




/**********************灰度腐蚀******************************/
*对灰度图像进行腐蚀操作
gray_erosion_shape (Image, ImageMin, 5, 5, 'octagon')




/***********************边界提取的概念---基于腐蚀***************/
*将图像二值化
threshold (Image76, Regions, 76, 255)
*边界提取
boundary (Regions, RegionBorder, 'inner')