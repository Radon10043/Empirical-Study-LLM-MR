> ### `indexOf` Function Specification
>
> #### Purpose
> Implements the Boyer-Moore algorithm for fast string searching. This function searches for a substring within a given string and returns the index of the first occurrence of the substring. If the substring is not found, it returns -1.
>
> #### Signature
> ```java
> public static int indexOf(String text, String pattern)
> ```
>
> #### Parameters
> - `text` : String
>     - The text in which to search for the pattern.
> - `pattern` : String
>     - The substring to search for within the text.
>
> #### Returns
> - `int`
>     - The index of the first occurrence of `pattern` within `text`.
>     - Returns -1 if `pattern` is not found within `text`.
>
> #### Requirements
> - JDK version 1.6 or higher.
>
> #### Usage Example
> ```java
> int index = Boyer.indexOf("example text", "text");
> System.out.println(index); // Outputs: 8
> ```
>
> #### Notes
> - This implementation likely utilizes preprocessing of the `pattern` for efficient searching, taking advantage of the Boyer-Moore algorithm's properties to skip sections of the `text` that cannot possibly match the `pattern`.
> - The algorithm is designed for efficiency and is particularly effective for searches in long texts or when the pattern is relatively long.