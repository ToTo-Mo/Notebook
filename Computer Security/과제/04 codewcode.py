import base64
import hashlib
from Crypto.Cipher import AES


BS = 16
pad = (lambda s: s + (BS - len(s) % BS) * chr(BS - len(s) % BS).encode())
unpad = (lambda s: s[:-ord(s[len(s)-1:])])


class AESCipher(object):
    def __init__(self, key):
        self.key = hashlib.sha256(key.encode()).digest()

    def encrypt(self, message):
        message = message.encode()
        raw = pad(message)
        cipher = AES.new(self.key, AES.MODE_CBC, self.__iv())
        enc = cipher.encrypt(raw)
        return base64.b64encode(enc).decode('utf-8')

    def decrypt(self, enc):
        enc = base64.b64decode(enc)
        cipher = AES.new(self.key, AES.MODE_CBC, self.__iv())
        dec = cipher.decrypt(enc)
        return unpad(dec).decode('utf-8')

    def __iv(self):
        return chr(0) * 16


if __name__ == "__main__":
    key = "abcdefghijklmnop"
    plaintext=""
    cipher = AESCipher(key)

    filepath = r'Computer Security\과제\04 plaintext.txt'
    with open(filepath,'r',encoding='utf-8') as file:

        for line in file:
            plaintext += line

    encryption = cipher.encrypt(plaintext)

    decryption = cipher.decrypt(encryption)

    print("key : ",key)
    print("encryption : ",encryption)
    print("decryption : ",decryption)