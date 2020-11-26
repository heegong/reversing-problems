import dis

def stage(st :str):
    ls  = []
    xor_key = 0x51
    for i in list(st):
        ls.append(chr(ord(i)^xor_key^0x1f))
    f = open("answer.txt",'w',encoding='utf-8')
    f.write(''.join(ls))
    f.close()


# FLAG{Xor_RanS03MWar3_Pyth0n_D1s_reversing}
dis.dis(stage)