function [y] = vibrato_effect_float(x, delay, LFO, FS)

    LFO_S = LFO/FS;          % Frequência de modulação em número de amostras        
    DELAY = round(delay*FS); % Largura da modulação em número de amostras
    L_IN = length(x);        % Tamanho do vetor de entrada   
    L_DELAY = 2 + DELAY + DELAY *2; % Tamanho do delayline
    W = LFO_S*2*pi;          % frequencia angular de modulação
    
    % Alocação de memória
    Delayline = zeros(L_DELAY,1);   
    y = zeros(size(x));             
    
    for n=1:(L_IN-1)
       % Calculo da posição da amostras que será repetida
       TAP = 1+DELAY+DELAY*sin(W*n);
       i = floor(TAP);
       % Atualiza o vetor com as amostras disponíveis para delay
       Delayline=[x(n);Delayline(1:L_DELAY-1)]; 
       % Filtro com Interpolação Linear
       frac = TAP-i;
       y(n,1) = Delayline(i+1)*frac+Delayline(i)*(1-frac); 
    end
end


