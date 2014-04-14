function [pointh, lineh] = plot_curve(pointsX, pointsY, lineX, lineY, color)
    p = @semilogx;
    lineh = p(lineX, lineY, ['-' color], 'LineWidth',1);
    hold on;
    pointh = p(pointsX, pointsY, ['x' color], 'LineWidth',2);