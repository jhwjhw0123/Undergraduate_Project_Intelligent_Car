%///////////////////////
%@Function: Simulate the Fuzzy Reasoning of The Intelligent Car
%@Arthor: Chen Wang, 2012301932, NPU
%Note: Chinese Charactors are uncompatible in the Editor, all texts are in Englsh
%/////////////////////
clc;
clear;
FisMat = newfis('CarAction');
FisMat = addvar(FisMat,'input','Speed',[10 255]);   
FisMat = addvar(FisMat,'input','Distance',[100 1500]);
FisMat = addvar(FisMat,'output','AdjustValue',[-100,100]);
%Member Function of Input Variable 1
FisMat = addmf(FisMat,'input',1,'low','trimf',[10,10,63]);                 %1
FisMat = addmf(FisMat,'input',1,'mid-low','trimf',[0,64,127.5]);         %2
FisMat = addmf(FisMat,'input',1,'mid','trimf',[64,127.5,191.25]);        %3
FisMat = addmf(FisMat,'input',1,'mid-high','trimf',[127.5,191.25,255]);  %4
FisMat = addmf(FisMat,'input',1,'high','trimf',[191.25,255,255]);     %5
%Member Function of Input Variable 2
FisMat = addmf(FisMat,'input',2,'close','trimf',[100,100,850]);              %1
FisMat = addmf(FisMat,'input',2,'mid','trimf',[100,750,1500]);             %2
FisMat = addmf(FisMat,'input',2,'far','trimf',[650,1500,1500]);           %3
%Member Function of Out Variable
FisMat = addmf(FisMat,'output',1,'veryfar-dec','trimf',[-100,-100,-70]); %1
FisMat = addmf(FisMat,'output',1,'far-dec','trimf',[-90,-80,-60]);      %2
FisMat = addmf(FisMat,'output',1,'dec','trimf',[-80,-60,-40]);           %3
FisMat = addmf(FisMat,'output',1,'mid-dec','trimf',[-60,-40,-20]);       %4
FisMat = addmf(FisMat,'output',1,'slight-dec','trimf',[-40,-20,0]);      %5
FisMat = addmf(FisMat,'output',1,'stable','trimf',[-20,0,20]);           %6
FisMat = addmf(FisMat,'output',1,'slight-inc','trimf',[0,20,40]);        %7
FisMat = addmf(FisMat,'output',1,'mid-inc','trimf',[20,40,60]);          %8
FisMat = addmf(FisMat,'output',1,'inc','trimf',[40,60,80]);              %9
FisMat = addmf(FisMat,'output',1,'far-inc','trimf',[60,80,90]);         %10
FisMat = addmf(FisMat,'output',1,'veryfar-inc','trimf',[70,100,100]);     %11
%Setup Fuzzy Reasoning Rules
rulelist = [1 3 11 1 1;1 2 10 1 1;1 1 7 1 1;2 3 9 1 1;2 2 8 1 1;2 1 6 1 1;3 3 8 1 1;3 2 6 1 1;3 1 4 1 1;4 3 5 1 1;4 2 3 1 1;4 1 2 1 1;5 3 4 1 1;5 2 2 1 1;5 1 1 1 1];
FisMat = addrule(FisMat,rulelist);
gensurf(FisMat);
writefis(FisMat);