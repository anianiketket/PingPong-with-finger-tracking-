%This function tracks a red and a blue band worn on a finger, covering 3/4
%of your finger.

function[yred,yblue]=CallObjectTrack(vidh,vidw,cam)
    warning off;
    
    SE=strel('disk',3);
    SE1=strel('disk',2);
    s=zeros(vidh,vidw);
    
    %Take an image from webcam
    s=snapshot(cam);
    tempimg=s;
    r=tempimg(:,:,1);
    g=tempimg(:,:,2);
    b=tempimg(:,:,3);
    
    %Separate red frames
    red_tempr=r>180;
    red_tempg=g<120;
    red_tempb=b<120;
    red_img=red_tempr & red_tempg & red_tempb;
    
    %Separate blue frames
    blue_tempb=b>170;
    blue_tempg=g>100 & g<150;
    blue_tempr=r<100;
    blue_img=blue_tempr & blue_tempg & blue_tempb;
    
    red_img=imdilate(red_img,SE1);
    blue_img=imdilate(blue_img,SE1);
    
    %Perform Connected Component Analysis and filter the noises.
    red_connComp=bwconncomp(red_img);
    red_stats=regionprops(red_connComp,'Area');
    red_mask=red_img;
    red_mask(vertcat(red_connComp.PixelIdxList{[red_stats.Area]<600 | [red_stats.Area]>3500}))=0;
    
    blue_connComp=bwconncomp(blue_img);
    blue_stats=regionprops(blue_connComp,'Area');
    blue_mask=blue_img;
    blue_mask(vertcat(blue_connComp.PixelIdxList{[blue_stats.Area]<600 | [blue_stats.Area]>3500}))=0;
    
    %Some morphological operations for smoothing the segmented object.
    red_mask=imdilate(red_mask,SE);
    blue_mask=imdilate(blue_mask,SE);
    
    %Find C.M. of binary object.
    [red_x,red_y]=find(red_mask);
    [blue_x,blue_y]=find(blue_mask);
    
    if ~isempty(red_x)
        red_C(1,:)=[mean(red_x),mean(red_y)];
        yred=red_C(1,1);
        
        %Display a circle at the mean position calculated.
        tempimg=insertShape(tempimg,'circle',[red_C(1,2),red_C(1,1),5],'LineWidth',3,'Color','red');
    else
        yred=0;
    end
    if ~isempty(blue_x)
        blue_C(1,:)=[mean(blue_x),mean(blue_y)];
        yblue=blue_C(1,1);
        
        %Display a circle at the mean position calculated.
        tempimg=insertShape(tempimg,'circle',[blue_C(1,2),blue_C(1,1),5],'LineWidth',3,'Color','blue');
    else
        yblue=0;
    end
    %Plot
    imshow(tempimg);
    pause(.01);    clearvars -except yred yblue;
end