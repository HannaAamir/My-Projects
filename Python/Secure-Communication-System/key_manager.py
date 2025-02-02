from cryptography.hazmat.backends import default_backend
from cryptography.hazmat.primitives.asymmetric import rsa
from cryptography.hazmat.primitives import serialization

def generate_private_key():
    """
    Generate an RSA pruvate key.
    Returns:
        private_key (rsa.RSAPrivateKey): The RSA private key.
    """
    private_key = rsa.generate_private_key(
        public_exponent=65537,
        key_size=2048,
        backend=default_backend()
    )

    return private_key



def save_keys_to_file(key, name):
    """
    Save an RSA key pair to files.
    Args:
        key (rsa.RSAPrivateKey): The RSA private key to save.
        name (str): The base name for the files.
    """
    public_key = key.public_key()
    public_key_bytes = public_key.public_bytes(
        encoding=serialization.Encoding.PEM,  # Use PEM encoding for compatibility
        format=serialization.PublicFormat.SubjectPublicKeyInfo  # Standard public key format
    )

    filename = name + "_public_key.pem"
    encryption_file = open(filename, "w")
    encryption_file.write(public_key_bytes.decode())
    encryption_file.close()




    with open(f"{name}_public_key.pem", "w") as public_file:
        public_file.write(public_key_bytes.decode())  # Decode bytes to string for writing

    private_key_bytes = key.private_bytes(
        encoding=serialization.Encoding.PEM,  # Use PEM encoding for private key
        format=serialization.PrivateFormat.TraditionalOpenSSL,  # Standard private key format
        encryption_algorithm=serialization.NoEncryption()  # Do not encrypt the private key
    )

    filename = name + "_private_key.pem"
    encryption_file = open(filename, "w")
    encryption_file.write(private_key_bytes.decode())
    encryption_file.close()

def main():
    private_key = generate_private_key()
    private_key_2 = generate_private_key()
    save_keys_to_file(private_key, 'alice')
    save_keys_to_file(private_key_2, 'bob')

    print("RSA key pairs generated and saved for Alice and Bob.")

if __name__ == "__main__":
    main()
