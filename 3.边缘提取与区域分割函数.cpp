/**************************************分水岭算法**********************/
//对单通道图像进行高斯平滑处理，去除噪声
gauss_filter (Br2, ImageGauss, 3)
//将图像颜色进行反转
invert_image (ImageGauss, ImageInvert)
//对高斯平滑后的图像进行分数岭处理与阈值分割，提取出盆地区域
watersheds (ImageInvert, Basins, Watersheds)
watersheds_threshold (ImageInvert, Basins1,70)


/*************************************Hough变换**********************/
*获得目标区域图像
rectangle1_domain (Image, ImageReduced, 170, 280, 310, 360)
* 用Sobel边缘检测算子提取边缘
sobel_dir (ImageReduced, EdgeAmplitude, EdgeDirection, 'sum_abs', 3)
*设置输出颜色为红色
dev_set_color ('red')
*阈值分割得到图像
threshold (EdgeAmplitude, Region, 55, 255)
* 截取图像
reduce_domain (EdgeDirection, Region, EdgeDirectionReduced)
* 进行Hough变换
hough_lines_dir (EdgeDirectionReduced, HoughImage, Lines, 4, 2, 'mean', 3, 25, 5, 5, 'true', Angle, Dist)
*将霍夫变换提取直线以普通形式描述的输入行存储为区域
gen_region_hline (LinesHNF, Angle, Dist)
*显示图像
dev_display (Image)
*设置输出颜色数目
dev_set_colored (12)
*设置输出填充方式为“轮廓”
dev_set_draw ('margin')
*显示LinesHNF
dev_display (LinesHNF) 
*设置输出填充方式为“填充”
dev_set_draw ('fill')
*显示Lines
dev_display (Lines)


/*************************************区域生长算法**********************/
//对图像进行均值处理，选用circle类型的中值滤波器
median_image (Image, ImageMedian, 'circle', 2, 'mirrored')
//使用regiongrowing算子寻找颜色相近的邻域
regiongrowing (ImageMedian, Regions, 1, 1, 2, 5000)
//对图像进行区域分割，提取满足各个条件的各个独立区域
shape_trans (Regions, Centers, 'inner_center')
connection (Centers, SingleCenters)
//计算出初步提取的区域的中心点坐标
area_center (SingleCenters, Area, Row, Column)
//以均值灰度图像为输入，进行区域增长计算，计算的起始坐标为上一步的各区域中心
regiongrowing_mean (ImageMedian, RegionsMean, Row, Column, 25, 100)


/*************************************亚像素区域提取*************************/

// 对图像进行亚像素区域提取
edges_sub_pix (Image, Edges, 'canny', 2, 12, 22)
// 放大图像用于详细的边缘检查
dev_set_part (160, 250, 210, 300)
dev_display (Edges)

/***********************************canny算法**************************/
//使用canny算法进行边缘提取
edges_image (Image, ImaAmp, ImaDir, 'lanser2', 0.5, 'nms', 12, 22)
//阈值分割
threshold (ImaAmp, Edges, 1, 255)
//骨骼化
skeleton (Edges, Skeleton)
//将骨骼化的区域转化为XLD
gen_contours_skeleton_xld (Skeleton, Contours, 1, 'filter')
//显示XLD
dev_display (Contours)



/***********************************kirsch算子边缘检测***************************/
//用kirsch算子进行边缘检测
kirsch_amp (Image, ImageEdgeAmp)
//进行阈值操作
threshold (ImageEdgeAmp, Region, 70, 255)
//骨骼化操作
skeleton (Region, Skeleton)
//显示图像
dev_display (Image)
//设置输出颜色为红色
dev_set_color ('red')
//显示骨骼图像
dev_display (Skeleton)


/***********************************prewitt算子边缘检测***************************/
//用prewitt算子进行边缘提取
prewitt_amp (Image, ImageEdgeAmp)
//进行阈值操作
threshold (ImageEdgeAmp, Region, 20, 255)
//骨骼化操作
skeleton (Region, Skeleton)
//显示图像
dev_display (Image)
//设置输出颜色为红色
dev_set_color ('red')
//显示骨骼图像
dev_display (Skeleton)



/***********************************动态阈值分割***************************/
*在图像上使用均值滤波器进行适当平滑 
mean_image (Image, ImageMean, 59, 59)
*动态阈值分割，提取圆区域
dyn_threshold (Image, ImageMean, RegionDynThresh, 15, 'not_equal')
* 显示图像
dev_display (Image)
*显示提取区域
dev_display (RegionDynThresh)


/***********************************自动阈值分割***************************/
*自动阈值分割
auto_threshold (Image, Regions, 5)
*显示分割区域
dev_display (Regions)


/***********************************直方图谷底确定阈值分割***************************/
*计算图像的灰度直方图
gray_histo (Image, Image, AbsoluteHisto, RelativeHisto)
histo_to_thresh (RelativeHisto, 8, MinThresh, MaxThresh)
dev_set_colored (12)
threshold (Image, Region, MinThresh[0], MaxThresh[0])
dev_display (Region)


/***********************************sobel算子***************************/
*边缘检测
sobel_amp (Image, EdgeAmplitude, 'sum_abs', 3)
*阈值分割
threshold (EdgeAmplitude, Region, 10, 255)
*提取边缘框架
skeleton (Region, Skeleton)
*显示图片
dev_display (Image)
*设置输出颜色为红色
dev_set_color ('red')
*显示边缘框架
dev_display (Skeleton)