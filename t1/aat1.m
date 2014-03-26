
function inst = instance_a(n) % n = 1000*(2^i); i = 1:15

	cont = 1;
	inst = 1:n;

	while cont <= n
		j = randi([cont, n]);

		swp = inst(j);
		inst(j) = inst(cont);
		inst(cont) = swp;

		cont = cont + 1;
	end

end

function inst = instance_b(n ,j) % n = 2^25; p = 2^j; j = 1:15

	inst = 1:n;

	for i = 1:j
		a = randi([1,n]);
		b = randi([1,n]);

		swp = inst(a);
		inst(a) = inst(b);
		inst(b) = swp;
	end

end


for i = 1:7
	inst_a{i} = instance_a(1000*(2^i));
end
