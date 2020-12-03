import random

def BYTE(num):
    hex_num = hex(num).replace('0x','')
    if len(hex_num) <= 2:
        return hex_num
    
    return hex_num[-2:]


one = hex(random.randint(0x1000,0xffff)).replace('0x','')
xor_increase = 0x4f

xor_sum = 0
two = ''
for i in one:
    xor_increase+=4

    xor_num = xor_increase ^ ord(i)
    two += chr(xor_num)
    xor_sum += xor_num-0x30


second_xor_sum = xor_sum+0xe2
three = BYTE(xor_sum)+BYTE(second_xor_sum)

result = one+two+three.upper()
print(result)