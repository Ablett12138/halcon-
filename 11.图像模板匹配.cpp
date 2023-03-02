/**********************          灰度值模板匹配             **********************/
*选取模板区域
gen_rectangle1 (ROI_0, 67.8852, 66.6982, 158.18, 164.768)

dev_display (ROI_0)

*获取区域大小
smallest_rectangle1 (ROI_0, Row1, Column1, Row2, Column2)

*剪裁模板区域
reduce_domain (GrayImage, ROI_0, ImageReduced)

*创建ncc模板
create_ncc_model (ImageReduced, 'auto', 0.0, 0.0, 'auto', 'use_polarity', ModelID)

*从原图中寻找图形
find_ncc_model (GrayImage, ModelID, 0, 3.14, 0.8, 1, 0.8, 'true', 0, Row, Column, Angle, Score)

*将找到的图像从图中标出来
gen_rectangle1 (Rectangle, Row-(Row2-Row1)/2, Column-(Column2-Column1)/2, Row+(Row2-Row1)/2, Column+(Column2-Column1)/2)

dev_set_draw ('margin')

dev_display (GrayImage)

dev_display (Rectangle)

*显示匹配结果                
dev_display_ncc_matching_results (ModelID, 'green', Row, Column, Angle, 0)

*释放模板空间
clear_ncc_model (ModelID)

///////////////////    采用仿射变换进行标定      ///////////////////
*生成模板区域
gen_circle (ROI_0, 169.629, 194.011, 78.8179)

*截取图像
reduce_domain (GrayImage, ROI_0, ImageReduced)

*计算图像位置
area_center (ROI_0, Area, Row1, Column1)

*创建模板
create_ncc_model (ImageReduced, 'auto', -0.39, 0.79, 'auto', 'use_polarity', ModelID)

*读取拍照的图像
read_image (Image1, 'D:/机器视觉/halcon_project/瓶盖位移.png')

*转化为二值图
rgb1_to_gray (Image1, GrayImage1)

*寻找匹配图像
find_ncc_model (GrayImage1, ModelID, -0.39, 0.79, 0.49, 1, 0.8, 'true', 0, Row, Column, Angle, Score)

*创建仿射变换矩阵
vector_angle_to_rigid (Row1, Column1, 0, Row, Column, Angle, HomMat2D)

*仿射变换
affine_trans_region (ROI_0, RegionAffineTrans, HomMat2D, 'nearest_neighbor')

dev_display (RegionAffineTrans)

*直接显示标定区域
dev_display_ncc_matching_results (ModelID, 'red', Row, Column, Angle, 0)

*清除缓存
clear_ncc_model (ModelID)


