import math

def get_magic_power(x):
    if   x == 0:
        return '-~0'
    elif x == 1:
        return '-~0<<-~0'
    elif x == 2:
        return '-~0<<(-~0<<-~0)'
    elif x == 4:
        return '-~0<<(-~0<<(-~0<<-~0))'
    elif x == 16:
        return '-~0<<(-~0<<(-~0<<(-~0<<-~0)))'
    elif x == 65535:
        return '-~0<<(-~0<<(-~0<<(-~0<<(-~0<<-~0))))'
    else:
        return None

def bitcnt(x):
    return int(math.floor(math.log2(x)) + 1)

def get_bits(x):
    bits = []
    max_iter = bitcnt(x)
    for i in range(0, max_iter):
        if x & (1 << i):
            bits.append(i)
    return bits

def ebanina(x):
    local_ebanina = ''
    bits = get_bits(x)
    for bit in bits:
        magic = get_magic_power(bit)
        if magic:
            local_ebanina += magic + '|'
        else:
            local_ebanina += '-~0<<({})|'.format(ebanina(bit))
    return local_ebanina[:-1]