/**********************        顶帽变换与底帽运算的计算步骤            *******************/
*生成结构半径为50的圆形结构
gen_disc_se (SE, 'byte', 50, 50, 0)
*对图像进行顶帽运算处理
gray_tophat (GrayImage, SE, ImageTopHat)
*对图像进行底帽运算处理
gray_bothat (GrayImage, SE, ImageBotHat)
