%% Initialize
clear all
clc
importfile('manjaro2A_NaN.log.csv');

algorithms = {'Stupid' 'Heap' 'Median' 'Quick'};
ks = {'k = 5' 'k = log2(n)' 'k = sqrt(n)' 'k = n/2'};

n = data(:,2);
names = cell(1,8);
for i=1:4
    names{2*i-1} = [algorithms{i} ' (theoretical)'];
    names{2*i}   = [algorithms{i} ' (measured)'];
end

klabels = cell(1,8);
for i=1:4
    klabels{2*i-1} = [ks{i} ' (theoretical)'];
    klabels{2*i}   = [ks{i} ' (measured)'];
end

k = cell(4,1);
k{1} = @(n) 5;
k{2} = @(n) log2(n);
k{3} = @(n) sqrt(n);
k{4} = @(n) n./2;

stupid_O = @(k,n) [k .* n, ones(size(n))];
heap_O = @(k,n) [n, k .* log2(n), ones(size(n))];
median_O = @(k,n) k + n;
quick_O = @(k,n) [k + n, n.^2];

complexities = cell(4,1);
complexities{1} = stupid_O;
complexities{2} = heap_O;
complexities{3} = median_O;
complexities{4} = quick_O;

%% Plot algorithm vs. k
figure(1);
for i = 0:3
    subplot(2,2,i+1);
    %figure('Visible','off');
    reg_curve(k{i+1}, n, data(:, 4*i+3), stupid_O, 'r');
    reg_curve(k{i+1}, n, data(:, 4*i+4), heap_O, 'g');
    reg_curve(k{i+1}, n, data(:, 4*i+5), median_O, 'b');
    reg_curve(k{i+1}, n, data(:, 4*i+6), quick_O, 'c');
    ylim([0 inf]);
    title(ks{i+1});
    legend(names, 'Location','Northwest');
    xlabel('Instance size (n)');
    ylabel('Time (s)');
    %saveas(gcf, sprintf('Imagens/A_k%d.png', i+1));
    hold off;
end
saveas(gcf, 'Imagens/A_ks.png');

%% Plot k vs. algorithm
figure(2);
for i = 0:3
    subplot(2,2,i+1)
    %figure('Visible','off');
    O = complexities{i+1};
    reg_curve(k{1}, n, data(:, 3+i), O, 'r');
    reg_curve(k{2}, n, data(:, 7+i), O, 'g');
    reg_curve(k{3}, n, data(:, 11+i), O, 'b');
    reg_curve(k{4}, n, data(:, 15+i), O, 'c');
    ylim([0 inf]);
    title(algorithms{i+1});
    legend(klabels, 'Location','Northwest');
    xlabel('Instance size (n)');
    ylabel('Time (s)');
    %saveas(gcf, sprintf('Imagens/A_alg%d.png', i+1));
    hold off;
end
saveas(gcf, 'Imagens/A_algs.png');