# **Assignment 5 Report**

---

## 1. Introduction

Provide a brief overview of your approach to this assignment. Explain the main goal and what you aimed to achieve with your solution.

---

## 2. Coding Process

### 2.1 Key Generation (`key_manager.py`)
- Describe how you implemented RSA key generation for Alice and Bob.
- Explain any challenges you encountered and how you resolved them.

I implemented by deciding to first generate the key(s) and then save it to seperate files. Firstly, I generated a private key since a public key can be derived from a private key. I acocmplished this by choosing a secure public exponent and and a large secure key size. I decided to derive my private key in the function meant to save the keys to the file to reduce redundancy and prevent any mismatch when passing key paramters in the save-to-file function. The main function then generates two private keys - one each for Alice and Bob. 

Challenges:

The primary challenge was developing a solid understanding of encoding for the keys and files. RSA keys are binary data; consequently, converting them to strings for writing to files reuqired careful handling of encoding and decoding. To resolve this, I used the .decode() method to convert the key bytes to strings before writing, ensuring proper representation in PEM files.

### 2.2 File Sending (`sender.py`)
- Outline the process you used to load and generate the required keys and IV (nonce).
- Explain how you signed and encrypted the keys, IV, and file content.
- Describe the role of HMAC and how you generated it for the encrypted content.



The sender loads their private key (bob_private_key.pem) using the load_sender_private_key() method.
The recipient’s public key (alice_public_key.pem) is loaded using the load_recipient_public_key() method. This ensures secure encryption of the symmetric keys.


The method generate_aes_hmac_nonce_keys() generates:
A 32-byte AES encryption key for securing the message,
A 32-byte HMAC key for message integrity verification,
and a 16-byte IV (nonce) for the AES cipher in CTR mode to ensure unique encryption for each message.

**Signing the Keys:**

* The AES key, HMAC key, and IV were concatenated into a single combined_key.
* A SHA-256 hash digest of the combined_key was generated.
* The sender's private key signs this digest using the RSA algorithm with padding and a pre-hashed mechanism for enhanced security (sign_keys() method).
* This signature ensures the integrity of the keys and IV and confirms that the sender created them.

**Encrypting the Keys:**

* The combined_key is encrypted using the recipient’s RSA public key (encrypt_keys() method).
* Security for the encryption is provided using OAEP padding with sha 256.
* The encrypted keys are saved in the file encrypted_keys.bin for sending.

**Encrypting the File Content:**

* The message is encrypted with the AES cipher in CTR mode, using the generated AES key and IV (encrypt_message() method).
* This ensures confidentiality while allowing efficient encryption of messages of arbitrary length.

Role of HMAC:

HMAC ensures the integrity and authenticity of the encrypted message.
Any tampering with the encrypted message would result in an invalid HMAC during verification.


HMAC Generation:

A SHA-256 HMAC is computed on the encrypted message using the derived HMAC key (generate_and_save_hmac() method).
The resulting HMAC is saved in the file hmac_message.bin for secure transfer alongside the encrypted message.

### 2.3 File Receiving (`receiver.py`)
- Describe the steps taken to load and decrypt the keys, IV, and content.
- Explain how you verified the HMAC and signature to ensure integrity and authenticity.
- Outline any issues encountered during decryption and verification.

The sender loads their private key (bob_private_key.pem) using the load_sender_private_key() method.
The recipient’s public key (alice_public_key.pem) is loaded using the load_recipient_public_key() method. This ensures secure encryption of the symmetric keys.

**Loading the Private Key:**

The recipient loads their private RSA key from a PEM file (alice_private_key.pem) using the load_private_key() method. This private key is essential for decrypting the encrypted keys.
**Decrypting the Keys:**

The encrypted keys are read from the file encrypted_keys.bin.
Using the recipient's private key, the concatenated keys (aes_key, hmac_key, and iv_nonce) are decrypted via RSA with OAEP padding in the decrypt_keys() method.
The concatenated keys are then split into their respective components:
aes_key (first 32 bytes) for AES encryption.
hmac_key (next 32 bytes) for integrity verification.
iv_nonce (last 16 bytes) for AES-CTR mode.

**Loading the Encrypted Message:**

The encrypted message and signature are read from the file encrypted_message.bin in the load_encrypted_message() method.
The RSA signature is separated from the encrypted message using the size of the RSA signature (2048 bits or 256 bytes).


Decrypting the Content:

Using the AES key and IV, the encrypted message is decrypted with AES in CTR mode via the decrypt_message() method.
The resulting plaintext is returned and stored as the decrypted_message.

**HMAC Verification:**

The HMAC of the encrypted message is read from hmac_message.bin.
A new HMAC is computed using the HMAC key and the encrypted message in the verify_encrypted_contents() method.


The two HMACs are compared:


If they match, the message integrity is verified.
Otherwise, a warning is raised that the message has been tampered with.


**Signature Verification:**

The concatenated keys (aes_key, hmac_key, and iv_nonce) are hashed using SHA-256.
The sender's public key is loaded from bob_public_key.pem.
The sender's RSA signature is verified using the hashed value of the concatenated keys and RSA with PSS padding in the verify_signature() method.
A valid signature confirms that the keys originated from the sender and have not been altered.


**HMAC Mismatch:**

If the HMAC of the received encrypted message does not match the computed HMAC, it indicates potential tampering or corruption during transmission.
Signature Verification Failure:

If the RSA signature does not match the hashed value of the concatenated keys, it could mean:
The keys have been tampered with.
An incorrect sender public key was loaded for verification.
The signature was not properly generated by the sender.
**Decryption Issues:**

If the decrypt_message() method fails, possible reasons include:
Incorrect decryption keys due to tampering with encrypted_keys.bin.
**The AES key or IV is mismatched or corrupted.
Encoding/Decoding Errors:**

Issues could arise if the decrypted message is not valid UTF-8 text, leading to decoding errors.



## 3. Testing and Validation

### 3.1 Testing Process
- Describe your approach to testing each component of the assignment.
- List the test cases you created and their purposes (e.g., HMAC verification, signature verification).

### 3.2 Validation Results
- Summarize the results of your test cases.
- Include details on any failed cases and explain how you resolved them.

| Test Case                          | Purpose                                              | Result                                          |
|------------------------------------|------------------------------------------------------|-------------------------------------------------|
| Valid Encryption and Decryption    | Ensure message can be decrypted by the receiver.     | Receiver retrieves the original plaintext.      |
| HMAC Verification                  | Confirm the integrity of the encrypted message.      | HMAC verification passes.                       |
| Tampered Encrypted Message         | Test if receiver identifies message tampering.       | Receiver detects tampering and rejects it.      |
| Invalid Signature Verification     | Test if receiver detects an invalid signature.       | Signature verification fails.                   |
| Missing Keys or Files              | Check how the program handles missing files.         | Program reports missing files and exits safely. |
| Key Reuse Prevention               | Ensure new keys are generated for each message.      | Different keys are used for each run.           |
| Large File Handling                | Verify functionality with large file inputs.         | Encrypted and decrypted files match perfectly.  |


Decoding Errors:

Issue: Decryption produced non-UTF-8 output for invalid or tampered ciphertext.
Resolution: Implemented error handling for decoding to handle such cases gracefully.
---

## 4. Questions and Explanations

**1. What is the purpose of including a timestamp in the file content?**  

Including a timestamp in the file content helps ensure data freshness and protects against replay attacks. It adds a time reference, allowing the receiver to verify that the data is recent and hasn't been captured and resent by an attacker at a later time. This can prevent situations where an old or obsolete file is reused to impersonate a valid communication.
**2. Are we using Sign-then-Encrypt or Encrypt-then-Sign in this assignment? Explain why this approach was chosen.**  
In this assignment, we are using Sign-then-Encrypt. This approach was chosen because it allows us to provide data integrity and authenticity guarantees while still maintaining the confidentiality of the data. By signing first, we ensure that any tampering with the data can be detected by the recipient. Encrypting afterward ensures that the data remains secure and protected from unauthorized access.

**3. Are we using Encrypt-then-MAC or MAC-then-Encrypt in this assignment? Explain the choice and its implications.**  
We are using Encrypt-then-MAC in this assignment. This approach is preferred because it ensures that the integrity and authenticity of the encrypted content are verified after decryption. Encrypt-then-MAC guarantees that an attacker cannot modify the encrypted data without detection. This choice is more secure than MAC-then-Encrypt, as it prevents an attacker from modifying the encrypted data and still producing a valid MAC.
**4. Why are we using both AES and RSA? Why not use RSA to encrypt the entire file content directly?**  
We use AES for encrypting the file content and RSA for encrypting the AES key and other critical components because of efficiency and performance considerations. RSA is computationally expensive, especially for large data sizes, while AES is fast and efficient for bulk data encryption. Using RSA to encrypt the entire file content would be inefficient and slow, whereas AES handles this well while RSA securely manages key exchange and authentication.



**5. Explain the difference between using RSA for encryption/decryption and using RSA for digital signing/verification.**  
RSA for encryption/decryption is used for securing data transmission. When a sender encrypts data using the recipient’s public key, only the recipient can decrypt it using their private key, ensuring confidentiality. RSA for digital signing/verification, on the other hand, ensures data integrity and authenticity. The sender signs the data using their private key, and the recipient uses the sender’s public key to verify that the data has not been altered and that it was indeed sent by the claimed sender.
**6. Explain why we sign first and then encrypt, instead of encrypting first and then signing.**  
Signing first and then encrypting provides better security guarantees. If we sign before encrypting, the signature is protected by the encryption and cannot be altered or removed without detection. If we encrypted first and then signed, an attacker could modify the encrypted data and re-sign it, which would compromise the integrity check. By signing first, we ensure that any tampering with the data can be detected when the receiver decrypts and verifies the signature.

---

## 5. Reflection

**1. What are three key lessons you learned from this assignment?**  
*Answer here*
ntegration of Cryptographic Primitives: Successfully combining AES for bulk data encryption, RSA for secure key exchange, and HMAC for message integrity was crucial in understanding the interplay of different cryptographic mechanisms.
Importance of Order in Security Operations: The sequence of operations (e.g., sign-then-encrypt or encrypt-then-MAC) significantly impacts the security guarantees of a system. This assignment reinforced the rationale for using these approaches.
Debugging Cryptographic Systems: Diagnosing issues like mismatched HMACs or incorrect padding schemes highlighted the importance of careful attention to detail and comprehensive testing when implementing security protocols.

**2. How would you approach a similar problem differently in the future?**  
*Answer here*

---

## 6. Conclusion

Summarize the main points of your solution and any improvements you would make if you had more time.
Given more time, improvements such as better error handling, automated testing, and exploring more modern authenticated encryption techniques could enhance the robustness and efficiency of the solution. Overall, this assignment provided valuable experience in designing and implementing secure communication protocols.
--- 

This structured template should guide students through explaining their approach, process, and understanding of key cryptographic principles used in this assignment.