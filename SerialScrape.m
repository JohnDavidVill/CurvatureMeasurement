%
% Author: John David Villarreal
%

%%% Initialization %%%

clc
clear all
close all

d_height = 5;

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
 avalue = 256;
 bvalue = 256;

 while(1)

   message = readline(port);                % Read from the port
   
   sensor = extractBetween(message, 1,1);   % Extract which sensor the data
                                            % is being fed from
   value = str2double(extractAfter(message, 2));   
                                            % Extract the value from the 
                                            % sensor as a double
   
   if(sensor == "A")
        
        avalue = value;

  elseif(sensor == "B")
 
        bvalue = value;

  end
                                    
   plot(elem_num, avalue, 'r.'); drawnow
   hold on
   %plot(elem_num, bvalue, '--'); drawnow
   %hold on
   elem_num = elem_num + 1;

end