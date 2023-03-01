/**********************     灰度共生矩阵的求解     ******************************/
*输出伪彩色图像
dev_set_lut ('temperature')

*创建灰度共生矩阵
gen_cooc_matrix (ROI_0, GrayImage, Matrix, 6, 0)

gen_cooc_matrix (TMP_Region, GrayImage, Matrix1, 6, 0)

*dev_set_lut ('default')

*由灰度共生矩阵得到特征值：能量，相关性，局部均匀性，对比度）
cooc_feature_matrix (Matrix, Energy, Correlation, Homogeneity, Contrast)

cooc_feature_matrix (Matrix1, Energy1, Correlation1, Homogeneity1, Contrast1)

*直接产生纹理特征值，可以选取四个方向的平均方向
cooc_feature_image (ROI_0, GrayImage, 6, 'mean', Energy2, Correlation2, Homogeneity2, Contrast2)