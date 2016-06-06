function [] = UI(i)
    warning off;
    
    SE0=strel('disk',3);
    SE1=strel('disk',2);
    
    global rectMask cam threshold config brightness contrast lowerArea upperArea player;
    player = i;
    config = true;
    lowerArea(i) = 1;
    upperArea(i) = 10000;
    
    threshold(i,:) = [1,255,1,255,1,255];
    
    figHandle = figure('Name','Token configuration');
    set(figHandle,'ButtonDownFcn',@updateRect);
    
    %Open GUI
    GUI();
    
    while config
        img=snapshot(cam);
        img=flip(img,2);
        editimg = brightness(i)*100+img;
        for j=1:3
            editimg(:,:,j) = imadjust(editimg(:,:,j),[],[],contrast(i));
        end
        rectMask = editimg;
        img = showImg(editimg,threshold(i,:));
        img = imdilate(img,SE1);

        %Perform Connected Component Analysis and filter the noises.
        mask = img;
        connComp = bwconncomp(img);
        if connComp.NumObjects ~= 0
            stats = regionprops(connComp,'Area');
            mask(vertcat(connComp.PixelIdxList{[stats.Area]<lowerArea(i) | [stats.Area]>upperArea(i)})) = 0;
            %Some morphological operations for smoothing the segmented object.
            mask = imdilate(mask,SE0);
        end
        
        imshowpair(editimg,mask,'montage');
        clear img;
    end
    clearvars -except cam threshold brightness contrast upperArea lowerArea
    close all;
end