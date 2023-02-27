/***************************************************二维码矫正*********************************************/
dev_open_window_fit_image (Image, 0, 0, -1, -1, WindowHandle)
dev_set_color ('red')
dev_set_line_width (2)
X := [163,280,362,75]
Y := [125,120,361,340]
gen_cross_contour_xld (Crosses, X, Y, 6, 0.78)
dev_display (Image)
dev_display (Crosses)
hom_vector_to_proj_hom_mat2d (X, Y, [1,1,1,1], [75,360,360,75], [110,110,360,360], [1,1,1,1], 'normalized_dlt', HomMat2D)
projective_trans_image (Image, Image_rectified, HomMat2D, 'bilinear', 'false', 'false')


/***************************************************仿射变换--位姿变换*********************************************/
threshold (GrayImage, Regions, 200, 255)
area_center (Regions, Area, Row, Column)
hom_mat2d_identity (HomMat2DIdentity)
hom_mat2d_translate (HomMat2DIdentity, Height/2-Row, Width/2-Column, HomMat2DTranslate)
affine_trans_image (GrayImage, ImageAffinTrans, HomMat2DTranslate, 'constant', 'false')
hom_mat2d_rotate (HomMat2DIdentity, 3.14/2, Height/2, Width/2, HomMat2DRotate)
affine_trans_image (ImageAffinTrans, ImageAffinTrans1, HomMat2DRotate, 'constant', 'false')
hom_mat2d_scale (HomMat2DIdentity, 1.5, 1.5, Height/2, Width/2, HomMat2DScale)
affine_trans_image (ImageAffinTrans1, ImageAffinTrans2, HomMat2DScale, 'constant', 'false')


/***************************************************图形放大--ROI分割*********************************************/
read_image (Clip, 'clip')
*把一个图像缩放到指定比例大小
zoom_image_factor (Clip, ImageZoomed, 0.5, 0.5, 'constant')
*获得图像尺寸
get_image_size (ImageZoomed, Width, Height)
*新建显示窗口，适应图像尺寸
dev_open_window (0, 0, Width, Height, 'black', WindowID)
dev_display (ImageZoomed)
*输入矩形长轴针对水平方向的角度
phi := 1.91
*输入矩形中心点的y值坐标、x值坐标
Row := 134
Column := 118
*选择ROI
gen_rectangle2 (Rectangle, Row, Column,phi, 19, 55)
*从原图中分割出ROI
reduce_domain (ImageZoomed, Rectangle, ImageReduced)
*显示分割后的ROI图像
dev_display (ImageReduced)