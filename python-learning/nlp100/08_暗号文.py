# def cipher(plain):
#     crypt = ''
#
#     for c in plain:
#         if c.islower():
#             crypt += chr(219-ord(c))
#         else:
#             crypt += c
#
#     return crypt

def cipher(plain):
    return ''.join([chr(219-ord(c)) if c.islower() else c for c in plain])

str = 'Alice was beginning to get very tired of sitting by her sister on the bank'

print(cipher(str))  # 暗号化
print(cipher(cipher(str)))  # 復号
