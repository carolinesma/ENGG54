function [y] = vibrato_effect_fixedPoint(x, delay, LFO, FS)
    q15 = 2^15;
    q12 = 2^12;
    q11 = 2^11;

    delayFix = int16(delay*q15);
    piFix = int16(round(pi*q12));

    LFO_S = div(LFO,FS,q15);            % Frequência de modulação em número de amostras        
    DELAY = mul(delayFix,FS,q15);       % Largura da modulação em número de amostras
    L_IN = uint32(length(x));           % Tamanho do vetor de entrada   
    L_DELAY = int16(2+DELAY+DELAY*2);   % Tamanho do delayline
    
    temp = mul(2, piFix, q12);
    W = mul(LFO_S*(q12/q15),temp,1); % frequencia angular de modulação
    W = W*(q15/q12);

    % Alocação de memória
    Delayline = int16(zeros(L_DELAY,1));   
    y = int16(zeros(size(x)));             
    
    for j=1:(L_IN-1)
       % Calculo da posição da amostras que será repetida
       mod = (double(W)/q15)*double(j);
       TAP = 1+double(DELAY)+double(DELAY)*sin(mod);
       i = floor(TAP);
       % Atualiza o vetor com as amostras disponíveis para delay
       Delayline=[x(j);Delayline(1:L_DELAY-1)]; 
       % Filtro com Interpolação Linear
       frac = sub(TAP*q11, i*q11);
       frac = frac*(q15/q11);
       int1 = mul(Delayline(i+1),frac,q15);
       sub2 = sub(1*q15,frac);
       int2 = mul(Delayline(i),sub2,q15);
       temp = int1 + int2;
       y(j,1) = temp;
    end
end

function c = add(a, b)
    int16_max = 2^15-1;
    int16_min = -2^15;

    temp = int32(a)+int32(b);
    temp = temp/2^15;

    if (temp > int16_max)
        temp = int16_max;
    end
    if (temp < int16_min)
        temp = int16_min;
    end
    
    c = int16(temp);
end

function c = sub(a, b)
    int16_max = 2^15-1;
    int16_min = -2^15;

    temp = int16(a)-int16(b);

    if (temp > int16_max)
        temp = int16_max;
    end
    if (temp < int16_min)
        temp = int16_min;
    end
    
    c = int16(temp);
end

function c = div(a,b,n)
    int16_max = 2^15-1;
    int16_min = -2^15;

    if ((abs(b) < abs(a) ) || (b == 0))
        if(bitxor(bitand(int16(b), int16(0x8000)),bitand(int16(a),int16(0x8000))))
            c = int16_min;
            return
        else
            c = int16_max;
            return
        end
    end

    temp =  int32(a*n);
    temp =  temp + int32(round(b/2)); %fator de arredondamento
    c = int16(temp/b);
   
end

function c = mul(a,b,n)
    int16_max = 2^15-1;
    int16_min = -2^15;
    
    temp = (int32(a)*int32(b));
    temp = temp + int32(0.5);
    temp = temp/n;

    if (temp > int16_max)
        temp = int16_max;
    end
    if (temp < int16_min)
        temp = int16_min;
    end

    c = int16(temp);
end
