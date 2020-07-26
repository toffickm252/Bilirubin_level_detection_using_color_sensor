x=[	10.24
26.63
19.79
17.87
24.48
13.89
30.12
26.81
25.94
27.54
17.5
24.10
17.81
28.47
31.95
];%normalized blue

y=[18
5
11
12
7
15
2.50
5.0
6
4.50
12
7
12.1
4
2
];%Assigned bilirubin level

scatter(x,y);
%plot(x,y,'.b')
p=polyfit(x,y,1);
f=polyval(p,x);

hold on
plot(x,f);

xlabel([ ' Normalized % of Blue' ' (Best fit line Eqn. y=' num2str(p(1)) '*x +' num2str(p(2)) ')']);
ylabel('Assigned Bilirubin Level(mg/dL)');
title('Plot of Assigned bilirubin level against Normalized of bilirubin');

%fit=polyfit(x,y,1);
%plot(polyval(fit,x));