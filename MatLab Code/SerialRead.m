%
% Author: John David Villarreal
%

%%% Initialization %%%

BaudRate = 9600;                            % Specify RX Baudrate
port = serialport("COM3", BaudRate);        % Init COM Port and BR
                                            % COM varies by machine and
                                            % will appear different on
                                            % different OSs. E.g. on Mac
                                            % it'll contain "usbmodem"

fopen(port);                                % Open the Port

%%% Plotting Data %%%

elem = 1;
while(1)

    read(elem) = str2double(fscanf(port));  % Read from the Port

    plot(elem);

    pause(0.01);
    elem = elem+1;

end