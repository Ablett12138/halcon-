//////////////////////////////////////////////        代码区          //////////////////////////////////////////////////
//********               概念          **************************************//
pirnt("越亮的点灰度值越大")
1.NumLevels=金字塔层数
2.



//*************************将面积计算结果以字符串形式显示在窗口中　（文字）　
disp_message (WindowHandle, 'A area : ' + Area + ' pixel' , 'window', Row, Column, 'black', 'true')

//***************************     row和colum的概念        ***********************************************//
row=y;    //竖着的
column=x; //横着的

//******************************        标定处理       **************************************//
* 生成一个十字星
gen_cross_contour_xld(Cross, Row, Column, 12, 0.0)

*手动选取区域
draw_region (Region, WindowHandle)
*手动选取矩形坐标
draw_rectangle1 (WindowHandle, Row, Column, Row1, Column1)


//******************************        图片读取及其初始化       **************************************//
*图片初始处理
read_image (Image, 'D:/机器视觉/halcon_project/字母.png')

rgb1_to_gray (Image, GrayImage)

get_image_size (GrayImage, Width, Height)

dev_close_window ()

dev_open_window (0, 0, Width, Height, 'black', WindowHandle)

dev_set_color ('blue')

dev_set_draw ('fill')

*设置字体
set_display_font (WindowHandle, 16, 'mono', 'true', 'false')

*显示F5继续
disp_continue_message (WindowHandle, 'black', 'true')
stop()

/**                  可选部分                     **/
*设置填颜色为12种
dev_set_colored (12)

*设置填充模式为轮廓
dev_set_draw ('margin')

*设置线宽
dev_set_line_width (2)

*输出伪彩色图像
dev_set_lut ('temperature')

*激活已创建的窗口
dev_set_window (WindowHandle1)

*读取图片,依次显示    J$'02'--表示前面路径后图片名称占两位
read_image (Image, 'smd/smd_on_chip_' + J$'02')

*打开自适应图片窗口
dev_open_window_fit_image (GrayImage1, 0, 0, -1, -1, WindowHandle1)

*获取图像信息 --宽和高
get_image_pointer1 (ModelImage, Pointer, Type, Width, Height)

/*******************             图片保存           *************************/
write_image( image , 'bmp' , 0 , 'C:/桌面/1' )

*窗口保存  //带文字,region保存
dump_window_image( image , 20000)   //图像名,窗口句柄
write_image( image , 'bmp' , 0 , 'C:/桌面/1' )

*裁剪后保存,改变尺寸
crop_domain (ImageReduced, ImagePart)
write_image (ImagePart, 'bmp', 0, 'D/img.bmp')


/*******************             3幅图像对比显示           *************************/
*3幅图像对比显示
1.将三张图两两结合在一起
2.最后显示
concat_obj(GrayImage1, ImageOpening ,Images)
concat_obj(Images , ImageTopHat, Images)
tile_images (Images,TiledImages,3, ' horizontal')


//////////////////////////////////////////////概念区//////////////////////////////////////////////////

/*************************          膨胀的定义       ******************************************************/
1.膨胀可以填充图像内部的小孔及图像边缘处的小凹陷部分,并能够磨平图像向外的尖角。
2.图像B经过反射180°后对图像A进行膨胀。 



/*************************          腐蚀的定义      ******************************************************/
1.腐蚀操作是对所选区域进行收缩的一种操作,可以用于消除边缘和杂点。
2.图像B经过反射180°后对图像A进行腐蚀。 




/*************************      开运算的计算步骤---区域操作       ******************************************************/
1.先腐蚀,后膨胀。
2.通过开运算能去除一些孤立的、细小的点,平滑毛糙的边缘线.
3.同时原区域面积也不会有明显的改变,类似于一种去"毛刺"的效果。 



/*************************        闭运算的计算步骤---区域操作        ******************************************/
1.先膨胀,后腐蚀。
2.这两步操作能将看起来很接近的元素,如区域内部的空洞或外部孤立的点连接成一体.
3.区域的外观和面积不会有明显示的改变。



/**********************         击中与击不中原理      **********************/
1.A被B腐蚀。
2.A的补集被B的补集腐蚀.
3.合成以上的两个结果的交集即为所求。




/**********************      灰度腐蚀原理---直接对图像操作     **********************/
1.灰度值腐蚀能够被用来分开相互连接的亮物体和连接支离破碎的暗物体。
2.腐蚀运算是将图像中的像素点赋值为其局部邻域中从度的最小值.
3.因此图像整体灰度值减少,图像中暗的区域变得更暗,较亮的区域被抑制。


/**********************         灰度膨胀原理---直接对图像操作       **********************/
1.腐蚀运算是将图像中的像素点赋值为其局部邻域中从度的最大值.
2.经过灰度图像膨胀操作,较亮的局部区域被"扩大"了
3.而较暗的局部区域被"收缩"了,图像整体变得更亮。



/**********************          灰度开运算和闭运算结果---直接对图像操作         **********************/
1.灰度开运算可以滤掉信号向上的小噪声,且保持信号的基本形状不变,即过滤掉比较亮的点。
2.灰度闭运算可以滤掉信号向下的小噪声,且保持信号的基本形状不变,即过滤掉比较暗的点。




/**********************         顶帽变换原理---直接对图像操作         **********************/
1.顶帽变换:原图像减去开运算的结果。
2.由于开运算可以消除暗背景下的较亮区域,如果用原图像减去开运算结果就可以得到原图中成度较暗的区域,所以又称白顶帽变换。



/**********************         底帽变换原理---直接对图像操作        **********************/
1.底帽变换:闭运算结果减去原图像。
2.由于闭运算可以删除亮度较高背景下的较暗区域,如果用原图像减去闭运算结果就可以得到原图像灰度较暗的区域,所以又称黑底帽变换。




/**********************          边界提取的概念---基于腐蚀        **********************/
1.首先用B对A进行腐蚀为C
2.然后用A-C即为边界


/**********************          孔洞填充的概念---基于膨胀          **********************/
1.孔洞定义:被前景连通域包围的封闭的背景区域,不限于圆形。
2.每个边界包围一个背景区域(即一个孔洞),给定每一个孔洞中一个点。
3.然后从该点开始进行条件膨胀,直至填充整个边界包围的区域。



/**********************         骨骼化的概念             **********************/
1.骨架:一幅图像的骨骼部分,它描述物体的几何形状和拓扑结构。
2.计算骨架的讨程一般称为"细化"或"骨骼化"
3.skeleton (regions, Skeleton)



/**********************          图像模板匹配             **********************/
1.图像模板匹配:在整个图像区域发现与给定子图像匹配的小块区域·
2.灰度、边缘、外形等特征的相似性和一致性


一、灰度模板匹配
1.地位:最经典的模板匹配算法,也是最早提出来的模板匹配算法
2.特征:像素灰度值、灰度梯度
3.适用条件:光照不变
4.常用方法:平均绝对差算法(MAD)绝对误差和算法(SAD)误差平方和算法(SSD) .
5.平均误差平方和算法(MSD)
6.归一化积相关(NCC:Normalized Cross Correlation )
7.序贯相似性检测算法(SSDA)
3.抗干扰性强

二、特征的模板匹配
*不变矩匹配法
1.基本原理：特征匹配是指建立两幅图像中特征点之间对应关系的过程。
2.用数学语言可以描述为： 两幅图像A和B中分别有m和n个特征点(m和n通常不相等)
3.其中有k对点是两幅图像共同拥有的,则如何确定两幅图像中k对相对应的点对即为特征匹配要解决的问题.
4.二阶矩表明图像的方向
特点：
1.由Hu矩组成的特征量对图片进行识别,优点就是速度很快。缺点是识别率比较低。
2.Hu不变矩一般用来识别图像中大的物体,对于物体的形状描述得比较好,图像的纹理特征不能太复杂.
3.像识别水果的形状,或者对于车牌中的简单字符的识别效果会相对好一些。

三、图像金字塔概念
1.图像金字塔是图像多尺度表达的一种,是一种以多分辨率来解释图像的有效但概念简单的结构。
2.广泛应用于图像分割、机器视觉和图像压缩。
3.一幅图像的金字塔是一系列以金字塔形状排列的分辨率逐步降低、且来源于同一张原始图的图像集合。
(1)高斯金字塔：   --有点像图像压缩
    1.从下往上采样,和金字塔由宽变窄.
    2.高斯金字塔是通过高斯平滑和亚采样获得向下采样图像。
    3.对图像G由底层向上,进行高斯内核卷积(平滑的作用);
    4.最后将所有偶数行和列去除。
    5.向下采样,后向上采样后,丢失了很多细节。
(2)拉普拉斯金字塔：
    1.高斯金字塔分别向下和向上采样。
    2.同层分辨率相减,多层叠加起来就是拉普拉斯金字塔。
    3.用高斯金字塔的每一层图像减去其上一层图像上采样并高斯卷积之后的预测图像,
      得到一系列的差值图像,即为拉普拉斯金字塔分解图像。
(3)图像融合：    --适用双目相机的图片拼接
    1.函数调用：
    (1)根据金字塔层数和对比度检查要生成的模板是否合适
    inspect_shape_model(lmage : Modellmages, ModelRegions : NumLevels,Contrast : )
    (2)使用图像创建形状匹配模型
    create_shape_model(Template : : NumLevels, AngleStart, AngleExtent,AngleStep,Optimization,Metric, Contrast, MinContrast : ModellD)
    (3)获取形状模板的轮廓
    get_shape_contours( : ModelContours: ModellD,Level; )


/**********************          相机标定             **********************/
（一）相机标定概念：
    1.成像过程：
        就是三维空间坐标到二维图像坐标的变换,这是一个投影过程（降维、丢失深度信息）。
    2.相机矩阵(camera projection matrix) :
        就是建立这种三维到二维的投影关系。
    3.相机标定指：
        建立相机图像像素位置与场景点位置之间的关系,即求解相机模型的参数。
    4.如何将世界坐标系下的坐标转换到相机坐标系下？ (R|T)

    5.三维到二维丢失了深度信息。

    6.相机畸变：
        (1)像素坐标轴倾斜
        (2)透镜形状缺陷
        (3)组装工艺偏差
    6.1 径向畸变：
        径向畸变主要是由镜头形状缺陷造成的,它又分为枕形畸变和桶形畸变。
    6.2 切向畸变：
        除了透镜的形状会引入径向畸变,在相机的组装过程中由于不能使透镜严格和成像平面平行,会引入切向畸变。
    7.相机标定：
        见概念截取/相机标定
        
(二) 双目立体视觉原理：
    1.人之所以能够感受到立体视觉,是因为人的左右眼之间有6到7cm的间隔,左眼与右眼看到的影像会有细微的差别,所以我们很容易判断物体的远近以及多个物体的前后关系。
     2.双目立体视觉的基本原理与人眼观察世界的方式类似,双目立体视觉获取图像是通过不同位置的两台摄像机或者一台摄像机经过平移或旋转拍摄同一幅场景,来获取立体图像对。

