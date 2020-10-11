import cv2
import operator
import numpy as np
#from numba import jit
import os
from PIL import Image
from numba import jit
import time
import concurrent.futures

def just_BR_class(left_top_row, left_top_col, right_down_row, right_down_col, case2_BR_lambda):
    area = 0
    for i in range(left_top_row,right_down_row):
        for j in range(left_top_col,right_down_col):
            if (np.array(label[res_key]) == img_segmentation_makeborder[i, j]).all():
                area = area + 1

    if area > ((right_down_row - left_top_row) * (right_down_col - left_top_col) * case2_BR_lambda):
        return True
    else:
        return False

def garbcut_seg(left_top_row, left_top_col, right_down_row, right_down_col,iter, flag_case):
    img_ori_copy = img_ori.copy()
    img_ori_copy_roi = img_ori_copy[(left_top_row - 1):(right_down_row - 1),
                       (left_top_col - 1):(right_down_col -1)]

    mask = np.zeros(img_ori_copy_roi.shape[:2],np.uint8)
    bgdModle = np.zeros((1,65),np.float64)
    fgdModle = np.zeros((1,65), np.float64)
    rect = (1, 1, img_ori_copy_roi.shape[1],img_ori_copy_roi.shape[0])
    cv2.grabCut(img_ori_copy_roi, mask, rect, bgdModle, fgdModle, iter, cv2.GC_INIT_WITH_RECT)
    mask2 = np.where((mask == 2) | (mask == 0), 0, 1).astype('uint8')
    im_res = img_ori_copy_roi * mask2[:, :, np.newaxis]

    im_res_copy = im_res.copy()
    im_res_gray_copy = cv2.cvtColor(im_res_copy, cv2.COLOR_RGB2GRAY)
    ret, img_res_binary = cv2.threshold(im_res_gray_copy, 10, 255, cv2.THRESH_BINARY)
    img_res_binary_makeborder= cv2.copyMakeBorder(img_res_binary,1,1,1,1,cv2.BORDER_CONSTANT,value=0)
    #cv2.imwrite('grabcut_binary_makeborder.jpg', img_res_binary_makeborder)
    contours, hierarchy = cv2.findContours(img_res_binary_makeborder, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

    flag_edge_grab = [[0 for col in range(img_res_binary_makeborder.shape[:2][1])] for row in range(img_res_binary_makeborder.shape[:2][0])]
    max_x = 0
    max_y = 0
    max_w = 0
    max_h = 0

    for i in range(len(contours)):
        x, y, w, h = cv2.boundingRect(contours[i])
        if w * h > max_w * max_h:
            max_x = x
            max_y = y
            max_w = w
            max_h = h

    for i in range(len(contours)):
        x, y, w, h = cv2.boundingRect(contours[i])
        if not(x == max_x and y == max_y and w == max_w and h == max_h):
            for i_grab_not_max in range(y, y + h):
                for j_grab_not_max in range(x, x + w):
                    img_res_binary_makeborder[i_grab_not_max, j_grab_not_max] = 0

    #cv2.imwrite('img_res_binary_res-1.jpg', img_res_binary_makeborder)

    grab_point_num = 0
    grab_in_weight = 0
    if max_w != 0 or max_h != 0:
        flag_grab_for = 1
        for i_grab in range(max_y,max_y+max_h):
            for j_grab in range(max_x,max_x+max_w):
                #print(img_res_binary[i_grab,j_grab])
                if img_res_binary_makeborder[i_grab,j_grab] != 0 and flag_grab_for == 1:
                    grab_edge_weight = cal_circle_edge_weight(i_grab,j_grab,case2_lambda,0,1,img_res_binary_makeborder,flag_edge_grab,left_top_row,left_top_col)
                    #cv2.imwrite('img_res_binary2.jpg', img_res_binary_makeborder)
                    flag_grab_for = 0

        for i_grab in range(max_y,max_y+max_h):
            for j_grab in range(max_x,max_x+max_w):
                if img_res_binary_makeborder[i_grab,j_grab] != 0 :
                    grab_point_num = grab_point_num + 1
                    if img_detec_binary_makeborder_copy[i_grab + left_top_row, j_grab + left_top_col] == 255:
                        grab_in_weight = grab_in_weight + 1

        if (grab_in_weight + grab_edge_weight / grab_point_num) > case2_grabcyt_ratio:
            for i_grab in range(max_y, max_y + max_h):
                for j_grab in range(max_x, max_x + max_w):
                    if img_res_binary_makeborder[i_grab, j_grab] != 0:
                        flag_edge[i_grab + left_top_row][j_grab + left_top_col] = flag_case

def morphology_filter():
    img_detec_binary_copy = img_detec_binary_makeborder_copy.copy()
    left_top_row, left_top_col, right_dowm_row, right_dowm_col = max_cir_rectangle()
    img_detec_binary_copy_roi = img_detec_binary_copy[left_top_row:right_dowm_row, left_top_col:right_dowm_col]

    opening = cv2.morphologyEx(img_detec_binary_copy_roi, cv2.MORPH_OPEN,
                               kernel=mprphological_kernel_Outlier)
    closing = cv2.morphologyEx(opening, cv2.MORPH_CLOSE,
                               kernel=mprphological_kernel_Outlier)

    opening = cv2.morphologyEx(closing, cv2.MORPH_OPEN,
                               kernel=mprphological_kernel_Horizontalline)
    closing = cv2.morphologyEx(opening, cv2.MORPH_CLOSE,
                               kernel=mprphological_kernel_Horizontalline)

    opening = cv2.morphologyEx(closing, cv2.MORPH_OPEN,
                               kernel=mprphological_kernel_Vertiacalline)
    closing = cv2.morphologyEx(opening, cv2.MORPH_CLOSE,
                               kernel=mprphological_kernel_Vertiacalline)
    return closing

def max_cir_rectangle():
    left_top_row = min(edge_positon)[0]
    left_top_col = min(edge_positon, key=lambda x: x[1])[1]

    right_down_row = max(edge_positon)[0]
    right_down_col = max(edge_positon, key=lambda x: x[1])[1]

    return left_top_row,left_top_col,right_down_row,right_down_col

def cal_circle_edge_weight(row_roi, col_roi, circle, temp_key, grab_flag, img=None, flag_edge_grab=None,left_top_row_offset=0,left_top_col_offset=0):
    edge_positon.clear()
    i = circle
    edge_weight_temp = 0
    get_edge(row_roi, col_roi, temp_key, grab_flag, img, flag_edge_grab)
    edge_weight_temp = edge_weight_temp + cal_edge_weight(left_top_row_offset,left_top_col_offset)
    i = i - 1
    if (circle > 1):
        edge_positon_copy = []
        for edge_point in edge_positon:
            edge_positon_copy.append(edge_point)

    while i > 0:
        clear_edge(grab_flag,img)
        edge_positon.clear()
        get_edge(row_roi, col_roi, temp_key, grab_flag, img, flag_edge_grab)
        edge_weight_temp = edge_weight_temp + cal_edge_weight()
        i = i - 1
        try:
            row_roi = edge_positon[1][0]
            col_roi = edge_positon[1][1]
        except IndexError:
            row_roi = -1
            col_roi = -1
            pass
    clear_edge(grab_flag, img)

    if (circle > 1):
        edge_positon.clear()
        for edge_point_copy in edge_positon_copy:
            edge_positon.append(edge_point_copy)

    print("该层边缘点权重：",edge_weight_temp)
    return edge_weight_temp

def clear_edge(grab_flag, img=None):
    if grab_flag == 1:
        for edge_point in edge_positon:
            img[edge_point] = 255
    else:
        for edge_point in edge_positon:
            img_segmentation_makeborder[edge_point][0] = 0
            img_segmentation_makeborder[edge_point][1] = 0
            img_segmentation_makeborder[edge_point][2] = 0

def cal_edge_weight(left_top_row_offset=0,left_top_col_offset=0):
    weight_edge = 0
    count = 0
    for edge_point in edge_positon:
        if img_detec_binary_makeborder[edge_point[0]+left_top_row_offset,edge_point[1]+left_top_col_offset] == 255:
            count = count + 1
            weight_edge = weight_edge + count
        else:
            count = 0
    return weight_edge

def get_edge(row_roi, col_roi,temp_key,grab_flag,img=None,flag_edge_grab=None):
    if grab_flag == 1:
        flag_edge_grab[row_roi][col_roi] = 1
    else:
        flag_edge[row_roi][col_roi] = 1
    i_row = row_roi
    j_col = col_roi
    count = 0
    while ((i_row != -1) and (j_col != -1)):
        edge_positon.append((i_row, j_col))
        k, t = judge_edge(i_row, j_col,temp_key,grab_flag,img,flag_edge_grab)
        i_row = k
        j_col = t
        count = count + 1
    print("边缘点数量：", count)

def judge_edge(row_roi, col_roi,temp_key,grab_flag,img=None,flag_edge_grab=None):
    for neighbor in neighbors:
        dr, dc = neighbor
        new_row = row_roi + dr
        new_col = col_roi + dc
        try:
            if grab_flag == 0:
                if flag_edge[new_row][new_col] == 0:
                    if (np.array(label[temp_key]) == img_segmentation_makeborder[new_row, new_col]).all():
                        if not((np.array(label[temp_key]) == img_segmentation_makeborder[new_row-1, new_col]).all()\
                                and (np.array(label[temp_key]) == img_segmentation_makeborder[new_row + 1, new_col]).all()\
                                and (np.array(label[temp_key]) == img_segmentation_makeborder[new_row, new_col + 1]).all() \
                                and (np.array(label[temp_key]) == img_segmentation_makeborder[new_row, new_col - 1]).all()):
                            flag_edge[new_row][new_col] = 1
                            return new_row, new_col
            else:
                if flag_edge_grab[new_row][new_col] == 0:
                    if not 0 == img[new_row, new_col]:
                        if not(img[new_row-1, new_col] != 0\
                                and img[new_row + 1, new_col] != 0 \
                                and img[new_row, new_col + 1] != 0 \
                                and img[new_row, new_col - 1] != 0):
                            flag_edge_grab[new_row][new_col] = 1
                            return new_row, new_col
        except IndexError:
            print("judge_edge数组越界")
            pass

    return -1,-1

def dynamic_judge_moto_point(in_weight_position):
    for row_roi,col_roi in in_weight_position:
        count_case4_moto_lambda = 0
        for neighbor in neighbors:
            dr, dc = neighbor
            new_row = row_roi + dr
            new_col = col_roi + dc
            try:
                if int(img_ori_gray[new_row-1, new_col]) - int(img_ori_gray[new_row, new_col]) > case4_moto_lambda:
                    count_case4_moto_lambda = count_case4_moto_lambda + 1
            except IndexError:
                print("dynamic数组越界")
                pass
        if count_case4_moto_lambda > case4_moto_num_lambda:
            moto_positon.append((row_roi + 1, col_roi + 1))
        else:
            not_moto_positon.append((row_roi + 1, col_roi + 1))

def not_moto_point_delete():
    for not_moto_point in not_moto_positon:
        img_detec_binary_makeborder_copy[not_moto_point] = 0

def checkfirst(bgr):
    res_key_local = None
    for key in label:
        if (np.array(label[key])==bgr).all():
            res_key_local = key
            break
    return res_key_local

def rename(root_dir):
    file_list = os.listdir(root_dir)
    for name in file_list:
        new_name = name.split('_')[-1]
        os.rename(os.path.join(root_dir,name),os.path.join(root_dir,new_name))

def create_my_cityscpaes_label_colormap():
    colormap=np.zeros([19,3],dtype=int)
    colormap[0]=np.array([ 0,0, 0])
    colormap[1]=np.array([ 128, 0 ,0])
    colormap[2]=np.array([ 64, 0, 0])
    colormap[3]=np.array([ 128 ,128, 0])
    colormap[4]=np.array([ 0, 0, 128])
    colormap[5]=np.array([ 128, 0, 128])
    colormap[6]=np.array([ 0, 128, 128])
    colormap[7]=np.array([ 128, 128, 128])
    colormap[8]=np.array([0, 128, 0])
    colormap[9]=np.array([ 192, 0, 0])
    colormap[10]=np.array([135,206,235])
    colormap[11]=np.array([ 192, 128, 0])
    colormap[12]=np.array([ 64, 0, 128])
    colormap[13]=np.array([ 192, 0, 128])
    colormap[14]=np.array([ 64, 128, 128])
    colormap[15]=np.array([ 192, 128, 128])
    colormap[16]=np.array([ 0, 64, 0])
    colormap[17]=np.array([ 128, 64, 0])
    colormap[18]=np.array([ 255, 255, 0])
    return colormap

def gen_planar(img):
    colormap = create_my_cityscpaes_label_colormap()
    ret = dict()
    height,width=img.shape[0],img.shape[1]
    img = img[: , : , : : -1]
    temp_img = np.ones((height,width,3), np.uint8)* 255
    with concurrent.futures.ProcessPoolExecutor() as executor:
        for idx, color in enumerate(colormap):
            temp_img = np.ones((height,width,3), np.uint8)* 255
            mask = np.all(color == img, axis=-1)
            pixel_num = (mask==True).sum()
            temp_img[np.where(mask[:,:,]==True)] = color
            # r = Image.fromarray(temp_img.astype(np.uint8),'RGB')
            if pixel_num > 0:
                temp_img = cv2.cvtColor(np.asarray(temp_img), cv2.COLOR_RGB2BGR)
                lcc_result = get_lcc(temp_img,idx,color)
                ret[idx] = lcc_result.copy()
            temp_img = np.ones((height,width,3), np.uint8)* 255
    return ret

def get_lcc(test_lcc_img, color_label, color):
    ret = []
    gray_image = cv2.cvtColor(test_lcc_img, cv2.COLOR_RGB2GRAY)
    _, thresh = cv2.threshold(gray_image, 125, 255, cv2.THRESH_BINARY_INV)
    nncomps = cv2.connectedComponentsWithStats(thresh)
    labels = nncomps[1]
    status = nncomps[2]
    for rec in status:
        x = rec[0]
        y = rec[1]
        width = rec[2]
        height = rec[3]
        cv2.rectangle(test_lcc_img, (x,y), (x+width, y+height), (125,125,125), 2)
    instances = len(status) -1
    # 创建一个临时图
    height,width=test_lcc_img.shape[0],test_lcc_img.shape[1]
    temp_img = np.ones((height,width,3), np.uint8) * 255
    with concurrent.futures.ProcessPoolExecutor() as executor:
        for ins in range(1, instances + 1):
            if color_label not in range(11,19) and status[ins][2] <= 5 and status[ins][3] <= 5:
                continue
            temp_img[np.where(labels==ins)] = color
            r = cv2.cvtColor(np.asarray(temp_img), cv2.COLOR_RGB2BGR)
            ret.append(r.copy())
            temp_img = np.ones((height,width,3), np.uint8) * 255
    return ret

@jit
def findfirst(height_segmentation, weight_segmentation, img_segmentation_makeborder):
    for i in range(height_segmentation):
        for j in range(weight_segmentation):
            if img_segmentation_makeborder[i, j][0] != 255:
                return i,j

if __name__ == "__main__":

    a = np.array([[1,2,3],[1,5,6], [2,5,3],[5,3,8]])
    print(np.where(a > 2))
    b = a[a > 2] == 3
    c = [0,2]
    d = np.array(([0,0],[2,2]))
    print(np.where(b))
    print(np.argwhere(a > 2))
    print(np.argwhere(a > 2)[c])
    b = np.argwhere(a > 2)
    for c1, c2 in b:
        print(c1, c2)

    label = {}
    label['road'] = [0, 0, 0]
    label['sidewalk'] = [0, 0, 128]
    label['building'] = [0, 0, 64]
    label['wall'] = [0, 128, 128]
    label['fence'] = [128, 0, 0]
    label['pole'] = [128, 0, 128]
    label['traffic light'] = [128, 128, 0]
    label['traffic sign'] = [128, 128, 128]
    label['terrain'] = [0, 0, 192]
    label['sky'] = [235, 206, 135]
    label['vegetation'] = [0, 128, 0]
    label['person'] = [0, 128, 192]
    label['rider'] = [128, 0, 64]
    label['car'] = [128, 0, 192]
    label['truck'] = [128, 128, 64]
    label['bus'] = [128, 128, 192]
    label['train'] = [0, 64, 0]
    label['motorcycle'] = [0, 64, 128]
    label['bicycle'] = [0, 255, 255]

    label_foreground = ['person', 'rider', 'car', 'truck', 'bus', 'train', 'motorcycle', 'bicycle']
    label_stable_background_C1 = ['road','sidewalk','building','wall','fence','terrain','sky']
    label_stable_background_C2 = ['pole','traffic light','traffic sign']
    label_dynamic_backgrount = ['vegetation']

    # 9邻域
    neighbors = [(-1,-1),(-1,0),(-1,1),(0,1),(1,1),(1,0),(1,-1),(0,-1)]

    #形态学滤波算子
    mprphological_kernel_Outlier = np.array([(0,1,0),(1,1,1),(0,1,0)],np.uint8)
    mprphological_kernel_Horizontalline = np.array([(-1, -1, -1), (2, 2, 2), (-1, -1, -1)],np.uint8)
    mprphological_kernel_Vertiacalline = np.array([(-1,2,-1), (-1,2,-1), (-1,2,-1)],np.uint8)

    #计算case1边缘权重层数
    case1_lambda = 5
    #计算case2边缘权重层数
    case2_lambda = 1

    # case1 运动像素点权重与面积的比值
    case1_segmentation_ratio = 0.4
    # case2 运动像素点权重与面积的比值
    case2_grabcyt_ratio = 0.4
    # case1前景面积大小
    case1_segmentation_area_lambda = 0
    # case1中grabcut迭代次数
    case1_grabcut_iter = 10

    # case2中grabcut迭代次数
    case2_grabcut_iter = 5
    # case2中满足长宽比目标的外接矩形落在对应分割平面的阈值
    case2_BR_lambda = 0.9
    #case2中形态学滤波后长宽比
    case_mprphological_length_width_ratio = 5
    #case2中形态学滤波后面积
    case2_mprphological_area = 49

    # case4中当前像素点与周围像素点的差值
    case4_moto_lambda = 20
    # case4中当前像素点与周围像素点的差值满足阈值的个数
    case4_moto_num_lambda = 3

    path_img = "background/"
    str_img_ori = "input/"
    str_img_det = "det/"
    str_img_seg = "seg/"
    str_img_seg_all = "seg_all/"
    str_res = "res/"

    with concurrent.futures.ProcessPoolExecutor() as executor:
        import time
        files = os.listdir(path_img+str_img_ori)
        # 按数值大小排序
        files.sort(key=lambda item: int(item.split('.')[0]))
        print(files)
        for file in files:
            img_ori = cv2.imread(path_img + str_img_ori + file)
            img_ori_gray = cv2.cvtColor(img_ori, cv2.COLOR_RGB2GRAY)

            file_det = file.split(".")
            img_detec = cv2.imread(path_img + str_img_det + file_det[0] + '.bmp')
            img_detec_gray = cv2.cvtColor(img_detec, cv2.COLOR_RGB2GRAY)
            start = time.time()
            ret, img_detec_binary = cv2.threshold(img_detec_gray, 100, 255, cv2.THRESH_BINARY)
            img_detec_binary_makeborder = cv2.copyMakeBorder(img_detec_binary, 1, 1, 1, 1, cv2.BORDER_CONSTANT,value=0)
            img_detec_binary_makeborder_copy = img_detec_binary_makeborder.copy()

            #初始化输出结果图
            detec_res = np.zeros((img_detec_binary_makeborder.shape[:2][0], img_detec_binary_makeborder.shape[:2][1]), dtype=np.uint8)

            img = cv2.imread(path_img + str_img_seg_all + file_det[0] + '.bmp')
            ret = gen_planar(img)
            for k, v in ret.items():
                for vi in range(len(v)):
                    img_segmentation = v[vi]
                    img_segmentation_makeborder = cv2.copyMakeBorder(img_segmentation, 1, 1, 1, 1, cv2.BORDER_CONSTANT, value=[255,255,255])
                    img_segmentation_gray = cv2.cvtColor(img_segmentation, cv2.COLOR_RGB2GRAY)
                    height_segmentation,weight_segmentation = img_segmentation_makeborder.shape[:2]

                    #用于边缘遍历标记和结果输出
                    flag_edge = np.zeros((height_segmentation, weight_segmentation))

                    res_key = None
                    #用于计算每张分割平面图的面积
                    segmentation_point_num = 0

                    #用于存放边缘点位置
                    edge_positon = []

                    #用于存放vegetation中运动点位置
                    moto_positon = []

                    # 用于存放vegetation中非运动点位置
                    not_moto_positon = []

                    #边缘权重
                    edge_weight = 0
                    #非边缘权重
                    in_weight = 0
                    #分割边缘计算标志位
                    flag_edge_grab = 0   #0代表计算全局分割边缘，1代表计算grabcut边缘值

                    segmentation_point_num = height_segmentation * weight_segmentation - (img_segmentation_makeborder.reshape(-1,3)[:,0] == 255).sum()
                    in_weight_seg_position = img_segmentation_makeborder[:, :, 0] < 255
                    in_weight_det_position = img_detec_binary_makeborder[in_weight_seg_position] == 255

                    in_weight = in_weight_det_position.sum()
                    img_detec_binary_makeborder_copy[img_segmentation_makeborder[:,:,0] < 255] = 0
                    i,j = findfirst(height_segmentation, weight_segmentation,img_segmentation_makeborder)
                    res_key = checkfirst(img_segmentation_makeborder[i,j])

                    if label_foreground.count(res_key):
                        edge_weight = cal_circle_edge_weight(i, j, case1_lambda, res_key,flag_edge_grab)
                        flag_edge[img_segmentation_makeborder[:, :, 0] < 255] = 1
                        if (in_weight + edge_weight / segmentation_point_num) > case1_segmentation_ratio:
                            detec_res[flag_edge == 1] = 255
                    if label_stable_background_C1.count(res_key) or label_dynamic_backgrount.count(res_key):
                        edge_weight = cal_circle_edge_weight(i, j, 1, res_key, flag_edge_grab)
                        left_top_row, left_top_col, right_down_row, right_down_col = max_cir_rectangle()
                        if label_dynamic_backgrount.count(res_key):
                            dynamic_judge_moto_point(np.argwhere(in_weight_seg_position)[in_weight_det_position])

                    if label_stable_background_C1.count(res_key):
                        print("C1")
                        left_top_row, left_top_col, right_down_row, right_down_col = max_cir_rectangle()
                        if (right_down_row - left_top_row > 0) and (right_down_col - left_top_col > 0):
                            closing = morphology_filter()
                            contours, hierarchy = cv2.findContours(closing, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

                            for i in range(len(contours)):
                                x, y, w, h = cv2.boundingRect(contours[i])
                                if w * h > case2_mprphological_area and w / h < case_mprphological_length_width_ratio and h / w < case_mprphological_length_width_ratio:
                                    cv2.rectangle(closing, (x, y), (x + w, y + h), 255, 1)
                                    if just_BR_class(left_top_row + y, left_top_col + x, left_top_row + y + h,
                                                     left_top_col + x + w,
                                                     case2_BR_lambda):
                                        garbcut_seg(left_top_row + y, left_top_col + x, left_top_row + y + h,
                                                    left_top_col + x + w,
                                                    case2_grabcut_iter, 2)
                            detec_res[flag_edge == 2] = 255
                    if label_dynamic_backgrount.count(res_key):
                        print("动态背景")
                        left_top_row, left_top_col, right_down_row, right_down_col = max_cir_rectangle()
                        if (right_down_row - left_top_row > 0) and (right_down_col - left_top_col > 0):
                            not_moto_point_delete()
                            #img_detec_binary_makeborder_copy[not_moto_positon] = 0
                            left_top_row, left_top_col, right_down_row, right_down_col = max_cir_rectangle()
                            contours, hierarchy = cv2.findContours(
                                img_detec_binary_makeborder_copy[left_top_row:right_down_row,
                                left_top_col:right_down_col],
                                cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
                            for i in range(len(contours)):
                                x, y, w, h = cv2.boundingRect(contours[i])
                                if w * h > case2_mprphological_area:
                                    if just_BR_class(left_top_row + y, left_top_col + x, left_top_row + y + h,
                                                     left_top_col + x + w,
                                                     case2_BR_lambda):
                                        garbcut_seg(left_top_row + y, left_top_col + x, left_top_row + y + h,
                                                    left_top_col + x + w,
                                                    case2_grabcut_iter, 3)
                            detec_res[flag_edge == 3] = 255

            respath = path_img + str_res + file
            print("******************************")
            end = time.time()
            print("one iter cost %s s",end-start)
            cv2.imwrite(respath, detec_res)










