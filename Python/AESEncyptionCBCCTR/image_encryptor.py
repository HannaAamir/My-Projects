# Start with the advanced CBC manager or simple CBC manager code in Section3 Repo.
from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes
from cryptography.hazmat.backends import default_backend
from cryptography.hazmat.primitives import padding
import os


class ECBImageEncryptor:
    def __init__(self, key):
        self.key = key
        aes_context = Cipher(algorithms.AES(key),
                             modes.ECB(),
                             backend=default_backend())
        self.encryptor = aes_context.encryptor()
        self.decryptor = aes_context.decryptor()
        self.padder = padding.PKCS7(128).padder()
        self.unpadder = padding.PKCS7(128).unpadder()

    def encrypt_image(self, input_image_path, output_image_path):
        header, body = self.read_image(input_image_path)
        padded_body = self.padder.update(body) + self.padder.finalize()
        encrypted_body = self.encryptor.update(padded_body) + self.encryptor.finalize()
        self.write_image(output_image_path, header, encrypted_body)

    def decrypt_image(self, encrypted_image_path, output_image_path):
        header, encrypted_body = self.read_image(encrypted_image_path)
        decrypted_body = self.decryptor.update(encrypted_body) + self.decryptor.finalize()
        unpadded_body = self.unpadder.update(decrypted_body) + self.unpadder.finalize()
        self.write_image(output_image_path, header, unpadded_body)

    def read_image(self, image_path):
        with open(image_path, 'rb') as f:
            header = f.read(54)  # Read the first 54 bytes (header)
            body = f.read()
        return header, body

    def write_image(self, image_path, header, body):
        with open(image_path, 'wb') as f:
            f.write(header)
            f.write(body)


class CBCImageEncryptor:
    def __init__(self, key):
        self.key = key

    def encrypt_image(self, input_image_path, output_image_path):
        iv = os.urandom(16)  # Generate a random IV for CBC mode
        aes_context = Cipher(algorithms.AES(self.key),
                             modes.CBC(iv),
                             backend=default_backend())
        encryptor = aes_context.encryptor()
        padder = padding.PKCS7(128).padder()

        header, body = self.read_image(input_image_path)
        padded_body = padder.update(body) + padder.finalize()
        encrypted_body = encryptor.update(padded_body) + encryptor.finalize()

        # Write the IV at the beginning of the encrypted file
        with open(output_image_path, 'wb') as f:
            f.write(iv)
            f.write(header)
            f.write(encrypted_body)

    def decrypt_image(self, encrypted_image_path, output_image_path):
        with open(encrypted_image_path, 'rb') as f:
            iv = f.read(16)  # Read the first 16 bytes for IV
            header = f.read(54)  # Read the next 54 bytes (header)
            encrypted_body = f.read()

        aes_context = Cipher(algorithms.AES(self.key),
                             modes.CBC(iv),
                             backend=default_backend())
        decryptor = aes_context.decryptor()
        unpadder = padding.PKCS7(128).unpadder()

        decrypted_body = decryptor.update(encrypted_body) + decryptor.finalize()
        unpadded_body = unpadder.update(decrypted_body) + unpadder.finalize()
        self.write_image(output_image_path, header, unpadded_body)

    def read_image(self, image_path):
        with open(image_path, 'rb') as f:
            header = f.read(54)  # Read the first 54 bytes (header)
            body = f.read()
        return header, body

    def write_image(self, image_path, header, body):
        with open(image_path, 'wb') as f:
            f.write(header)
            f.write(body)


class CTRImageEncryptor:
    def __init__(self, key):
        self.key = key

    def encrypt_image(self, input_image_path, output_image_path):
        nonce = os.urandom(16)  # Generate a random nonce for CTR mode
        aes_context = Cipher(algorithms.AES(self.key),
                             modes.CTR(nonce),
                             backend=default_backend())
        encryptor = aes_context.encryptor()

        header, body = self.read_image(input_image_path)
        ciphertext = encryptor.update(body) + encryptor.finalize()

        # Write the nonce at the beginning of the encrypted file
        with open(output_image_path, 'wb') as f:
            f.write(nonce)
            f.write(header)
            f.write(ciphertext)

    def decrypt_image(self, encrypted_image_path, output_image_path):
        with open(encrypted_image_path, 'rb') as f:
            nonce = f.read(16)  # Read the first 16 bytes for nonce
            header = f.read(54)  # Read the next 54 bytes (header)
            ciphertext = f.read()

        aes_context = Cipher(algorithms.AES(self.key),
                             modes.CTR(nonce),
                             backend=default_backend())
        decryptor = aes_context.decryptor()

        decrypted_body = decryptor.update(ciphertext) + decryptor.finalize()
        self.write_image(output_image_path, header, decrypted_body)

    def read_image(self, image_path):
        with open(image_path, 'rb') as f:
            header = f.read(54)  # Read the first 54 bytes (header)
            body = f.read()
        return header, body

    def write_image(self, image_path, header, body):
        with open(image_path, 'wb') as f:
            f.write(header)
            f.write(body)


def main():
    symmetric_key = os.urandom(32)  # Use a random 256-bit key for AES

    # Specify input and output image paths
    input_image_path = 'top_secret.bmp'  # Replace with your input BMP file
    ecb_output_path = 'ecb_encrypted_image.bmp'
    cbc_output_path = 'cbc_encrypted_image.bmp'
    ctr_output_path = 'ctr_encrypted_image.bmp'

    # ECB Mode
    ecb_encryptor = ECBImageEncryptor(symmetric_key)
    ecb_encryptor.encrypt_image(input_image_path, ecb_output_path)
    ecb_encryptor.decrypt_image(ecb_output_path, 'ecb_decrypted_image.bmp')

    # CBC Mode
    cbc_encryptor = CBCImageEncryptor(symmetric_key)
    cbc_encryptor.encrypt_image(input_image_path, cbc_output_path)
    cbc_encryptor.decrypt_image(cbc_output_path, 'cbc_decrypted_image.bmp')

    # CTR Mode
    ctr_encryptor = CTRImageEncryptor(symmetric_key)
    ctr_encryptor.encrypt_image(input_image_path, ctr_output_path)
    ctr_encryptor.decrypt_image(ctr_output_path, 'ctr_decrypted_image.bmp')


if __name__ == "__main__":
    main()
