# Assignment 3: Image Encryption with ECB, CBC, and CTR Modes

## Objective

In this assignment, you will build on the work done in **Lab 3**, where you implemented image encryption using AES-ECB mode. You will now expand the implementation to include **CBC** and **CTR** modes of AES. Using sample codes for CBC and CTR, you will:
1. Implement image encryption using **ECB**, **CBC**, and **CTR** modes in **one Python file**.
2. Compare and analyze the visual and security effects of encrypting images with these different modes.
3. Document your findings in `assignment3_report.md`.

---

## Task Breakdown

### Part 1: Implement Image Encryption for ECB, CBC, and CTR Modes

You will create a **Python program** to implement image encryption and decryption using different AES modes. The file should include three classes, each responsible for encrypting and decrypting images using AES in a specific mode:

1. **ECB Mode**:
   - **Class**: `ECBImageEncryptor`
   - Implement image encryption and decryption using **AES in ECB mode**.
   - Ensure the code properly handles image encryption, leaves the first 54 bytes (header) unchanged, and pads the image body correctly for AES encryption.

2. **CBC Mode**:
   - **Class**: `CBCImageEncryptor`
   - Modify the ECB implementation to support encryption using **AES in CBC mode**.
   - Handle the **Initialization Vector (IV)** by generating it randomly and storing it properly for use during decryption.

3. **CTR Mode**:
   - **Class**: `CTRImageEncryptor`
   - Modify the ECB implementation to support encryption using **AES in CTR mode**.
   - Handle the **IV (Nonce)** appropriately, as CTR mode operates as a stream cipher.

Your Python file should handle reading an image, encrypting it, and writing the encrypted result into a new image file for each mode.

---

### Part 2: Compare the Results
Using your three classes, encrypt **top_secret.bmp**. After encrypting the image using the three modes, analyze the differences in both visual output and security:

1. **Visual Comparison**:
   - Compare the appearance of the encrypted images across the three modes.
   - **ECB Mode**: Note if recognizable patterns remain in the image after encryption.
   - **CBC and CTR Modes**: Compare the resulting images to assess how they mask patterns and provide better security compared to ECB.

2. **Security Comparison**:
   - Explain why **ECB mode** is insecure for encrypting structured data like images.
   - Discuss how **CBC mode** improves security by introducing an IV.
   - Highlight the advantages of **CTR mode** for encrypting large or streaming data.

---

### Part 3: Complete the Report

Create a report file titled `assignment3_report.md` where you will analyze the results and answer the following questions:

1. **Description of Image Encryption**:
   - Describe the process of image encryption for each mode (ECB, CBC, and CTR).
   
2. **Visual and Security Analysis**:
   - Compare the visual differences between the images encrypted using each mode.
   - Which encryption mode produces the most visually secure result, and why?
   - How does each mode differ in terms of security when encrypting structured data like images?

3. **Answer the Following Questions**:
   - Why is **ECB mode** unsuitable for encrypting structured data like images?
   - How does **CBC mode** enhance security compared to ECB?
   - What are the primary advantages of **CTR mode**, and in what scenarios is it preferable to CBC or ECB?
   - If you were encrypting confidential image data, which mode would you choose and why?

4. **Additional Questions**:
   - Is padding necessary for each mode? Why or why not?
   - How does handling the **Initialization Vector (IV)** differ between CBC and CTR modes?

---

## Deliverables

1. **Python File**:
   - `image_encryptor.py`: This file should include three classes:
     - `ECBImageEncryptor`: Handles image encryption and decryption using AES in ECB mode.
     - `CBCImageEncryptor`: Handles image encryption and decryption using AES in CBC mode.
     - `CTRImageEncryptor`: Handles image encryption and decryption using AES in CTR mode.

2. **Encrypted Image Files**:
   - Three encrypted versions of the image (e.g., `top_secret.bmp`):
     - `encrypted_image_ecb.bmp`
     - `encrypted_image_cbc.bmp`
     - `encrypted_image_ctr.bmp`

3. **Report**:
   - `assignment3_report.md`: A detailed comparison of ECB, CBC, and CTR modes based on the visual and security analysis.

---

## Grading Criteria

- **Code Correctness**: Your Python script should correctly encrypt and decrypt the image using the specified modes.
- **Thoroughness of Analysis**: Your report should address the provided questions in detail, demonstrating a clear understanding of the differences between the encryption modes.
- **Completion**: Ensure all files (Python script, encrypted images, and the report) are submitted.

---

## Learning Outcomes

By completing this assignment, you will:
- Gain hands-on experience with AES encryption in **ECB**, **CBC**, and **CTR** modes.
- Understand the **visual and security implications** of different encryption modes, especially when applied to structured data like images.
- Learn how to handle key cryptographic concepts such as **padding** and **Initialization Vectors (IVs)** across different AES modes.
- Be able to select an appropriate encryption mode based on the type of data being encrypted.

---
