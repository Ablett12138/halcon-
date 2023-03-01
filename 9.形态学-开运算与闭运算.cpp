/**********************开运算的计算步骤*******************/
*阈值分割
threshold (GrayImage, Regions1, 0, 198)
*以半径为11的圆进行开运算计算
opening_circle (Regions1, RegionOpening,0.5)
*以边长为11的长方形进行开运算
opening_rectangle1 (Regions1, RegionOpening1,1,1)
*生成一个a=11,b=13的椭圆
gen_ellipse (Ellipse, 20, 20, 1.57, 1.8, 1.9)
*通过绘制的图形进行开运算
opening (Regions1, Ellipse, RegionOpening2)
*显示
dev_display (RegionOpening)
dev_display (RegionOpening1)
dev_display (RegionOpening2)


/**********************闭运算的计算步骤*******************/
*阈值分割
threshold (GrayImage, Regions1, 25, 189)
*以半径为11的圆进行开运算计算
closing_circle (Regions1, RegionClosing, 7)
*以边长为11的长方形进行开运算
closing_rectangle1 (Regions1, RegionClosing1, 9, 9)
*生成一个a=11,b=13的椭圆
gen_ellipse (Ellipse, 200, 200, 0, 5, 7)
*通过绘制的图形进行开运算
closing (Regions1, Ellipse, RegionClosing2)
*显示
dev_display (RegionClosing)
dev_display (RegionClosing1)
dev_display (RegionClosing2)


/**********************击中与击不中代码**********************/
threshold (GrayImage, Regions, 0, 44)
*connection (Regions, ConnectedRegions)
*skeleton (ConnectedRegions, Skeleton)
*pruning (Skeleton, RegionPrune, 1)
*fill_up (RegionPrune, RegionFillUp)
*select_shape (RegionFillUp, SelectedRegions, 'area', 'and', 200, 99999)

dev_display (Image)
*dev_display (SelectedRegions)

smallest_rectangle1 (Regions, Row1, Column1, Row2, Column2)

gen_rectangle1 (Rectangle, Row1, Column1, Row2, Column2)

gen_circle (Circle, Row1, Column1, 1)
gen_circle (Circle2, Row2, Column2, 2)

hit_or_miss (Regions, Circle, Circle2, RegionHitMiss, Row1, Column1)


/**********************灰度开运算与闭运算**********************/
*对灰度图像进行开运算操作
gray_opening_shape (Image, ImageOpening, 5, 5, 'octagon')
*对灰度图像进行闭运算操作
gray_closing_shape (Image, ImageClosing, 5, 5, 'octagon')

