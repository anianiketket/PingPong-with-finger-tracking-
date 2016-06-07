%This code will run the image processing part of Fing Fong game in MATLAB.
%It will by default run for two colours. The Kalman Filter is designed for
%two players till now. It is simple to further increase number of objects.
%If you want the x coordinates too then check the Run.m file
global vidh vidw cam threshold brightness contrast lowerArea upperArea config; 
brightness = [0,0]; 
contrast = [1,1]; 
threshold = [0,0,0,0,0,0;0,0,0,0,0,0]; 
vidh = 640; 
vidw = 480; 
cam = webcam('Integrated Webcam');
UI(1); config=0; %Threshold the RGB values by first clicking on preview window. It will take snapshot. Now drag
UI(2); % a rectangle on the color on left side and see the binary on the right side. You can adjust contrast, brightness, max size and min size
global state_playerOne state_playerTwo P_playerOne P_playerTwo Ex; KalmanFilterInit(); P_playerOne = Ex; P_playerTwo = Ex; state_playerOne = [0;0;0;0]; state_playerTwo = [0;0;0;0];
close all
while 1
    y = Run(2); %Press Ctrl+C to break the loop
end