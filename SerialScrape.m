%
% Author: John David Villarreal
%

%%% Initialization %%%

clc
clear all
close all

d_height = 0.63;
height = 0.52;

BaudRate = 9600;                            % Specify RX Baudrate
port = serialport("/dev/cu.usbmodem11103", BaudRate);        
                                            % Init COM Port and BR
                                            % COM varies by machine and
                                            % will appear different on
                                            % different OSs. E.g. on Mac
                                            % it'll contain "usbmodem"

%fopen(port);                                % Open the Port
port.Timeout = 84600;

high_threshold = 30000;
low_threshold = 10000;
threshold_tolerance = 500;

%%% Reading Data %%%

configureTerminator(port, "LF");            % Terminator for the end of
                                            % message

 elem_num = 0;
 d_time = 1;
 time_flag = 1;

 while(1)

   message = readline(port);                % Read from the port
 
   value = str2double(message);   
                                            % Extract the value from the 
                                            % sensor as a double
   disp(value)
   plot(elem_num, value, 'b.'); drawnow     % Draw the serial input plot
   hold on

   % Find element numbers to calculate time in a future calculation
   % Start/Stop timer based on threshold
   if(value <= high_threshold-threshold_tolerance && value >= high_threshold+threshold_tolerance)              
      
       if(time_flag == 1)
          tic
       end
   elseif(value <= low_threshold)
        d_time = toc;
        break
   end

   elem_num = elem_num + 1;                 % Iterate over loop

 end

 %%% Calculations %%%

c_const = 2*(86400 / 2*pi)^2;               % Constant value in calculation                           
c_height = (sqrt(d_height + height) - sqrt(height))^2;
                                            % Height value in calculation

radius = 2*c_const*c_height/(d_time^2)/1000;% Radius calculation

fprintf("The Radius of the Earth is %d km\n\r", radius);
                                            % Print the result to the 
                                            % Command Window
