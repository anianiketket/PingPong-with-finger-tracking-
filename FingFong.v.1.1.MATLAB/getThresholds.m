function [thres_value] = getThresholds(img,rect)
roi = imcrop(img,rect);
thres_value = [min(min(roi(:,:,1))) max(max(roi(:,:,1))) min(min(roi(:,:,2))) max(max(roi(:,:,2))) min(min(roi(:,:,3))) max(max(roi(:,:,3)))];    
return;
end