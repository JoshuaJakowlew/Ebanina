function getMagicPower(x)
{
    switch (x)
    {
        case 0:     return '-~0';
        case 1:     return '-~0<<-~0';
        case 2:     return '-~0<<(-~0<<-~0)';
        case 4:     return '-~0<<(-~0<<(-~0<<-~0))';
        case 16:    return '-~0<<(-~0<<(-~0<<(-~0<<-~0)))';
        case 65535: return '-~0<<(-~0<<(-~0<<(-~0<<(-~0<<-~0))))';
        default:    return null;
    }
}

function bitcnt(x)
{
    return Math.floor(Math.log2(x)) + 1;
}

function getBits(x)
{
    const bits = [];
    const maxIter = bitcnt(x);
    for (var i = 0; i < maxIter; ++i)
        if (x & (1 << i))
            bits.push(i);
    return bits;
}

function ebanina(x)
{
    let local_ebanina = '';
    const bits = getBits(x);
    bits.forEach(bit => {
        const magic = getMagicPower(bit);
        local_ebanina += magic ? magic + '|'
                               : `-~0<<(${ebanina(bit)})|`;
    });

    return local_ebanina.slice(0, -1);
}