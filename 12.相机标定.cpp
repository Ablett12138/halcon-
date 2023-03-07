/**********************          相机标定             **********************/
ImgPath := '3d_machine_vision/calib/'
dev_close_window ()
dev_open_window (0, 0, 652, 494, 'black', WindowHandle)
dev_update_off ()
dev_set_draw ('margin')
dev_set_line_width (3)
set_display_font (WindowHandle, 14, 'mono', 'true', 'false')
* 
* Calibrate the camera.
* 设置相机初始的参数
gen_cam_par_area_scan_division (0.016, 0, 0.0000074, 0.0000074, 326, 247, 652, 494, StartCamPar)
*创建标定数据模型   --参数为：基于标定目标的标定
create_calib_data ('calibration_object', 1, 1, CalibDataID)
*设置相机参数
set_calib_data_cam_param (CalibDataID, 0, [], StartCamPar)

*设置标定版    --caltab_30mm.descr:标定板的描述数据
set_calib_data_calib_object (CalibDataID, 0, 'caltab_30mm.descr')

*设置相片数
NumImages := 10
*Note, we do not use the image from which the pose of the measurement plane can be derived
for I := 1 to NumImages by 1
    *设置标定路径
    read_image (Image, ImgPath + 'calib_' + I$'02d')
    dev_display (Image)
    *提取角点中心
    find_calib_object (Image, CalibDataID, 0, 0, I, [], [])
    *提取角点轮廓信息
    get_calib_data_observ_contours (Caltab, CalibDataID, 'caltab', 0, 0, I)
    dev_set_color ('green')
    dev_display (Caltab)
endfor

*进行相机标定
calibrate_cameras (CalibDataID, Error)
*获取参数
get_calib_data (CalibDataID, 'camera', 0, 'params', CamParam)
* Write the internal camera parameters to a file --保存信息
write_cam_par (CamParam, 'camera_parameters.dat')
*显示信息
Message := 'Interior camera parameters have'
Message[1] := 'been written to file'
disp_message (WindowHandle, Message, 'window', 12, 12, 'red', 'false')
clear_calib_data (CalibDataID)