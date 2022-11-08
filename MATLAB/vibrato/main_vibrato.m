% Leitura do arquivo de áudio
infile = 'acoustic.wav';
[x, FS] = audioread(infile, 'native');
%sound(x, FS);

% Parametros para o Vibrato

LFO = 10;                % Parâmetro de frequência para a modulação 
delay = 0.0008;          % Parâmetro para a largura da modulação

%% Execução para ponto fixo

y = vibrato_effect_fixedPoint(x, delay, LFO, FS);
y = double(y)./2^15;
audiowrite('vibrato_matlab_fixedpt.wav', y, FS);
%% Execução para ponto flutuante

y = vibrato_effect_float(x, delay, LFO, FS);
audiowrite('vibrato_matlab_float.wav', y, FS);
%%

sound(y, FS);


