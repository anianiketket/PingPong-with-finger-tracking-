function[y]=Run(i)
global cam state_playerOne state_playerTwo P_playerOne P_playerTwo;
tempimg=snapshot(cam);
[x1,y1]=CallObjectTrackforKalman(1);
sensorreading=[x1;y1];
[state_playerOne,P_playerOne]=KalmanFilterRun(0.005,state_playerOne,P_playerOne,sensorreading);
tempimg=insertShape(tempimg,'circle',[round(state_playerOne(1)),round(state_playerOne(2)),5],'LineWidth',3,'Color','red');
Ky1=state_playerOne(2);
if(i==2)
    [x2,y2]=CallObjectTrackforKalman(2);
    sensorreading=[x2;y2];
    [state_playerTwo,P_playerTwo]=KalmanFilterRun(0.005,state_playerTwo,P_playerTwo,sensorreading);
    Ky2=state_playerTwo(2);
    tempimg=insertShape(tempimg,'circle',[round(state_playerTwo(1)),round(state_playerTwo(2)),5],'LineWidth',3,'Color','blue');
else 
    Ky2 = 0;
end
y = [Ky1,Ky2];
imshow(tempimg);
return
end