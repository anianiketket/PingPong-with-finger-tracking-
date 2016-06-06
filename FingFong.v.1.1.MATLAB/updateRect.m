function [] = updateRect(~,~) 
global rectMask threshold player;
threshold(player,:) = getThresholds(rectMask,round(getrect()));
end