function [pointh, lineh] = reg_curve(k, n, times, complexity, color)
    x = min(n(~isnan(times))):1000:max(n(~isnan(times)));
    c = fit(complexity, k(n), n, times);
    calc = complexity(k(x)',x');
    [pointh, lineh] = plot_curve(n, times, x, calc * c, color);