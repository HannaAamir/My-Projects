import os
import hashlib

from cryptography.hazmat.primitives.asymmetric.ec import derive_private_key
from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes
from cryptography.hazmat.primitives import padding, hmac, hashes, serialization
from cryptography.hazmat.backends import default_backend
from cryptography.hazmat.primitives.asymmetric import rsa
from cryptography.hazmat.primitives.asymmetric.padding import OAEP, MGF1
from cryptography.hazmat.primitives.asymmetric import padding
from cryptography.hazmat.primitives.kdf.pbkdf2 import PBKDF2HMAC
from cryptography.hazmat.primitives.serialization import load_pem_private_key, load_pem_public_key, Encoding, PublicFormat, PrivateFormat, NoEncryption
from cryptography.hazmat.primitives.hashes import SHA256
from getpass import getpass
from cryptography.hazmat.primitives import hashes
from cryptography.hazmat.primitives.asymmetric import rsa, padding
from cryptography.hazmat.backends import default_backend


# Constants
SALT_SIZE = 16
SALT_LENGTH = 16
KEY_LENGTH = 32 # ensures the ciphertext length matches for decoding 
ITERATIONS = 100000
PASSWORD_FILE = "passwords.txt"
MASTER_PASSWORD_FILE = "master_pass.txt"
BACKUP_KEY_FILE = "backup_key.txt"
PRIVATE_KEY_FILE = "private_key.pem"
PUBLIC_KEY_FILE = "public_key.pem"



# --- Signup Function ---
def signup():
    """
    This function creates a master password, for the password manager application. The master password is then hashed and securely saved,
    with an RSA encrypted backup.
    """
    
    print("=== Master Password Setup ===")
    master_password = getpass("Create a master password: ")
    confirm_password = getpass("Confirm the master password: ")

    if master_password != confirm_password:
        print("Passwords do not match. Please try again.")
        return signup()

    # Hash the master password
    salt, hashed_password = hash_master_password(master_password)
    save_master_password(salt, hashed_password)

    # Backup the master password key using RSA encryption
    backup_master_password(master_password)

    print("Master password created successfully and backed up securely.")


def encrypt_password(password, encryption_key):
    """
    This function encrypts a password using AES encryption in CTR (Counter) mode.

    Param:

        password (str): The plaintext password to be encrypted.
        encryption_key (bytes): A 16-byte, 24-byte, or 32-byte key for AES encryption.

    Returns:
        tuple: The encrypted password (bytes) and the nonce (bytes) used for encryption.
        
    """
    nonce = os.urandom(16)
    cipher = Cipher(algorithms.AES(encryption_key), modes.CTR(nonce))
    encryptor = cipher.encryptor()
    encrypted_password = encryptor.update(password.encode()) + encryptor.finalize()
    return encrypted_password, nonce


def decrypt_password(encrypted_password, nonce, encryption_key):
    """
    This function decrypts the encrypted password using AES decryption in CTR mode.
    
    Param:
    
        encrypted_password (bytes): The encrypted password to be decrypted.
        nonce (bytes): The nonce used during the encryption process.
        encryption_key (bytes): A 16-byte, 24-byte, or 32-byte key for AES decryption.
        
    Return:
        str: The decrypted password as a plaintext string.
        
    """
    cipher = Cipher(algorithms.AES(encryption_key), modes.CTR(nonce))
    decryptor = cipher.decryptor()
    decrypted_password = decryptor.update(encrypted_password) + decryptor.finalize()
    return decrypted_password.decode()


def add_hmac(data, hmac_key):
    """
    This function takes in a specified key for the data and generates an HMAC.

    Param:
        data (bytes): The data to be authenticated.
        hmac_key (bytes): The secret key used for HMAC generation.
        
    Returns:
        bytes: The HMAC value, which acts as a cryptographic signature for the data.
    
    """
    h = hmac.HMAC(hmac_key, hashes.SHA256(), backend=default_backend())
    h.update(data)
    return h.finalize()


def verify_hmac(data, hmac_key, expected_hmac):
    """
    This function compares and verifies the computed HMAC for the given HMAC and verifies if they match.

    Param:
        data (bytes): The data whose HMAC needs to be verified.
        hmac_key (bytes): The secret key used to verify the HMAC.
        expected_hmac (bytes): The given HMAC value to compare against.
    """
    
    h = hmac.HMAC(hmac_key, hashes.SHA256(), backend=default_backend())
    h.update(data)
    try:
        h.verify(expected_hmac)
        return True
    except Exception:
        return False


# --- Master Password Functions ---
def hash_master_password(master_password):
    """
    Ensures secure password storage by hashing the master password using using PBKDF2 with HMAC and SHA-256.

    Param:
        master_password (str): The plaintext master password to be hashed.
    Returns:
        tuple: A tuple containing the salt (bytes) and the hashed password (bytes).
    
    """
    salt = os.urandom(SALT_SIZE)
    hashed_password = hashlib.pbkdf2_hmac(
        "sha256", master_password.encode(), salt, 100000
    )
    return salt, hashed_password


def validate_master_password(input_password, stored_salt, stored_hash):
    """
    Compares the hash with a stored hash for validation of input password.

    Param:
        input_password (str): The plaintext password provided by the user for validation.
        stored_salt (bytes): The salt that was used when the master password was initially hashed.
        stored_hash (bytes): The previously stored hash of the master password.
    Returns:
        bool: True if the input password, when hashed, matches the stored hash; False otherwise.


    """
    hashed_input = hashlib.pbkdf2_hmac(
        "sha256", input_password.encode(), stored_salt, 100000
    )
    return hashed_input == stored_hash


def save_master_password(salt, hashed_password):
    with open(MASTER_PASSWORD_FILE, "w") as file:
        file.write(f"{salt.hex()}|{hashed_password.hex()}")


def load_master_password():
    with open(MASTER_PASSWORD_FILE, "r") as file:
        data = file.read().strip().split("|")
        return bytes.fromhex(data[0]), bytes.fromhex(data[1])


# --- Password Manager Functions ---
def load_passwords():
    if not os.path.exists(PASSWORD_FILE):
        return {}

    passwords = {}
    with open(PASSWORD_FILE, "r") as file:
        for line in file:
            service_name, encrypted_password, nonce, hmac_value = line.strip().split("|")
            passwords[service_name] = {
                "encrypted_password": bytes.fromhex(encrypted_password),
                "nonce": bytes.fromhex(nonce),
                "hmac": bytes.fromhex(hmac_value),
            }
    return passwords


def save_passwords(passwords):
    with open(PASSWORD_FILE, "w") as file:
        for service_name, data in passwords.items():
            file.write(
                f"{service_name}|{data['encrypted_password'].hex()}|{data['nonce'].hex()}|{data['hmac'].hex()}\n"
            )


def add_service(service_name, password, encryption_key, hmac_key):
    passwords = load_passwords()

    if service_name in passwords:
        print(f"Service '{service_name}' already exists.")
        return

    encrypted_password, nonce = encrypt_password(password, encryption_key)
    hmac_value = add_hmac(encrypted_password, hmac_key)
    passwords[service_name] = {
        "encrypted_password": encrypted_password,
        "nonce": nonce,
        "hmac": hmac_value,
    }
    save_passwords(passwords)
    print(f"Service '{service_name}' added successfully.")


def retrieve_service(service_name, encryption_key, hmac_key):
    passwords = load_passwords()

    if service_name not in passwords:
        print(f"Service '{service_name}' not found.")
        return

    record = passwords[service_name]
    encrypted_password = record["encrypted_password"]
    nonce = record["nonce"]
    hmac_value = record["hmac"]

    if not verify_hmac(encrypted_password, hmac_key, hmac_value):
        print("HMAC verification failed. Data integrity compromised.")
        return

    decrypted_password = decrypt_password(encrypted_password, nonce, encryption_key)
    print(f"Password for '{service_name}': {decrypted_password}")


def delete_service(service_name):
    passwords = load_passwords()

    if service_name not in passwords:
        print(f"Service '{service_name}' not found.")
        return

    del passwords[service_name]
    save_passwords(passwords)
    print(f"Service '{service_name}' deleted successfully.")


# --- Additional Features ---
def change_master_password(old_master_password):
    salt, stored_hash = load_master_password()

    if not validate_master_password(old_master_password, salt, stored_hash):
        print("Invalid master password.")
        return

    new_master_password = getpass("Enter a new master password: ")
    confirm_password = getpass("Confirm your new master password: ")

    if new_master_password != confirm_password:
        print("Passwords do not match.")
        return

    new_salt, new_hashed_password = hash_master_password(new_master_password)
    new_encryption_key = hashlib.scrypt(
        new_master_password.encode(), salt=b"key_salt", n=2**14, r=8, p=1, dklen=32
    )
    new_hmac_key = hashlib.scrypt(
        new_master_password.encode(), salt=b"hmac_salt", n=2**14, r=8, p=1, dklen=32
    )

    old_encryption_key = hashlib.scrypt(
        old_master_password.encode(), salt=b"key_salt", n=2**14, r=8, p=1, dklen=32
    )
    old_hmac_key = hashlib.scrypt(
        old_master_password.encode(), salt=b"hmac_salt", n=2**14, r=8, p=1, dklen=32
    )

    passwords = load_passwords()
    updated_passwords = {}

    for service_name, data in passwords.items():
        encrypted_password = data["encrypted_password"]
        nonce = data["nonce"]
        hmac_value = data["hmac"]

        if not verify_hmac(encrypted_password, old_hmac_key, hmac_value):
            print(f"Skipping {service_name}: HMAC verification failed.")
            continue

        decrypted_password = decrypt_password(encrypted_password, nonce, old_encryption_key)
        new_encrypted_password, new_nonce = encrypt_password(decrypted_password, new_encryption_key)
        new_hmac_value = add_hmac(new_encrypted_password, new_hmac_key)

        updated_passwords[service_name] = {
            "encrypted_password": new_encrypted_password,
            "nonce": new_nonce,
            "hmac": new_hmac_value,
        }

    save_passwords(updated_passwords)
    save_master_password(new_salt, new_hashed_password)
    print("Master password changed successfully.")


def generate_rsa_keys():
    private_key = rsa.generate_private_key(public_exponent=65537, key_size=2048)
    public_key = private_key.public_key()

    with open(PRIVATE_KEY_FILE, "wb") as priv_file:
        priv_file.write(private_key.private_bytes(Encoding.PEM, PrivateFormat.PKCS8, NoEncryption()))

    with open(PUBLIC_KEY_FILE, "wb") as pub_file:
        pub_file.write(public_key.public_bytes(Encoding.PEM, PublicFormat.SubjectPublicKeyInfo))

    return private_key, public_key


def backup_master_password(master_password):
   private_key, public_key = generate_rsa_keys()
   master_key = hashlib.scrypt(
       master_password.encode(), salt=b"key_salt", n=2**14, r=8, p=1, dklen=32
   )


   encrypted_master_key = public_key.encrypt(
       master_key, OAEP(mgf=MGF1(algorithm=SHA256()), algorithm=SHA256(), label=None)
   )


   with open(BACKUP_KEY_FILE, "wb") as backup_file:
       backup_file.write(encrypted_master_key)


   print("Master password backed up securely.")








def recover_master_password(encrypted_data_file="backup_key.txt", private_key_file="private_key.pem"):
       """
       Recover the master password using an encrypted backup file and a private key.

       Args:
           encrypted_data_file (str): The file containing the encrypted master password.
           private_key_file (str): The file containing the private key.

       Returns:
           str: The decrypted master password if recovery is successful.

       Raises:
           ValueError: If recovery fails.
       """
       try:
           # Load the private key from the file
           with open(private_key_file, "rb") as key_file:
               private_key = serialization.load_pem_private_key(
                   key_file.read(),
                   password=None,
                   backend=default_backend()
               )

           # Read the encrypted master key from the backup file
           with open(encrypted_data_file, "rb") as backup_file:
               encrypted_master_key = backup_file.read()
               print(f"Encrypted Master Key (length): {len(encrypted_master_key)}")

           # Decrypt the master key using the private key
           decrypted_master_key = private_key.decrypt(
               encrypted_master_key,
               padding.OAEP(
                   mgf=padding.MGF1(algorithm=hashes.SHA256()),
                   algorithm=hashes.SHA256(),
                   label=None
               )
           )

           # Attempt to decode the decrypted master key as UTF-8
           try:
               master_password = decrypted_master_key.decode()
               print(f"Master Password: {master_password}")
           except UnicodeDecodeError:
               master_password = None  # Set to None if not UTF-8
               print("The decrypted master password is not valid UTF-8 text. Displaying as hex:")
               print(f"Master Password (hex representation): {decrypted_master_key.hex()}")

           # Return the master password or raise an error if it's not valid
           if master_password is None:
               raise ValueError("The decrypted master password is not valid UTF-8 text.")

           return master_password

       except FileNotFoundError as e:
           raise FileNotFoundError(f"Error: {e.filename} not found.")
       except ValueError as ve:
           raise ve
       except Exception as e:
           raise ValueError(f"An unexpected error occurred during recovery: {e}")

   # Example usage:
if __name__ == "__main__":
       try:
           recovered_password = recover_master_password()
           print("Master Password Recovered:", recovered_password)
       except Exception as e:
           print(e)


def signout():
    print("Clearing sensitive data from memory...")
    # Here we simulate clearing sensitive data
    print("Cache cleared. Signing out... Goodbye!")
    exit()


# --- Main Functionality ---
def main():
    print("Welcome to the Password Manager!")
    while True:
        if not os.path.exists(MASTER_PASSWORD_FILE):
            print("No master password found. Creating a new one.")
            signup()

        master_password = getpass("Enter your master password to log in: ")
        salt, stored_hash = load_master_password()

        if not validate_master_password(master_password, salt, stored_hash):
            print("Invalid master password. Try again.")
            continue

        print("Login successful!")

        encryption_key = hashlib.scrypt(
            master_password.encode(), salt=b"key_salt", n=2**14, r=8, p=1, dklen=32
        )
        hmac_key = hashlib.scrypt(
            master_password.encode(), salt=b"hmac_salt", n=2**14, r=8, p=1, dklen=32
        )

        while True:
            print("\nOptions:")
            print("1. Add Service\n2. Retrieve Service\n3. Delete Service\n4. Change Master Password\n5. Recover Master Password\n6. Sign Out\n7. Exit")
            choice = input("Enter your choice: ")

            if choice == "1":
                service_name = input("Enter the service name: ")
                password = getpass("Enter the password: ")
                add_service(service_name, password, encryption_key, hmac_key)
            elif choice == "2":
                service_name = input("Enter the service name: ")
                retrieve_service(service_name, encryption_key, hmac_key)
            elif choice == "3":
                service_name = input("Enter the service name: ")
                delete_service(service_name)
            elif choice == "4":
                change_master_password(master_password)
            elif choice == "5":
                recover_master_password()
            elif choice == "6":
                signout()
            elif choice == "7":
                print("Exiting program.")
                exit()
            else:
                print("Invalid choice. Try again.")


if __name__ == "__main__":
    main()

