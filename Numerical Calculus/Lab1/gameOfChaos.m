function gameOfChaos(no_of_sims)
X = [-1, -0.5; 0, 1; 1, -0.5]
clf; hold on; axis square;
plot(X(:,1), X(:,2))
plot(X([3,1],1), X([3,1],2), 'red')

P=[0, 0];
for i = 1:no_of_sims
    r = randi(3);
    P(1) = (X(r,1) + P(1)) / 2;
    P(2) = (X(r,2) + P(2)) / 2;
    
    % P = (X(r,:) + P) / 2;
    
    plot(P(1), P(2), '.k', 'MarkerSize', 8)
end