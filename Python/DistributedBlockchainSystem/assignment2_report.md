
# Hanna Aamir - Assignment 2 Report

## Proof of Work (PoW) in This Assignment



Proof of Work (PoW) is employed in this assignment as a function, which gets called in the main program in order to find the valid nonce and current hash value. The nonce produces a valid hash (less than the predetermined target value) after is is summed with the previous block;s hash and user input. The purpose of PoW, in this assignment, remains typical as it is used to validate transactions and add new blocks to the chain.

PoW function logic:
1. **Concatenation**: The nonce, previous hash, and user input are concatenated into a single string.
2. **Hashing**: Another function for sha 256 is called to produce a hash value for the concatenated string.
3. **Comparison**: The resulting hash is compare; if the hash is lower than the target, the nonce is valid, and a new block can be created.
4. **Iteration**: An invalid hash results in an increment of the nonce and a repeat of this process.



## Impact of Adjusting the PoW Target

Overall, reducing the target value increases the difficulty of the puzzle. 

### More specifically:

- **Difficulty Increase**: Lowering the target value decreaes the range of acceptable nonce values since the hash must be smaller than the target. As a result, it becomes more difficult. 
- **Greater # of Attempts Required**: Since there is a smaller range of acceptable values, more nonce values need to be tested to find a valid one. In other words, the expected number of attempts to find a valid nonce grows exponentially as the target decreases. This is a result of the hash output space being fixed (with a smaller target creating a narrower range of acceptable hashes).
- **Performance Implications**: Naturally, the increase in attempts results in an increase in time - which lower performance.

## Challenges Encountered During Implementation




1. **Matching example output**: I encountered issues when verifying the correctness of the nonce values with the example output give . I researched and realized that the order of concatenation as well as the operating system results in this output difference.



4. **PoW Function Return**: I realized I had to make the PoW return nonce and current hash in order to be able to compute it in the main - instead of just returning the nonce.

