x=0:0.001:1;
y=0.08.^x;
y1=1-y;
plot(x,y,'--k');
hold on;
plot(x,y1,'k');
legend('\lambda_T','\lambda_S');%%用图例标识曲线