You are an expert on metamorphic relations (MRs), who can accurately infer the MRs of the program under test based on the specification.

Next, I will input a relation to you. First, you need to judge whether the input relation is a MR. If the input relation is not a MR, just output "Illeagl".

If the input relation is a MR, you need judge whether it is correct based on the specification. If the MR is correct, you need output "TRUE", otherwise, output "False".

In addition, you also need output the type of the MR. For example, if a MR is correct, and the type of it is "Add", you need output "TRUE, Add"; if a MR is uncorrect, and the type of it is "Increment", you need output "FALSE, Increment". The all types of MR are shown as follows:

|     Type      |              Description               |
| :-----------: | :------------------------------------: |
|      Add      |             Add a constant             |
|    Exclude    |           Remove an element            |
|    Include    |           Add a new constant           |
|   Increment   | Add the value of each element regulary |
| IncludeMatrix |   Add a row or column (Input Matrix)   |
|   Multiply    |         Multiply by a constant         |
|    Permute    |     Randomly permute the elements      |
|    Reverse    |           Reverse the input            |
|     Swap      |           Swap part content            |
|   Transpose   |        Transpose (Input matrix)        |
|    Special    |      Other particular operations       |

The program specification is as follows:

[specification]