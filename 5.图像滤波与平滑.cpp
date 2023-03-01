/**********************     高通滤波     ***************************/
*得到高通滤波模型
gen_highpass (ImageHighpass, 0.1, 'n', 'dc_center', Width, Height)
*对图像进行傅里叶变换
fft_generic(GrayImage,ImageFFT,'to_freq',-1,'none','dc_center','complex')
*对频率图像进行高通滤波
convol_fft(ImageFFT,ImageHighpass,ImageConvol)
*对得到的频率图像进行傅里叶反变换
fft_generic(ImageConvol,ImageResult,'from_freq',1,'none','dc_center','byte')
*显示图像
dev_display (ImageResult)




/**********************     低通滤波     ***************************/
*获得一个低通滤波模型
gen_lowpass (ImageLowpass, 0.1, 'none', 'dc_center', Width, Height)
*对噪声图像进行傅里叶变换，得到频率图像
fft_generic (Image, ImageFFT, 'to_freq', -1, 'sqrt', 'dc_center', 'complex')
*对频率图像进行低通滤波
convol_fft (ImageFFT, ImageLowpass, ImageConvol)
*对频率图像进行傅里叶变换
fft_generic (ImageConvol, ImageFFT1, 'from_freq',1, 'sqrt', 'dc_center', 'complex') 



/**********************     拉普拉斯算子     ***************************/
*对图像进行拉普拉斯算子处理
laplace (Image, ImageLaplace, 'signed', 3, 'n_8_isotropic')
*显示处理后的图像
dev_display (ImageLaplace)


/**********************     ***********中值滤波***     ******************************/
*添加椒盐噪声
sp_distribution (3, 3, Distribution)
add_noise_distribution (GrayImage, ImageNoise, Distribution)
*中值滤波
median_image (ImageNoise, ImageMedian, 'circle', 3, 'mirrored')
*显示图像
dev_display (ImageMedian)



/**********************     ***********均值滤波***     ******************************/
*添加高斯噪声
gauss_distribution (20, Distribution)
add_noise_distribution (GrayImage, ImageNoise, Distribution)
*均值滤波处理
mean_image (ImageNoise, ImageMean, 5, 5)
*显示图像
dev_display (ImageMean)



/**********************     平滑处理---直方图均衡化     *****************************/
*直方图均衡化
equ_histo_image (GrayImage, ImageEquHisto)



/**********************     灰度值处理     *****************************/
*图像取反
invert_image (GrayImage, ImageInvert)
*增强对比度
emphasize (GrayImage, ImageEmphasize, Width, Height, 2)
*缩放图像灰度值
scale_image (GrayImage, ImageScaled, 1, 100)
*分别显示ImageInvert、ImageEmphasize、ImageScaled
dev_display (ImageInvert)
dev_display (ImageEmphasize)
dev_display (ImageScaled)