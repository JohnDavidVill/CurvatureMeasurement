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
 elem_a = 255;
 elem_b = 255;

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
    if(elem_a == 255 && elem_b == 255)      % Find element for sensor A
        elem_a = elem_num;
    elseif(elem_a ~= 255 && elem_b == 255)  % Find element for sensor B
        elem_b = elem_num;
        break
    end

   end

   elem_num = elem_num + 1;

end

%%% Calculations %%%
d_baud = elem_b - elem_a;                   % Find the difference in the
                                            % element numbers. This is the
                                            % difference in the amount of
                                            % bauds between the two times

d_time = d_baud * (1 / BaudRate);           % Calculate time based off of
                                            % the difference in bauds and
                                            % the baud rate

c_const = 2*(86400 / 2*pi)^2;
c_height = (sqrt(d_height + height) - sqrt(height))^2;

radius = 2*c_const*c_height/(d_time^2);

fprintf("The Radius of the Earth is %d m\n\r", radius);