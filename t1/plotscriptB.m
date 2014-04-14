%% Initialize
clear all
clc
importfile('manjaro2B_NaN.log.csv');

n = data(:,2);
names = cell(4,1);
names{1} = 'Stupid';
names{2} = 'Heap';
names{3} = 'Median';
names{4} = 'Quick';

klabels = cell(4,1);
klabels{1} = 'k = 5';
klabels{2} = 'k = log2(n)';
klabels{3} = 'k = sqrt(n)';
klabels{4} = 'k = n/2';

k = cell(4,1);
k{1} = @(n) 5;
k{2} = @(n) log2(n);
k{3} = @(n) sqrt(n);
k{4} = @(n) n./2;

p = @(X,Y,color) plot_curve(X,Y,X,Y,color);

%% Plot algorithm vs. k
%figure(1);
for i = 0:3
    %subplot(2,2,i+1);
    figure('Visible','off');
    h1 = p(n, data(:, 4*i+3), 'r');
    hold on;
    h2 = p(n, data(:, 4*i+4), 'g');
    h3 = p(n, data(:, 4*i+5), 'b');
    h4 = p(n, data(:, 4*i+6), 'c');
    %ylim([0 inf]);
    title(klabels{i+1});
    legend([h1, h2, h3, h4], names, 'Location','Northwest');
    xlabel('Permutations (p)');
    ylabel('Time (s)');
    saveas(gcf, sprintf('Imagens/B_k%d.png', i+1));
    hold off;
end

%% Plot k vs. algorithm
%figure(2);
for i = 0:3
    %subplot(2,2,i+1);
    figure('Visible','off');
    h1 = p(n, data(:, 3+i), 'r');
    hold on;
    h2 = p(n, data(:, 7+i), 'g');
    h3 = p(n, data(:, 11+i), 'b');
    h4 = p(n, data(:, 15+i), 'c');
    %ylim([0 inf]);
    title(names{i+1});
    legend([h1, h2, h3, h4], klabels, 'Location','Northwest');
    xlabel('Permutations (p)');
    ylabel('Time (s)');
    saveas(gcf, sprintf('Imagens/B_alg%d.png', i+1));
    hold off;
end