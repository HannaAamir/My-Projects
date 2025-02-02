import os
from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes
from cryptography.hazmat.primitives import hashes, hmac, serialization
from cryptography.hazmat.backends import default_backend
from cryptography.hazmat.primitives.asymmetric import padding, utils


class Receiver:
    def __init__(self, _recipient_name, _sender_name):
        self.decrypted_message = None
        self.recipient_name = _recipient_name
        self.sender_name = _sender_name
        self.private_key = None
        self.aes_key = None
        self.hmac_key = None
        self.iv_nonce = None
        self.encrypted_message = None
        self.combined_keys = None
        self.signature = None

    def load_private_key(self):
        filename = f"{self.recipient_name}_private_key.pem"
        with open(filename, "rb") as private_key_file:
            self.private_key = serialization.load_pem_private_key(
                private_key_file.read(),
                backend=default_backend(),
                password=None

            )

    def decrypt_keys(self):
        filename = "encrypted_keys.bin"
        with open(filename, "rb") as encrypted_keys_file:
            combined_encrypted_keys = encrypted_keys_file.read()

        self.combined_keys = self.private_key.decrypt(
            combined_encrypted_keys,
            padding.OAEP(
                mgf=padding.MGF1(algorithm=hashes.SHA256()),
                algorithm=hashes.SHA256(),
                label=None  # rarely used. Just leave it 'None'
            )
        )

        self.aes_key = self.combined_keys[:32]
        self.hmac_key = self.combined_keys[32:64]
        self.iv_nonce = self.combined_keys[64:80]

    def load_encrypted_message(self):
        filename = 'encrypted_message.bin'
        with open(filename, "rb") as encrypted_message_file:
            encrypted_message_with_signature = encrypted_message_file.read()
            signature_size = 2048 // 8  # RSA signature size (2048 bits)
            self.encrypted_message = encrypted_message_with_signature[:-signature_size]
            self.signature = encrypted_message_with_signature[-signature_size:]

    def verify_encrypted_contents(self):
        filename = "hmac_message.bin"
        with open(filename, "rb") as hmac_file:
            hmac_message = hmac_file.read()

        h = hmac.HMAC(self.hmac_key, hashes.SHA256(), backend=default_backend())

        # Update the HMAC with the message
        h.update(self.encrypted_message)
        current_hmac_message = h.finalize()

        return current_hmac_message == hmac_message

    def decrypt_message(self):
        aes_context = Cipher(algorithms.AES(self.aes_key),
                             modes.CTR(self.iv_nonce),
                             backend=default_backend())
        decryptor = aes_context.decryptor()
        decrypted_message = decryptor.update(self.encrypted_message).decode()
        return decrypted_message

    def verify_signature(self):
        filename = self.sender_name + "_public_key.pem"
        f = open(filename, "rb")
        sender_public_key = serialization.load_pem_public_key(
            f.read(),
            backend=default_backend()
        )
        chosen_hash = hashes.SHA256()
        hasher = hashes.Hash(chosen_hash, default_backend())
        hasher.update(self.combined_keys)
        digest = hasher.finalize()
        sender_public_key.verify(
            self.signature,
            digest,
            padding.PSS(
                mgf=padding.MGF1(hashes.SHA256()),
                salt_length=padding.PSS.MAX_LENGTH
            ),
            utils.Prehashed(chosen_hash)
        )

    def run(self):
        self.load_private_key()
        self.decrypt_keys()
        self.load_encrypted_message()
        if self.verify_encrypted_contents():
            print("Message verified.")
        else:
            print("Message not verified.")
            return
        self.decrypted_message = self.decrypt_message()
        print(self.decrypted_message)
        self.verify_signature()

if __name__ == "__main__":
    receiver = Receiver("alice", "bob")
    receiver.run()
