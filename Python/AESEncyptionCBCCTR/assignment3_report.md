


## Description of Image Encryption:

ECB mode works by dividing an image into blocks of different sizes. A symmetric key is used to encrypt each block. 
THe resulting series of the encrypted blocks are concatenated to to form the ciphertext.

CBC mode works by using an intialization vector to XOR with the first block before encryption. Next, each subsequent block is XORed with the previous encrypted bloc, before encryption. This causes identical blocks of plaintext
to produce different ciphertexts. 

CTR mode converts the block cipher into a stream cipher. A counter and IV are used in combination to generate a unique nonce for each block. The cipher text is produced by encrypting the nonce and XOR it with the plaintext. 

---

**Visual and Security Analysis**:
   - In ECB mode, identical plaintext blocks produce the same ciphertext, causing patterns to be visible. Frequency analysis will reveal this, leading to vulnerability.
   - In CBC mode, the output is more random so the structure of the original image is less recognizable. Familiar areas of the image are obscured, making it hard to realize the original image.
   - In CTR mode, it is similar to CBC in how the output is random. A counter is used to ensure that identical areas appear different in the resulting image.

Therefore, the encryption mode that produces the most visually secure result is CTR. It very effectively conceals the patterns in the image; the counter also provides an additional layer of uniqueness, making it the most secure.


**Why is **ECB mode** unsuitable for encrypting structured data like images?**:

ECB mode is unsuitable because it encrypts identical blocks of plaintext into identical ciphertext blocks. Conseuqntly, patterns in the image remain visible after encryption, making it vulnerable.


**How does **CBC mode** enhance security compared to ECB?**:

CBC mode enhances securoty because it uses an intialization vector and chaining blocks together. THE XOR process ensures that identical plaintext blocks will produce different ciphertext blocks. Consequently, there are less visible patterns in the result.

**What are the primary advantages of **CTR mode**, and in what scenarios is it preferable to CBC or ECB?**:
  

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

