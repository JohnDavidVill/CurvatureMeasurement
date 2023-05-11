%
% Author: John David Villarreal
%

%%% Initialization %%%

clc
clear all
close all

BaudRate = 115200;                          % Specify RX Baudrate
port = serialport("COM5", BaudRate);        % Init COM Port and BR
                                            % COM varies by machine and
                                            % will appear different on
                                            % different OSs. E.g. on Mac
                                            % it'll contain "usbmodem"

fopen(port);                                % Open the Port

%%% Reading Data %%%

configureTerminator(port, "CR");            % Terminator for the end of
                                            % message

 elem_num = 0;
 while(1)

   message = readline(port);                % Read from the port
   
   sensor = extractBetween(message, 1,1);   % Extract which sensor the data
                                            % is being fed from
   value = str2double(extractAfter(message, 2));   
                                            % Extract the value from the 
                                            % sensor as a double
 
   plot(elem_num, value, 'r.'); drawnow
   hold on
   elem_num = elem_num + 1;

end