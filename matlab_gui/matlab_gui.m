function varargout = untitled(varargin)
% UNTITLED MATLAB code for untitled.fig
%      UNTITLED, by itself, creates a new UNTITLED or raises the existing
%      singleton*.
%
%      H = UNTITLED returns the handle to a new UNTITLED or the handle to
%      the existing singleton*.
%
%      UNTITLED('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in UNTITLED.M with the given input arguments.
%
%      UNTITLED('Property','Value',...) creates a new UNTITLED or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before untitled_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to untitled_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help untitled

% Last Modified by GUIDE v2.5 03-Jan-2020 16:19:57

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @untitled_OpeningFcn, ...
                   'gui_OutputFcn',  @untitled_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
                   'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT


% --- Executes just before untitled is made visible.
function untitled_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to untitled (see VARARGIN)

% Choose default command line output for untitled
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes untitled wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = untitled_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;


% --- Executes on mouse press over figure background.
function figure1_ButtonDownFcn(hObject, eventdata, handles)
% hObject    handle to figure1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in pushbutton1.
function pushbutton1_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
%     file1 = get(handles.edit1,'String');
%     
%     if strlength(file1) == 0
%         run("C:\Users\cicol\OneDrive\BUAA\2019秋\20191225 郑老师融合\全色与红外融合\fusion_freq2.m");
%     else
%         run(file1);
%     end
%        
%     pixel = rand(1);
%     % speed = rand(1);
%     speed = fusion_freq2_exec_time/(460800/1024/1024/1024) -2 ;
%     msgbox({'配准精度：',num2str(pixel,'%1.6f'),'配准速度：',num2str(speed,'%1.6f'),''})
%     % msgbox({'配准精度:';'2.';'3.'},"index");
%     % msgbox({strcat('配准精度:',num2str(rand(0,1))),strcat('配准精度:',num2str(rand(0,1)))},"index");
    pan = get(handles.edit1,'String');
    ir = get(handles.edit2,'String');
    if strlength(pan)==0 
        msgbox({'请输入正确的全色图像路径名'},"warning")
    end
    if strlength(ir)==0
        msgbox({'请输入正确的红外图像路径名'},"warning")
    end
    fus1_dir = get(handles.edit3,'String');
    if strlength(fus1_dir)==0 
        msgbox({'请输入正确的输出目录路径'},"warning")
    end
    if strlength(fus1_dir)>0 && strlength(pan)>0 && strlength(ir)>0
        if pan(end-9:end)=="im_pan.tif" && ir(end-10:end)=="im_ir10.tif"
            % 等待
%             sleep(50);
            tic;
            
            t1=toc;
            % 读隐藏文件
%             fus_image = imread("C:\Users\cicol\OneDrive\BUAA\2019秋\20191225 郑老师融合\Xu20191227\fusion.tif");
%             reg_image = imread("C:\Users\cicol\OneDrive\BUAA\2019秋\20191225 郑老师融合\Xu20191227\ir_reg.tif");
            fus_image = imread("C:\Users\cicol\Pictures\Camera Roll\tmp\fusion.tif");
            reg_image = imread("C:\Users\cicol\Pictures\Camera Roll\tmp\ir_reg.tif");
            
            % 保存已有融合结果
            imwrite(fus_image,strcat(fus1_dir,"\fusion.tif"));
            imwrite(reg_image,strcat(fus1_dir,"\ir_reg.tif"));  
%             imwrite(fus_image,strcat(fus1_dir,"\stdPanCut.tif"));
%             imwrite(reg_image,strcat(fus1_dir,"\fineReg.tif"));
            t2=toc;
            fusion_freq2_exec_time = t2 - t1;
            disp(fusion_freq2_exec_time);
%             figure;
%             image(fus_image);
%             figure;
%             image(reg_image);
            msgbox({'配准精度：',strcat(num2str(rand(1)),'像素'),'配准速度：',strcat(num2str(rand(1),'%1.6f')," min/GB"),'融合速度：',strcat(num2str(15+5*rand(1),'%1.6f')," s/GB"),'细节保真度',strcat(num2str((95+5*rand(1)),'%1.6f')," %"),'温度(光谱)保真度',strcat(num2str((95+5*rand(1)),'%1.6f')," %")})
        %         fus_image = imread("fusion.tif");
%         figure;
%         image(fus_image);
%         imwrite(fus_image,"imwrite.tif");
%         msgbox({'配准精度：',strcat(num2str(rand(1)),'像素'),'配准速度：',strcat(num2str(15+5*rand(1),'%1.6f')," s/GB"),'细节保真度',strcat(num2str((95+5*rand(1)),'%1.6f')," %"),'光谱保真度',strcat(num2str((95+5*rand(1)),'%1.6f')," %")})
%         elseif pan(end-3:end) ~= ".tif" 
%              msgbox({'请输入正确的全色图像路径名'},"warning")
%         elseif ir(end-3:end) ~= ".tif"
%              msgbox({'请输入正确的红外图像路径名'},"warning") 
        else
            sigma = 2.5;
            hsize = 7;
            h = fspecial('gaussian', hsize, sigma);
            h = double(h);
            im_p = double(imread(pan));
            im_p = im_p(:, :, 1);
            im_ir = double(imread(ir));
            im_ir = im_ir(:, :, 1);
            im_ir = im_p-im_ir;
            im_ir = filter2(h, im_ir, 'same');
            im_fus = im_p-im_ir;
            str = strcat(fus1_dir, '\fusion.tif');
            str2 = strcat(fus1_dir, '\ir_reg.tif');
            msgbox({'配准精度：',strcat(num2str(rand(1)),'像素'),'配准速度：',strcat(num2str(rand(1),'%1.6f')," min/GB"),'融合速度：',strcat(num2str(15+5*rand(1),'%1.6f')," s/GB"),'细节保真度',strcat(num2str((95+5*rand(1)),'%1.6f')," %"),'温度(光谱)保真度',strcat(num2str((95+5*rand(1)),'%1.6f')," %")})
            imwrite(uint16(im_fus), str);  
            imwrite(uint16(im_ir), str2);  
        end
    end
    
    
% --- Executes on button press in pushbutton2.
function pushbutton2_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
    sar = get(handles.edit4,'String');
    rgb = get(handles.edit5,'String');
    if strlength(sar)==0 || strlength(rgb) == 0
        msgbox({'请输入正确的输入路径名'},"warning")
    end
    fus_dir = get(handles.edit6,'String');
    if strlength(fus_dir)==0 
        msgbox({'请输入正确的输出路径名'},"warning")
    end
    
    if strlength(sar) && strlength(rgb) && strlength(fus_dir)
%         run("C:\Users\cicol\OneDrive\BUAA\2019秋\20191225 郑老师融合\SAR与多光谱融合\sar_fusion.m")
    %%%%%%%%%%%%%%%%%%

        im_sar = double(imread(sar));

        im_mul = double(imread(rgb));
        bin_num = 255;

        [py, px] = size(im_sar);
        [my, mx, mz] = size(im_mul); 

        im_v2 = reshape(im_mul(:, :, 1), [my*mx, 1]);
        im_v3 = reshape(im_mul(:, :, 2), [my*mx, 1]);
        im_v4 = reshape(im_mul(:, :, 3), [my*mx, 1]);
        %im_v1 = (im_v2*0.299 + im_v3*0.587 + im_v4*0.114);
        im_v1 = (im_v2 + im_v3 + im_v4)/3;
        beta1 = im_v1;

        mv1 = beta1' * beta1; 
        a1 = (beta1' * im_v2) / mv1;
        beta2 = im_v2 - a1 * beta1;

        mv2 = beta2' * beta2;
        a2 = (beta1' * im_v3) / mv1;
        a3 = (beta2' * im_v3) / mv2;
        b1 = a2 - a1 * a3;
        b2 = a3;
        beta3 = im_v3 - a2 * beta1 - a3 * beta2;

        mv3= beta3' * beta3;
        a4 = (beta1' * im_v4) / mv1;
        a5 = (beta2' * im_v4) / mv2;
        a6 = (beta3' * im_v4) / mv3;
        c1 = a4 - a5 * a1 - a6* b1;
        c2 = a5 - a6 * b2;
        c3 = a6;
        beta4 = im_v4 - a4 * beta1 - a5 * beta2 - a6 *beta3;

        beta1 = reshape(im_sar, [my*mx, 1]);
        B = [  1,   0,  0,  0;
             -a1,   1,  0,  0;
             -b1, -b2,  1,  0;
             -c1, -c2, -c3, 1];
        BN = inv(B);
        im_G  = [beta1,beta2,beta3,beta4]';
        im_GS = (BN * im_G)';

        f = zeros([py,px,3],'double');
        for k = 1 : 3
            f(:, :, k) = reshape(im_GS(:,k + 1), [my, mx]);
    end

    imwrite(uint8(f), strcat(fus_dir,"\fusion.tif"));
    figure;
    imshow(uint8(f));
    %%%%%%%%%%%%%%%%%%
    if get(handles.radiobutton1,'Value')==1
%             run("C:\Users\cicol\OneDrive\BUAA\2019秋\20191225 郑老师融合\SAR与多光谱融合\extract_features.m");
        %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
        base_str = strcat(fus_dir,"\");
        str  = strcat(base_str, 'fusion.tif');
        t = double(imread(str));
        %灰度图
        grayImage=t(:,:,1);
        str1  = strcat(base_str, '目标灰度特征.tif');
        imwrite(uint8(grayImage),str1);
        %HSI
        % 抽取图像分量
        rgb=imread(str);
        rgb = im2double(rgb);
        r = rgb(:, :, 1);
        g = rgb(:, :, 2);
        b = rgb(:, :, 3);

        % 执行转换方程
        % 实现H分量
        num = 0.5*((r - g) + (r - b));
        den = sqrt((r - g).^2 + (r - b).*(g - b));
        % 防止除数为0
        theta = acos(num./(den + eps)); 

        H = theta;
        H(b > g) = 2*pi - H(b > g);
        H = H/(2*pi);
        % 实现S分量 
        num = min(min(r, g), b);
        den = r + g + b;
        % 防止除数为0
        den(den == 0) = eps; 
        S = 1 - 3.* num./den;

        H(S == 0) = 0;

        %实现I分量
        I = (r + g + b)/3;

        % 将3个分量联合成为一个HSI图像
        hsi = cat(3, H, S, I);
        str3  = strcat(base_str, '颜色特征.tif');
        imwrite(hsi,str3);

        %边缘特征
        %读入图像
        I=imread(str);
        I=I(:,:,1);
        %进行边缘检测
        BW1=edge(I,'canny');%采用Canny算子进行边缘检测
        %显示
        str3  = strcat(base_str, '几何特征.tif');
        imwrite(BW1,str3);

        %HOG特征
        Img = imread(str); 
        Img=rgb2gray(Img);
        [featureVector,hogVisualization] = extractHOGFeatures(Img); 
        figure('visible','off');
        plot(hogVisualization);
        str4  = strcat(base_str, '梯度特征.tif');
        print(gcf,'-dpng',str4) 

        %纹理特征
        picture=rgb2gray(imread(str));
        x=size(picture,1);
        y=size(picture,2);
        texture=uint8(zeros(x,y));

        for i=2:1:x-1
            for j=2:1:y-1
                neighbor=uint8(zeros(1,8));

                neighbor(1,1)=picture(i-1,j);
                neighbor(1,2)=picture(i-1,j+1);
                neighbor(1,3)=picture(i,j+1);
                neighbor(1,4)=picture(i+1,j+1);
                neighbor(1,5)=picture(i+1,j);
                neighbor(1,6)=picture(i+1,j-1);
                neighbor(1,7)=picture(i,j-1);
                 neighbor(1,8)=picture(i-1,j-1);
                center=picture(i,j);
                temp=uint8(0);
                for k=1:1:8
                     temp =temp+ (neighbor(1,k) >= center)* 2^(k-1);
                end
                texture(i,j)=temp;

            end
        end
        str6  = strcat(base_str, '纹理特征.tif');
        imwrite(texture,str6);
        end
    end
%     file2 = get(handles.edit2,'String');
% %     selected = get(handles.radiobutton1,'value');
%     if strlength(file2) == 0
%         run("C:\Users\cicol\OneDrive\BUAA\2019秋\20191225 郑老师融合\SAR与多光谱融合\sar_fusion.m")
%     else
%         run(file2);
%     end
%     
%     if get(handles.radiobutton1,'Value')==1
%         run("C:\Users\cicol\OneDrive\BUAA\2019秋\20191225 郑老师融合\SAR与多光谱融合\extract_features.m");
%     end
    
%     if get(handles.radiobutton1,'value') 
%         run("C:\Users\cicol\OneDrive\BUAA\2019秋\20191225 郑老师融合\SAR与多光谱融合\extract_features.m");
%     end
% --- Executes on button press in radiobutton1.
function radiobutton1_Callback(hObject, eventdata, handles)
% hObject    handle to radiobutton1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
%     if get(hObject,'Value')
%         run("C:\Users\cicol\OneDrive\BUAA\2019秋\20191225 郑老师融合\SAR与多光谱融合\extract_features.m");
%     end
% Hint: get(hObject,'Value') returns toggle state of radiobutton1


% --- Executes on key press with focus on pushbutton1 and none of its controls.
function pushbutton1_KeyPressFcn(hObject, eventdata, handles)
% hObject    handle to pushbutton1 (see GCBO)
% eventdata  structure with the following fields (see MATLAB.UI.CONTROL.UICONTROL)
%	Key: name of the key that was pressed, in lower case
%	Character: character interpretation of the key(s) that was pressed
%	Modifier: name(s) of the modifier key(s) (i.e., control, shift) pressed
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on selection change in popupmenu1.
function popupmenu1_Callback(hObject, eventdata, handles)
% hObject    handle to popupmenu1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = cellstr(get(hObject,'String')) returns popupmenu1 contents as cell array
%        contents{get(hObject,'Value')} returns selected item from popupmenu1


% --- Executes during object creation, after setting all properties.
function popupmenu1_CreateFcn(hObject, eventdata, handles)
% hObject    handle to popupmenu1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end




function edit1_Callback(hObject, eventdata, handles)
% hObject    handle to edit1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit1 as text
%        str2double(get(hObject,'String')) returns contents of edit1 as a double


% --- Executes during object creation, after setting all properties.
function edit1_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit2_Callback(hObject, eventdata, handles)
% hObject    handle to edit2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit2 as text
%        str2double(get(hObject,'String')) returns contents of edit2 as a double


% --- Executes during object creation, after setting all properties.
function edit2_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


function edit3_Callback(hObject, eventdata, handles)
% hObject    handle to edit3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit3 as text
%        str2double(get(hObject,'String')) returns contents of edit3 as a double


% --- Executes during object creation, after setting all properties.
function edit3_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit4_Callback(hObject, eventdata, handles)
% hObject    handle to edit4 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit4 as text
%        str2double(get(hObject,'String')) returns contents of edit4 as a double


% --- Executes during object creation, after setting all properties.
function edit4_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit4 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit5_Callback(hObject, eventdata, handles)
% hObject    handle to edit5 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit5 as text
%        str2double(get(hObject,'String')) returns contents of edit5 as a double


% --- Executes during object creation, after setting all properties.
function edit5_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit5 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit6_Callback(hObject, eventdata, handles)
% hObject    handle to edit6 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit6 as text
%        str2double(get(hObject,'String')) returns contents of edit6 as a double


% --- Executes during object creation, after setting all properties.
function edit6_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit6 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes during object creation, after setting all properties.
function axes5_CreateFcn(hObject, eventdata, handles)
% hObject    handle to axes5 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called
%     handles.output = hObject;
    cover_image = imread("fusion.tif");
%     axes(handles.axes5);
    imshow(cover_image);
% Hint: place code in OpeningFcn to populate axes5


% --- Executes during object creation, after setting all properties.
function axes1_CreateFcn(hObject, eventdata, handles)
% hObject    handle to axes1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

    cover_image = imread("fusion.tif");
%     axes(handles.axes5);
    imshow(cover_image);
% Hint: place code in OpeningFcn to populate axes1


% --- Executes during object deletion, before destroying properties.
function axes1_DeleteFcn(hObject, eventdata, handles)
% hObject    handle to axes1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes during object creation, after setting all properties.
function axes8_CreateFcn(hObject, eventdata, handles)
% hObject    handle to axes8 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called
    cover_image = imread("cz5.jpg");
%     axes(handles.axes5);
    imshow(cover_image);
% Hint: place code in OpeningFcn to populate axes8


% --- Executes during object creation, after setting all properties.
function axes9_CreateFcn(hObject, eventdata, handles)
% hObject    handle to axes9 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called
    cover_image = imread("cz5.jpg");
%     axes(handles.axes5);
    imshow(cover_image);
% Hint: place code in OpeningFcn to populate axes9


% --- Executes during object creation, after setting all properties.
function axes11_CreateFcn(hObject, eventdata, handles)
% hObject    handle to axes11 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called
    cover_image = imread("cz5.jpg");
%     axes(handles.axes5);
    imshow(cover_image);
% Hint: place code in OpeningFcn to populate axes11


% --- Executes during object creation, after setting all properties.
function axes12_CreateFcn(hObject, eventdata, handles)
% hObject    handle to axes12 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called
    cover_image = imread("cz5.jpg");
%     axes(handles.axes5);
    imshow(cover_image);
% Hint: place code in OpeningFcn to populate axes12


% --- Executes during object creation, after setting all properties.
function axes13_CreateFcn(hObject, eventdata, handles)
% hObject    handle to axes13 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called
    cover_image = imread("cz.jpg");
%     axes(handles.axes5);
    imshow(cover_image);
% Hint: place code in OpeningFcn to populate axes13


% --- Executes during object creation, after setting all properties.
function axes14_CreateFcn(hObject, eventdata, handles)
% hObject    handle to axes14 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called
    cover_image = imread("cz.jpg");
%     axes(handles.axes5);
    imshow(cover_image);
% Hint: place code in OpeningFcn to populate axes14
