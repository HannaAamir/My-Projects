import os
from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes
from cryptography.hazmat.primitives import hashes, hmac, serialization
from cryptography.hazmat.backends import default_backend
from cryptography.hazmat.primitives.asymmetric import padding, rsa, utils

class Sender:
    def __init__(self, _sender_name, _recipient_name):
        self.sender_name = _sender_name
        self.recipient_name = _recipient_name

        self.recipient_public_key = None
        self.private_key = None

        self.aes_key = None
        self.hmac_key = None
        self.iv_nonce = None

        self.encrypted_aes_key = None
        self.encrypted_hmac_key = None
        self.encrypted_iv_nonce = None

        self.signature = None
        self.encrypted_keys = None
        self.encrypted_message = None

    def load_recipient_public_key(self):
        filename = self.recipient_name + "_public_key.pem"
        f = open(filename, "rb")
        self.recipient_public_key = serialization.load_pem_public_key(
            f.read(),
            backend=default_backend()
        )

    def load_sender_private_key(self):
        filename = self.sender_name + "_private_key.pem"
        with open(filename, "rb") as private_key_file_object:
            self.private_key = serialization.load_pem_private_key(
                private_key_file_object.read(),
                backend=default_backend(),
                password=None
            )

    def generate_aes_hmac_nonce_keys(self):
        self.aes_key = os.urandom(32)
        self.hmac_key = os.urandom(32)
        self.iv_nonce = os.urandom(16)

    def sign_keys(self):
        combined_key = self.aes_key + self.hmac_key + self.iv_nonce
        chosen_hash = hashes.SHA256()
        hasher = hashes.Hash(chosen_hash, default_backend())
        hasher.update(combined_key)
        digest = hasher.finalize()


        self.signature = self.private_key.sign(
            digest,
            padding.PSS(
                mgf=padding.MGF1(hashes.SHA256()),
                salt_length=padding.PSS.MAX_LENGTH
            ),
            utils.Prehashed(chosen_hash)
        )

    def encrypt_keys(self):
        combined_key = self.aes_key + self.hmac_key + self.iv_nonce
        self.encrypted_keys = self.recipient_public_key.encrypt(
            combined_key,
            padding.OAEP(
                mgf=padding.MGF1(algorithm=hashes.SHA256()),
                algorithm=hashes.SHA256(),
                label=None  # rarely used. Just leave it 'None'
            )
        )

    def save_keys(self):
        filename = "encrypted_keys.bin"
        with open(filename, 'wb') as file:
            file.write(self.encrypted_keys)

    def encrypt_message(self, message):
        aesCipher = Cipher(algorithms.AES(self.aes_key),
                           modes.CTR(self.iv_nonce),
                           backend=default_backend())
        aesEncryptor = aesCipher.encryptor()
        self.encrypted_message = aesEncryptor.update(message.encode())

    def generate_and_save_hmac(self):
        h = hmac.HMAC(self.hmac_key, hashes.SHA256(), backend=default_backend())

        # Update the HMAC with the message
        h.update(self.encrypted_message)

        # Finalize the HMAC computation and print the result in hexadecimal format
        filename = "hmac_message.bin"
        with open(filename, "wb") as file_out:
            file_out.write(h.finalize())

    def save_encrypted_message(self):
        filename = "encrypted_message.bin"
        with open(filename, "wb") as file_out:
            file_out.write(self.encrypted_message + self.signature)

    def run(self):
        self.load_recipient_public_key()
        self.load_sender_private_key()
        self.generate_aes_hmac_nonce_keys()
        self.sign_keys()
        self.encrypt_keys()
        self.save_keys()
        self.encrypt_message("I think math is the language of the universe.")
        self.generate_and_save_hmac()
        self.save_encrypted_message()


if __name__ == "__main__":
    sender = Sender('bob', 'alice')
    sender.run()





