clear

%float

filename='ff7vic.wav';
%ler audio
[x,Fs] = audioread(filename);

%fuzz
gain = 11; % Spinal Tap it
mix = 1; % Hear only fuzz
q=x*gain/max(abs(x));
z=sign(-q).*(1-exp(sign(-q).*q));
y=mix*z*max(abs(x))/max(abs(z))+(1-mix)*x;

%escrever saida
audiowrite('outfuzz.wav',y,Fs);

TotalTime = length(y)./Fs;
t = 0:TotalTime/(length(y)):TotalTime-TotalTime/length(y);

%grafico de saida
plot(t,y)
title('outfuzz.wav','fontsize', 16)
xlabel('tempo [s]', 'fontsize', 12) 
ylabel('Amplitude','fontsize', 12) 

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
