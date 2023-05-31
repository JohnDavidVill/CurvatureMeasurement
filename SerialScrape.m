%
% Author: John David Villarreal
%

%%% Initialization %%%

clc
clear all
close all

d_height = 0.63;
height = 0.52;

BaudRate = 115200;                          % Specify RX Baudrate
port = serialport("COM5", BaudRate);        % Init COM Port and BR
                                            % COM varies by machine and
                                            % will appear different on
                                            % different OSs. E.g. on Mac
                                            % it'll contain "usbmodem"

fopen(port);                                % Open the Port
port.Timeout = 84600;

threshold = 20;

%%% Reading Data %%%

configureTerminator(port, "CR");            % Terminator for the end of
                                            % message

 elem_num = 0;
 d_time = 1;
 time_flag = 1;

 while(1)

   message = readline(port);                % Read from the port
   
   sensor = extractBefore(message, 2);      % Extract which sensor the data
                                            % is being fed from
   value = str2double(extractAfter(message, 2));   
                                            % Extract the value from the 
                                            % sensor as a double

                                   
   plot(elem_num, value, 'b.'); drawnow     % Draw the serial input plot
   hold on

   if(value == threshold)                   % Find element numbers to calculate
                                            % time in a future calculation
    if(time_flag == 1)                      % Start/Stop timer based on threshold
        tic
        time_flag = 0;
    elseif(time_flag == 0)
        d_time = toc;
        break
    end

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