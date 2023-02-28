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






