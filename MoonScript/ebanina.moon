get_magic_power = (x) ->
    switch x
        when 0     then '-~0'
        when 1     then '-~0<<-~0'
        when 2     then '-~0<<(-~0<<-~0)'
        when 4     then '-~0<<(-~0<<(-~0<<-~0))'
        when 16    then '-~0<<(-~0<<(-~0<<(-~0<<-~0)))'
        when 65536 then '-~0<<(-~0<<(-~0<<(-~0<<(-~0<<-~0))))'
        else            nil

get_bit_cnt = (x) -> math.floor(math.log(x, 2)) + 1

get_bits = (x) ->
    return for i = 0, get_bit_cnt(x) - 1
        if x & (1 << i) != 0 then i
        else continue

ebanina = (x) ->
    local_ebanina = ''
    for bit in *get_bits x
        magic = get_magic_power bit
        if magic then local_ebanina ..= magic .. '|'
        else          local_ebanina ..= '-~0<<(' .. ebanina(bit) .. ')|'
    local_ebanina = local_ebanina\sub 1, -2 -- remove last character
    return local_ebanina

{:ebanina}