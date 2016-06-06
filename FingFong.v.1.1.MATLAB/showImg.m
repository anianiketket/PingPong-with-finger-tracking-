function[img] = showImg(img,value)
r=img(:,:,1);
g=img(:,:,2);
b=img(:,:,3);
tempimg_r = (r>value(1) & r<value(2));
tempimg_g = (g>value(3) & g<value(4));
tempimg_b = (b>value(5) & b<value(6));
img = tempimg_r & tempimg_g & tempimg_b;
end