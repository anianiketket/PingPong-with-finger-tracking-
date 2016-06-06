function[thvalue,brightnessfactor,lower,upper]=UI(cam)
    warning off;
    SE=strel('disk',3);
    SE1=strel('disk',2);
    global value flagxx brightfactor gamma1 lowerx upperx;
    flagxx=0;
    brightfactor=0;
    value=[0,0,0,0,0,0];
    
    %Open GUI
    while flagxx==0
        tempimg=snapshot(cam);
        tempimg=flip(tempimg,2);
        GUI();
        editimg=brightfactor*100+tempimg;
        for i=1:3
        editimg(:,:,i)=imadjust(editimg(:,:,i),[],[],gamma1);
        end
        img = Showimg(editimg,value);
        img=imdilate(img,SE1);

        %Perform Connected Component Analysis and filter the noises.
        connComp=bwconncomp(img);
        stats=regionprops(connComp,'Area');
        mask=img;
        mask(vertcat(connComp.PixelIdxList{[stats.Area]<lowerx | [stats.Area]>upperx}))=0;
        %Some morphological operations for smoothing the segmented object.
        mask=imdilate(mask,SE);

        imshowpair(mask,editimg,'montage');
        clear img;
        %Contains Thresholded value
        thvalue=round(value);
        brightnessfactor=brightfactor;
        lower=lowerx;
        upper=upperx;
    end
    clearvars -except cam thvalue brightnessfactor
end