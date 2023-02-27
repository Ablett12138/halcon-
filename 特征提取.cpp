//提取区域1中最大与最小灰度值　　　
min_max_gray (ROI_0, GrayImage, 5, Min1, Max1, Range1)


//提取区域1中灰度值的平均值与偏差　　　　
intensity (Rectangle1, GrayImage, Mean1, Deviation1)


//提取区域中最小灰度值
gray_features (SelectedRegions, Image, 'min',MinDisp)


//提取区域中最大灰度值
gray_features (SelectedRegions, Image, 'max', MaxDisp)


//求区域的旋转最小外接矩形　　　　
smallest_rectangle2 (Regions, Row, Column, Phi, Length1, Length2)


//求平行坐标的最小外接矩形　　
smallest_rectangle1 (Regions, Row1, Column1, Row2, Column2)


//找出每个区域的最大内接圆以及内接圆的中心坐标和半径
inner_circle (Regions, Row, Column, Radius)


//利用面积以及椭圆长轴与短轴的比值特征，将眼睛部分区域提取出来
select_shape (ConnectedRegions, SelectedRegions, ['area','anisometry'], 'and', [100,1], [3000,2]);



/*计算区域中孔的面积*/
area_holes (Regions, Area)



// 计算所有不相连区域的面积和中心点坐标
area_center (Regions, Area, Row, Column)
center:=|Area|
// 获取一个字符串的空间大小
get_string_extents (WindowID, 12345, Ascent, Descent, TxtWidth, TxtHeight)
// 将面积计算结果以字符串形式显示在窗口中
for I := 0 to center-1 by 1
    disp_message (WindowID, Area[I], 'window', Row[I] - TxtHeight / 2, Column[I] - TxtWidth / 2, 'white', 'true')
endfor

