# Secure Password Manager - Final Report

## Table of Contents
1. **Introduction**
2. **System Features and Functional Requirements**
   - 1. Sign-Up
   - 2. Sign-In
   - 3. Adding New Services and Passwords
   - 4. Retrieving Passwords
   - 5. Updating/Deleting Passwords
   - 6. Changing the Master Password
   - 7. Sign-Out
   - 8. Master Password Recovery
3. **Cryptographic Components and Design Choices**
4. **Project Reflection**
5. **Lessons Learned**
6. **Conclusion**

---

## **1. Introduction**
This report outlines the implementation of our secure password manager program. The application uses modern cryptographic methods for securely storing passwords, integrity verification, and password recovery. The features of our program includes user authentication, password encryption, and master password recovery using RSA.

---

## **2. System Features and Functionalities**

### **1. Sign-Up**
- **Input:** Master password.
- **Process:**
  1. Hash and salt the master password using PBKDF2 with SHA-256.
  2. Save the salt and hashed password in `master_pass.txt`.
  3. Generate an RSA key pair for recovery and save it securely in `.pem` files.
  4. Backup the master key using the RSA public key, storing it in `backup_key.txt`.
- **Output:** Master account is created, and cryptographic keys are securely stored.

### **2. Sign-In**
- **Input:** Master password.
- **Process:**
  1. Confirm the input master password against the stored salted hash.
  2. If confirmed, get an encryption key and HMAC key using PBKDF2.
- **Output:** User is verified and can get into the password manager program.

### **3. Adding New Services and Passwords**
- **Input:** Service name and its password.
- **Process:**
  1. Encrypt the password using AES-CTR with a generated nonce.
  2. Compute an HMAC for the encrypted password.
  3. Save the encrypted password and associated metadata in `passwords.txt`.
- **Output:** New service and password are securely stored.

### **4. Retrieving Passwords**
- **Input:** Service name.
- **Process:**
  1. Locate the encrypted password and its nonce.
  2. Verify the password's HMAC to ensure integrity.
  3. Decrypt the password using AES-CTR.
- **Output:** Decrypted password is displayed to the user.

### **5. Deleting Services**
- **Input:** Service name.
- **Process:**
  1. Locate the service in `passwords.txt`.
  2. Remove the corresponding entry securely.
- **Output:** Service and its password are deleted.

### **6. Changing the Master Password**
- **Process:**
  1. Authenticate the user with the current master password.
  2. Prompt for a new password and confirm it.
  3. Re-hash and re-salt the new password, saving it to `master_pass.txt`.
- **Output:** Master password is updated successfully.

### **7. Master Password Recovery**
- **Backup:**
  1. During sign-up, encrypt the master key using the RSA public key and save it in `backup_key.txt`.
- **Recovery:**
  1. Use the RSA private key to decrypt the master key stored in `backup_key.txt`.
  2. Provide the recovered hashed master password to the user.
- **Output:** Recovered hashed master password.

### **8. Sign-Out**
- **Process:** Clear sensitive data from memory and exit the session.
- **Output:** User is securely signed out.

---

## **3. Cryptographic Components and Design Choices**

### **1. PBKDF2 with SHA-256**
- Used for hashing the master password with a salt to ensure secure password storage.

### **2. AES-CTR**
- We used AES-CTR mode for encrypting passwords with a random 16-byte nonce for each entry.

### **3. RSA**
- RSA key pairs were used for securely backing up and recovering the master key.

### **4. HMAC with SHA-256**
- We used HMAC with SHA-256 to ensure the integrity and authenticity of encrypted data.

### **5. Secure File Management**
- The master password and encrypted data are securely stored in `.txt` and `.pem` files.

---

## **4. Project Reflection**
For this project, we decided on a practical AES-RSA approach, which allowed us to encrypt and decrypt data effortlessly and achieve clear, expected outcomes. This approach was essential for the three of us to complete the project successfully. 

Meeting the requirements of the project while running everything on the terminal was a challenging task. Coordinating and dividing tasks among the three of us proved difficult due to the broad scope of the project and our initial unfamiliarity with implementing some aspects of the assignment without templates or detailed resources. 

Despite these challenges, we believe the requirements have been met, and the final result is something we are proud of. It required a considerable amount of learning and collaboration, especially in troubleshooting errors during runtime in the terminal.

---

## **5. Lessons Learned**

1. **Importance of Strong Key Derivation:**
   PBKDF2 ensures computationally intensive key derivation, making brute force attacks impractical.

2. **Proper Use of Nonces:**
   Generating a unique nonce for AES-CTR prevents vulnerabilities such as ciphertext reuse.

3. **HMAC for Data Integrity:**
   Ensuring data authenticity through HMAC minimizes risks of data tampering.

4. **RSA for Recovery:**
   RSA keys provide a robust mechanism for securely recovering the master password.

5. **Sensitive Data Management:**
   Clearing sensitive data from memory post-use is critical for minimizing exposure.

6. **User-Friendly Security:**
   Balancing ease of use with cryptographic rigor encourages better adoption of security practices.

7. **Error Handling:**
   Providing clear error messages without leaking sensitive information enhances the application's usability and security.

8. **Secure File Permissions:**
   Proper access control for sensitive files (e.g., private keys) is essential for protecting data.

9. **Encryption Key Separation:**
   Using separate keys for encryption and HMAC prevents potential cross-contamination of cryptographic operations.

10. **Backup and Recovery Planning:**
    Establishing a secure backup mechanism minimizes data loss risks.

---

## **6. Conclusion**

The password manager program we made demonstrates cryptographic best practices and provides password storage, retrieval, and recovery. By using cryptographic libraries, our program ensures both security and usability, it also meets the needs of users who want a reliable password manager. This project was a joint effort that pushed us to overcome significant challenges and achieve a functional, secure application. The methods we used for this project were a bit different than the structure of the code provided because we used the terminal to test our password manager. We decided on a practical AES-RSA approach that allowed us to encrypt and decrypt effortlessly while also giving us a clear outcome that we needed to complete the project. We tested the program until the requirements for this project were met and added a redirection phase that allowed us to redirect potential attackers from sensitive data. The toughest portion of this project was getting the three of us to put the portions we completed together to make a cohesive program that compiled in the terminal to give us the desired results. Another difficulty we faced was that each of us had portions that were broad and unspecified in the template code. The instructions were not as detailed or specific which made it harder for us to comprehend what we needed to complete the program. However, with a lot of research and using class-provided resources we were able to work through the project.

---
