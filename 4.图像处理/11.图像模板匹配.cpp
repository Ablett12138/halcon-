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

///////////////////    采用仿射变换进行标定--灰度模板匹配      ///////////////////
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


/**********************          形状模板匹配             **********************/
*阈值分割
threshold (GrayImage, Regions, 0, 141)

connection(Regions, ConnectedRegions)
*选取区域
select_shape (ConnectedRegions, SelectedRegions, 'area', 'and', 15000, 16000)
*填充区域
fill_up (SelectedRegions, RegionFillUp)

*膨胀些许
dilation_circle (RegionFillUp, RegionDilation, 1.5)

*开运算去除毛刺
opening_circle (RegionDilation, RegionOpening, 1.5)

*截取区域
reduce_domain (GrayImage, RegionOpening, ImageReduced)

*创建形状模板
create_scaled_shape_model (ImageReduced, 5, rad(0), rad(360), 'auto', 0.5, 1.6, 'auto', 'none', 'ignore_global_polarity', 40, 10, ModelID)

*提取模板轮廓
get_shape_model_contours (ModelContours, ModelID, 1)

*显示模板轮廓到模板位置
area_center (ImageReduced, Area, Row, Column)
vector_angle_to_rigid (0, 0, 0, Row, Column, 0, HomMat2D)
affine_trans_contour_xld (ModelContours, ContoursAffineTrans, HomMat2D)
*显示图像
dev_display (Image)
dev_display (ContoursAffineTrans)

*disp_continue_message (WindowHandle, 'black', 'true')
*stop ()

*读取需匹配图像
read_image (Image1, 'D:/机器视觉/halcon_project/形状匹配测试集.png')
rgb1_to_gray (Image1, GrayImage1)
dev_display (GrayImage1)
*匹配模板
find_scaled_shape_model (GrayImage1, ModelID, rad(0), rad(360), 0.8, 1.0, 0.5, 5, 0.5, 'least_squares', 5, 0.8, Row1, Column1, Angle1, Scale1, Score1)

*循环显示匹配出来的模板轮廓
for i :=0 to |Score1|-1 by 1
    hom_mat2d_identity (HomMat2DIdentity)
    hom_mat2d_translate (HomMat2DIdentity, Row1[i], Column1[i], HomMat2DTranslate)
    hom_mat2d_rotate (HomMat2DTranslate, Angle1[i], Row1[i], Column1[i], HomMat2DRotate)
    hom_mat2d_scale (HomMat2DRotate, Scale1[i], Scale1[i], Row1[i], Column1[i], HomMat2DScale)
    *记得采用转换前的轮廓
    affine_trans_contour_xld (ModelContours, ContoursAffineTrans1, HomMat2DScale)
    if (i<|Score1|)
        disp_continue_message (WindowHandle, 'black', 'true')
        dev_display (ContoursAffineTrans1)
        stop ()
    endif
endfor

clear_shape_model (ModelID)
dev_close_window ()

/**********************          形状模板匹配             **********************/
*使用采集助手读取图像
open_framegrabber ('File', 1, 1, 0, 0, 0, 0, 'default', -1, 'default', -1, 'default', 'rings/rings.seq', 'default', -1, 1, FGHandle)
grab_image (ModelImage, FGHandle)
get_image_pointer1 (ModelImage, Pointer, Type, Width, Height)
dev_close_window ()
dev_open_window (0, 0, Width, Height, 'white', WindowHandle)
dev_display (ModelImage)
* 设置显示条件
dev_set_color ('red')
dev_set_draw ('margin')
dev_set_line_width (5)
*生成模版的圆形区域并截取模版
gen_circle (ModelROI, 251, 196, 103)
reduce_domain (ModelImage, ModelROI, ImageROI)
*创建基于金字塔层数的模型表示
inspect_shape_model (ImageROI, ShapeModelImage, ShapeModelRegion, 5, 30)
dev_display (ShapeModelRegion)
*创建基于形状的模版
create_shape_model (ImageROI, 'auto', 0, rad(360), 'auto', 'none', 'use_polarity', 30, 10, ModelID)
get_shape_model_contours (ShapeModel, ModelID, 1)
*循环识别目标图像
for i := 1 to 7 by 1
    *读取图像
    grab_image (SearchImage, FGHandle)
    dev_display (SearchImage)
    *匹配模版
    find_shape_model (SearchImage, ModelID, 0, rad(360), 0.6, 0, 0.55, 'least_squares', 0, 0.8, RowCheck, ColumnCheck, AngleCheck, Score)
    *显示匹配结果
    for j := 0 to |Score| - 1 by 1
        vector_angle_to_rigid (0, 0, 0, RowCheck[j], ColumnCheck[j], AngleCheck[j], MovementOfObject)
        affine_trans_contour_xld (ShapeModel, ModelAtNewPosition, MovementOfObject)
        dev_set_color ('blue')
        dev_display (ModelAtNewPosition)
        dev_set_color ('red')
        affine_trans_pixel (MovementOfObject, -120, 0, RowArrowHead, ColumnArrowHead)
        disp_arrow (WindowHandle, RowCheck[j], ColumnCheck[j], RowArrowHead, ColumnArrowHead, 2)
    endfor
endfor
*清除模版和关闭采集助手
clear_shape_model (ModelID)
close_framegrabber (FGHandle)

