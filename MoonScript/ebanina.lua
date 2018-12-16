local get_magic_power
get_magic_power = function(x)
  local _exp_0 = x
  if 0 == _exp_0 then
    return '-~0'
  elseif 1 == _exp_0 then
    return '-~0<<-~0'
  elseif 2 == _exp_0 then
    return '-~0<<(-~0<<-~0)'
  elseif 4 == _exp_0 then
    return '-~0<<(-~0<<(-~0<<-~0))'
  elseif 16 == _exp_0 then
    return '-~0<<(-~0<<(-~0<<(-~0<<-~0)))'
  elseif 65536 == _exp_0 then
    return '-~0<<(-~0<<(-~0<<(-~0<<(-~0<<-~0))))'
  else
    return nil
  end
end
local get_bit_cnt
get_bit_cnt = function(x)
  return math.floor(math.log(x, 2)) + 1
end
local get_bits
get_bits = function(x)
  return (function()
    local _accum_0 = { }
    local _len_0 = 1
    for i = 0, get_bit_cnt(x) - 1 do
      local _continue_0 = false
      repeat
        if x & (1 << i) ~= 0 then
          _accum_0[_len_0] = i
        else
          _continue_0 = true
          break
        end
        _len_0 = _len_0 + 1
        _continue_0 = true
      until true
      if not _continue_0 then
        break
      end
    end
    return _accum_0
  end)()
end
local ebanina
ebanina = function(x)
  local local_ebanina = ''
  local _list_0 = get_bits(x)
  for _index_0 = 1, #_list_0 do
    local bit = _list_0[_index_0]
    local magic = get_magic_power(bit)
    if magic then
      local_ebanina = local_ebanina .. (magic .. '|')
    else
      local_ebanina = local_ebanina .. ('-~0<<(' .. ebanina(bit) .. ')|')
    end
  end
  local_ebanina = local_ebanina:sub(1, -2)
  return local_ebanina
end
print(ebanina(12))
return {
  ebanina = ebanina
}
