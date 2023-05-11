%
% Author: John David Villarreal
%

%%% Initialization %%%

BaudRate = 115200;                          % Specify RX Baudrate
port = serialport("COM5", BaudRate);        % Init COM Port and BR
                                            % COM varies by machine and
                                            % will appear different on
                                            % different OSs. E.g. on Mac
                                            % it'll contain "usbmodem"

fopen(port);                                % Open the Port

%%% Reading Data %%%

configureTerminator(port, "CR");

 while(1)

   message = readline(port);
   
   sensor = extractBetween(message, 1,1);
   value = extractAfter(message, 2);

   disp(value);

end