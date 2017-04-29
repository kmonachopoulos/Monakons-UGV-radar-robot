%%
%--------------------------------------------------------------------------------------------------------------------------------
% Technological Educational Institute of Athens - Xbee mini-project 
%--------------------------------------------------------------------------------------------------------------------------------
%%
%%
%--------------------------------------------------------------------------------------------------------------------------------
% Project       : Monakons-UGV-Autonomus_Robot
% File          : MatlabRobotCommunication.m
% Description   : This code implements sets the communication parameters of arduino and matlab through a Serial port
% Author        : Monachopoulos Konstantinos
%--------------------------------------------------------------------------------------------------------------------------------
%%

clear;clc;
S=serial('com18'); % Create an S Object
data=0;
set(S,'inputbuffersize',4096,'timeout',20); % Set serial communication parameter
fopen(S); % Open serial communcation
i=20:4:130;
i=i.*(pi/180); % Convert deegres to rad (to plot using polar function)
    
while (1)
    if s.bytesavailable>0 % If data from UGV are available
    data=fscanf(S);
    data = str2num(data);
    figure,polar(i,data) % Plot the space infront of the UGV
    end
    data=0;
end
    
% instrfind  % Checks if serial is activated
% fclose(S); % Close the serial port
% delete(S); % Delete S object
% clear S;