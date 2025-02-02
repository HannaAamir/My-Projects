# Assignment 5: Encryption, Authentication, and Integrity System for Alice and Bob

### Objective
In this assignment, you will build a secure communication system that incorporates encryption, integrity, and authentication for two users: Alice and Bob. The goal is to implement a system where each user can securely send and receive the content of a file using file-based communication, ensuring confidentiality, integrity, and authenticity through encryption, digital signatures, and HMACs.

This assignment covers RSA key generation, message signing, encryption, decryption, signature verification, secure AES key exchange, HMAC generation and verification, and file-based communication between Alice and Bob.

Refer to the provided example in [section5](https://github.com/applied-crypto-cu-denver/section5/blob/main/sign_then_encrypt.py) as a starting point. You can also refer to [section6](https://github.com/applied-crypto-cu-denver/section6/blob/main/rsa_exchange.py) for another example of key transport using RSA. The assignment builds on concepts from Assignment 4, so feel free to adopt and adapt relevant code as needed.

---

### Story Context (Scenario)
Alice and Bob need to securely exchange the content of a file (`secret.txt`) over an insecure channel, ensuring the confidentiality, integrity, and authenticity of the exchanged data. We use files to simulate network communications between Alice and Bob. 

---

### Assignment Requirements

#### 1. Key Generation (Key Manager Program - `key_manager.py`):
- **RSA Key Pair Generation for Each Operator (Alice and Bob)**:  
  The key manager program will generate a pair of RSA public and private keys for both Alice and Bob.
- **Saving Keys to Disk**:  
  Each RSA public and private key pair must be saved under filenames that reflect the operator's name (e.g., `alice_public_key.pem`, `bob_private_key.pem`).

#### 2. File Sending (Sender Program - `sender.py`):
- **Loading the Sender’s Private Key and Recipient’s Public Key**:  
  The program will load the sender’s private RSA key and the recipient’s public RSA key from the saved files.
- **AES/HMAC Key and IV (Nonce) Generation**:  
  Within the `sender.py` program, generate a random AES key, a random HMAC key, and an IV (nonce) using a secure random number generator. These values will be used for encrypting the file content and ensuring its integrity.
- **Signing the Keys**:  
  The sender will sign the concatenated AES key, IV, and HMAC key using their private RSA key to generate a signature. This signature will later verify the authenticity of the key materials. This is called the `signature`.
- **Encrypting Keys/IV using RSA**:  
  Concatenate the AES key, HMAC key, and IV, then encrypt them using the recipient’s RSA public key to ensure only the recipient can decrypt and access the AES and HMAC keys. Save the encrypted key material to `encrypted_keys.bin`.
- **File Content Encryption using AES**:  
  Concatenate the sender’s name, the original file content, a timestamp (current time), and the signature. Encrypt this data using AES in **CTR mode** with the generated AES key and IV. We call this `encrypted_message`.
- **HMAC Generation**:  
  Calculate an HMAC over the `encrypted message` using the generated HMAC key. Save this HMAC to a file named `hmac_message.bin`.
- **Saving Encrypted Data**:  
  Save the encrypted message to a file named `encrypted_message.bin`.

#### 3. File Receiving (Receiver Program - `receiver.py`):
- **Loading the Receiver's Private Key**:  
  The recipient (e.g., Bob) will load their private RSA key to decrypt the incoming encrypted data.
- **Decrypting the AES Key, HMAC Key, and IV**:  
  The recipient will decrypt the AES key, HMAC key, and IV using their private RSA key from the `encrypted_keys.bin` file.
- **HMAC Verification**:  
  The receiver will generate an HMAC of the encrypted file content and verify that it matches the HMAC provided in `hmac.bin` to confirm the integrity of the file content.
- **File Content Decryption**:  
  Use the decrypted AES key and IV to decrypt the data, extracting the sender’s name, the file content, the signature, and the timestamp.
- **Signature Verification**:  
  Load the sender’s public RSA key and verify the signature over the file content to ensure the integrity and authenticity of the communication.

#### 4. Testing and Validation:
- Both the `sender.py` and `receiver.py` programs must include test cases that demonstrate successful encryption, decryption, HMAC verification, and signature verification of the file content.
- Include tests that cover cases where:
  - The HMAC verification fails (e.g., due to tampered data): adding one additional test case to cover the scenario where the `encrypted_message.bin` file is tampered with, leading to failed HMAC verification.
  - The signature verification fails (e.g., due to incorrect sender’s public key).
  - All verifications pass, showing that the file content’s integrity and authenticity are confirmed.
  - Use numbers (e.g. `encrypted_message1.bin`, `encrypted_message2.bin`, ...) to distinguish between different cases. 

---

### Deliverables:

1. **Key Manager Program (`key_manager.py`)**:  
   Code that generates RSA keys for Alice (sender) and Bob (receiver) and saves them to files.

2. **Sender Program (`sender.py`)**:  
   Code that signs the AES key, IV, and HMAC key, encrypts them using RSA, encrypts the file content using AES in CTR mode, and generates and saves an HMAC for the encrypted file content.

3. **Receiver Program (`receiver.py`)**:  
   Code that decrypts the AES key, IV, and HMAC key using RSA, verifies the HMAC, decrypts the file content, and verifies the signature.

4. **Encrypted Files**:  
   - `encrypted_keys.bin`: Encrypted AES key, HMAC key, and IV (encrypted using the recipient's RSA public key).
   - `encrypted_message.bin`: The AES-encrypted file content containing sender’s name, file content, timestamp, and signature.
   - `hmac_message.bin`: HMAC of the encrypted file content.

5. **Report (`assignment_report.md`)**:  
   A complete report that provides a step-by-step description of the process, explaining the need for each step. Provide details on the testing and validation approach, particularly for signature verification and HMAC verification.
   Answer the following questions in your report:
   - What is the purpose of including a timestamp in the file content?
   - Are we using Sign-then-Encrypt here, or Encrypt-then-Sign? Explain.
   - Are we using Encrypt-then-MAC here, or MAC-then-Encrypt? Explain.
   - Why are we using both AES and RSA? Why not encrypt the file using RSA directly?

---

### Grading Rubric:

1. **Correctness (50%)**:
   - Accurate implementation of RSA key generation, signing, AES key exchange, encryption, and HMAC generation.
   - Proper use of AES encryption in **CTR mode**.
   - Correct verification of signatures, HMACs, and decryption of the file content.

2. **Code Quality (20%)**:
   - Clear, readable, and well-documented code.
   - Proper use of functions and modular design.

3. **Testing (20%)**:
   - Adequate test cases provided.
   - Test results demonstrate the correctness of encryption, decryption, HMAC, and signature verification.
   - Includes cases for failed HMAC and signature verification.

4. **Documentation (10%)**:
   - Explanation of the program design in the report.
   - Clear description of file-based communication, signature verification, AES key exchange, encryption, and HMAC verification.

