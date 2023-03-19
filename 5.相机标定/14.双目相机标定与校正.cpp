/**********************          双目相机标定  --与图像校正           **********************/
dev_update_off ()
* Set the image path
ImgPath := '3d_machine_vision/stereo/'
* Read the first images to get their size
I := 0
read_image (ImageL, ImgPath + 'calib_distorted_l_' + I$'03d')
read_image (ImageR, ImgPath + 'calib_distorted_r_' + I$'03d')
* Reopen the windows with an appropriate size
dev_close_window ()
get_image_size (ImageL, WidthL, HeightL)
get_image_size (ImageR, WidthR, HeightR)
dev_open_window (0, 0, WidthL, HeightL, 'black', WindowHandle1)
set_display_font (WindowHandle1, 14, 'mono', 'true', 'false')
dev_open_window (0, WidthL + 12, WidthL, HeightL, 'black', WindowHandle2)
* Set the initial values for the internal camera parameters
*设置相机的内参
gen_cam_par_area_scan_division (0.0125, 0, 7.4e-6, 7.4e-6, WidthL / 2.0, HeightL / 2.0, WidthL, HeightL, StartCamParL)
StartCamParR := StartCamParL
* Create a calibration data model in which all calibration data
* including the image coordinates of the calibration marks and
* the observation poses of the calibration plate will be
* accumulated   2-两个相机  1-只有一个标定板
create_calib_data ('calibration_object', 2, 1, CalibDataID)
set_calib_data_cam_param (CalibDataID, 0, [], StartCamParL)
set_calib_data_cam_param (CalibDataID, 1, [], StartCamParR)
set_calib_data_calib_object (CalibDataID, 0, 'caltab_30mm.descr')
* Start the loop over the calibration images
for I := 0 to 10 by 1
    * Read and display the calibration images
    read_image (ImageL, ImgPath + 'calib_distorted_l_' + I$'03d')
    read_image (ImageR, ImgPath + 'calib_distorted_r_' + I$'03d')
    dev_set_window (WindowHandle1)
    dev_display (ImageL)
    dev_set_window (WindowHandle2)
    dev_display (ImageR)
    * Find the calibration plate and store observations
    * in the calibration data model
    find_calib_object (ImageL, CalibDataID, 0, 0, I, [], [])
    find_calib_object (ImageR, CalibDataID, 1, 0, I, [], [])
    * Visualize the extracted calibration marks and the
    * coordinate system defined by the estimated pose.
    visualize_observation_results (ImageL, CalibDataID, 0, I, WindowHandle1)
    visualize_observation_results (ImageR, CalibDataID, 1, I, WindowHandle2)
    wait_seconds (.2)
endfor
* Perform the actual calibration
calibrate_cameras (CalibDataID, Errors)
* Get the calibrated camera parameters
get_calib_data (CalibDataID, 'camera', 0, 'params', CamParamL)
get_calib_data (CalibDataID, 'camera', 1, 'params', CamParamR)
* Since the left camera is the reference camera for the
* calib data model, the pose of the right camera is its
* pose relative to the left camera
*左相机相对右相机的旋转平移
get_calib_data (CalibDataID, 'camera', 1, 'pose', cLPcR)
* Store the results into files. Here, you can either store the
* individual results
write_cam_par (CamParamL, 'cam_left-125.dat')
write_cam_par (CamParamR, 'cam_right-125.dat')
write_pose (cLPcR, 'pos_right2left.dat')
* or you store the complete camera setup model and thus enable ---或者存储完整的摄像机设置模型，从而启用
* the later access to all contained parameters               ---之后访问所有包含的参数
get_calib_data (CalibDataID, 'model', 'general', 'camera_setup_model', CameraSetupModelID)
write_camera_setup_model (CameraSetupModelID, 'stereo_camera_setup.csm')
* Generate the rectification maps   --生成校正图
gen_binocular_rectification_map (MapL, MapR, CamParamL, CamParamR, cLPcR, 1, 'viewing_direction', 'bilinear', RectCamParL, RectCamParR, CamPoseRectL, CamPoseRectR, RectLPosRectR)
* Read in a stereo image pair, acquired with the stereo camera system,
* which has been calibrated, just now.
read_image (ImageL, ImgPath + 'caliper_distorted_l')
read_image (ImageR, ImgPath + 'caliper_distorted_r')
* Rectify the stereo images and display them
*图像校正
map_image (ImageL, MapL, ImageRectifiedL)
map_image (ImageR, MapR, ImageRectifiedR)
dev_set_window (WindowHandle1)
dev_clear_window ()
dev_display (ImageRectifiedL)
disp_message (WindowHandle1, 'Rectified images', 'window', 12, 12, 'black', 'true')
dev_set_window (WindowHandle2)
dev_clear_window ()
dev_display (ImageRectifiedR)
clear_calib_data (CalibDataID)