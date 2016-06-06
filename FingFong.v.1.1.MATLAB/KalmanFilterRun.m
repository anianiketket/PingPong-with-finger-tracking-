function[state_estimate,P] = KalmanFilterRun(u,state_estimate,P,sensorreading)
    global A B C Ex Ez vidh vidw    
    state_estimate = A*state_estimate+B*u;
    P=A*P*A'+Ex;
    K=P*C'/(C*P*C'+Ez);
    if (sensorreading(1)~=0 || sensorreading(2)~=0)
        state_estimate=state_estimate + K*(sensorreading-C*state_estimate);
    end
    if(state_estimate(1)>vidh)
        state_estimate(1)=vidh;
    elseif(state_estimate(1)<0)
            state_estimate(1)=0;
    end
    if(state_estimate(2)>vidw)
        state_estimate(2)=vidw;
    elseif(state_estimate(2)<0)
            state_estimate(2)=0;
    end
    P=(eye(4)-K*C)*P;
end