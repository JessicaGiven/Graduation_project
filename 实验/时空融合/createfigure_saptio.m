function createfigure(X1, YMatrix1)
%CREATEFIGURE(X1, YMATRIX1)
%  X1:  x ���ݵ�ʸ��
%  YMATRIX1:  y ���ݵľ���

%  �� MATLAB �� 06-Dec-2017 16:51:49 �Զ�����

% ���� figure
figure1 = figure;

% ���� axes
axes1 = axes('Parent',figure1);
hold(axes1,'on');

% ʹ�� plot �ľ������봴������
plot1 = plot(X1,YMatrix1,'LineWidth',1,'Color',[0 0 0]);
set(plot1(1),'DisplayName','\lambda_T','LineStyle','--');
set(plot1(2),'DisplayName','\lambda_S');

% ���� xlabel
xlabel('ƽ���˶���Ϣ','FontWeight','bold','FontSize',14);

% ȡ�������е�ע���Ա���������� Y ��Χ
% ylim(axes1,[0 1.15]);
box(axes1,'on');
% ������������������
set(axes1,'YTickLabel',{'0','0.2','0.4','0.6','0.8','1',''});
% ���� legend
legend1 = legend(axes1,'show');
set(legend1,...
    'Position',[0.683651804670911 0.76906675355254 0.197452229299362 0.138356160627653],...
    'FontWeight','bold',...
    'FontSize',10);

