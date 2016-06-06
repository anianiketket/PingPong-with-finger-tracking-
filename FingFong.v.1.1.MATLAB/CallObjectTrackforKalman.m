function[x_,y_]=CallObjectTrackforKalman(pl)
    global cam threshold brightness contrast lowerArea upperArea;
    SE = strel('disk',3);
    SE1 = strel('disk',2);
    s = snapshot(cam);
    tempimg = s;
    
    tempimg = brightness(pl)*100+tempimg;
    for i=1:3
        tempimg(:,:,i) = imadjust(tempimg(:,:,i),[],[],contrast(pl));
    end
    
    r = tempimg(:,:,1);
    g = tempimg(:,:,2);
    b = tempimg(:,:,3);
    
    tempr = r > threshold(pl,1) & r < threshold(pl,2);
    tempg = g > threshold(pl,3) & g < threshold(pl,4);
    tempb = b > threshold(pl,5) & b < threshold(pl,6);
    img = tempr & tempg & tempb;
    
    img=imdilate(img,SE1);
    %Perform Connected Component Analysis and filter the noises.
    connComp = bwconncomp(img);
    stats = regionprops(connComp,'Area');
    mask = img;
    mask(vertcat(connComp.PixelIdxList{[stats.Area] < lowerArea(pl) | [stats.Area] > upperArea(pl)}))=0;
    
    %Some morphological operations for smoothing the segmented object.
    mask=imdilate(mask,SE);
    
    %Find C.M. of binary object.
    [x,y]=find(mask);
    
    if ~isempty(x)
        C(1,:)=[mean(x),mean(y)];
        x_ = C(1,2);
        y_ = C(1,1);
    else
        x_ = 0;
        y_ = 0;
    end
    clearvars -except x_ y_;
end