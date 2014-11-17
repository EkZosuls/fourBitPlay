%Open M4A file truncate and format it as binary for Arduino demo
%Aleks Zosuls Boston University 2014

%read M4A file with Dan Ellis' function
%http://www.ee.columbia.edu/~dpwe/resources/matlab/m4aread/#2
[Y,SR,NBITS,OPTS] = m4aread('01 Summertime Sadness (Lana Del Rey.m4a');

YOff = Y+1;  %DC shift so that all values are => zero

%use quantizer to make four bit version
q = quantizer('mode', 'ufixed', 'overflowmode', 'saturate', 'format', [5 4]);
output2 = quantize(q, YOff(200000:2500000,1));

%scale output of quantizer to 0:15 integers
output2 = output2*15/1.94;
output2 = round(output2);   %round scaling
downoutput = output2(1:5:length(output2)); %decimate output to reduce sample rate
%decimating by 5 reduces sample period to approximately 80 microseconds on
%an Arduino UNO. This was calculate then hand tuned

%save as a binary file
fid = fopen('lana1.bin','w')
fwrite(fid, downoutput, 'uint8')
fclose(fid)
%thisfile can be put on a microflash and read by arduino to produce some 
%poor quality audio