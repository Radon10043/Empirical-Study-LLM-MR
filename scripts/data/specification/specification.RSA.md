> ### `candp` Function Specification
>
> #### Description
> The `candp` function performs modular exponentiation. It calculates \(m^e \mod n\), where \(n\) is the product of two numbers \(p\) and \(q\). This operation is common in cryptographic algorithms, such as RSA, where it's used for encryption and decryption processes as well as digital signatures.
>
> #### Function Signature
> ```c++
> long long candp(int m, int e, int p, int q);
> ```
>
> #### Parameters
> - `m`: The base integer of the modular exponentiation. In cryptographic terms, this could represent the message to be encrypted or decrypted.
> - `e`: The exponent in the modular exponentiation. In the context of RSA, this could be the public or private exponent.
> - `p` and `q`: Two integers whose product forms the modulus for the operation. In RSA, these would be the prime factors of the modulus.
>
> #### Returns
> - The function returns a `long long` integer that is the result of \(m^e \mod (p \cdot q)\).
>
> #### Logic
> 1. **Initialize Variables**: Initializes the result as 1 and calculates the modulus \(n\) as the product of `p` and `q`.
>
> 2. **Modular Exponentiation**: Iteratively multiplies `result` by `m` modulo \(n\), `e` times. This loop effectively performs the operation \(m^e \mod n\) without directly calculating the potentially very large number \(m^e\) and then applying the modulus.
>
> 3. **Modulus in Multiplication**: The temporary variable `temp` stores the intermediate product of `result` and `m` modulo \(n\) in each iteration. This ensures that the result does not overflow the bounds of a `long long` integer during the computation.
>
> 4. **Return Result**: After `e` iterations, returns the final value of `result`, which is \(m^e \mod n\).
>
> #### Notes
> - The function uses a simple loop for exponentiation, which can be efficient for small to moderate-sized exponents but might not be optimal for very large exponents. For larger exponents, methods like square-and-multiply could offer better performance.
> - The function is designed to work within the bounds of `long long` integers, making it suitable for handling the large numbers typical in cryptographic applications, but it's still subject to overflow if `m`, `e`, `p`, or `q` are too large.
> - The calculation is done modulo \(n\) to ensure that the result remains within a manageable size, adhering to the constraints of modular arithmetic commonly used in cryptography.