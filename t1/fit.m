function c = fit(complexity, k, n, times)
    fitted = complexity(k, n);
    i = find(~isnan(times));
    fitted(i,:);
    norm = fitted(i,:)' * fitted(i,:);
    c = norm \ (fitted(i,:)' * times(i));