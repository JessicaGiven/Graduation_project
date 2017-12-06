function createfigure(X1, YMatrix1)
%CREATEFIGURE(X1, YMATRIX1)
%  X1:  x 数据的矢量
%  YMATRIX1:  y 数据的矩阵

%  由 MATLAB 于 06-Dec-2017 16:51:49 自动生成

% 创建 figure
figure1 = figure;

% 创建 axes
axes1 = axes('Parent',figure1);
hold(axes1,'on');

% 使用 plot 的矩阵输入创建多行
plot1 = plot(X1,YMatrix1,'LineWidth',1,'Color',[0 0 0]);
set(plot1(1),'DisplayName','\lambda_T','LineStyle','--');
set(plot1(2),'DisplayName','\lambda_S');

% 创建 xlabel
xlabel('平均运动信息','FontWeight','bold','FontSize',14);

% 取消以下行的注释以保留坐标轴的 Y 范围
% ylim(axes1,[0 1.15]);
box(axes1,'on');
% 设置其余坐标轴属性
set(axes1,'YTickLabel',{'0','0.2','0.4','0.6','0.8','1',''});
% 创建 legend
legend1 = legend(axes1,'show');
set(legend1,...
    'Position',[0.683651804670911 0.76906675355254 0.197452229299362 0.138356160627653],...
    'FontWeight','bold',...
    'FontSize',10);

