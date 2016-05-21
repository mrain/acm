with open('B-small-attempt0.in') as fp, open('output', 'w') as fw:
    for idx, line in enumerate(fp):
        if idx == 0:
            continue
        if idx % 2 == 1:
            continue
        bag = [int(c) for c in line.strip().split()]
        time = []
        for tmp in xrange(max(bag)):
            # thres: downto thres and eat
            thres = tmp + 1
            time.append(thres + sum([(x-1)/thres for x in bag]))
        fw.write('Case #{idx}: {time}\n'.format(idx=idx/2, time=min(time)))
